#include "convexpolygonplacer.h"
#include "nester_geometry.h"
#include <algorithm>
#include <vector>

namespace corecvs {
static Polygon polFromRec(const Rectangled &R) { //rectangled is RO and corner is ll one, legacy code
    return {R.ulCorner(), R.llCorner(), R.lrCorner(), R.urCorner()};
}

void ConvexPolygonPlacer::setInnerFitPolygon(const Polygon &A) { // all RO, legacy code
    double leftOfA = A.getPoint(0).x();
    double rightOfA = A.getPoint(0).x();
    double topOfA = A.getPoint(0).y();
    double botOfA = A.getPoint(0).y();
    double markedPointAbciss = A.getPoint(0).x(); //marked vertex is top-right of A
    for (size_t i = 1; i < A.size(); ++i) {
        double xCandidate = A.getPoint(i).x();
        double yCandidate = A.getPoint(i).y();
        if (yCandidate > topOfA) {
            topOfA = yCandidate;
            markedPointAbciss = xCandidate;
        } else if (yCandidate == topOfA) {
            if (xCandidate > markedPointAbciss){
                markedPointAbciss = xCandidate;
            }
        } else if (yCandidate < botOfA) {
            botOfA = yCandidate;
        }
        if (xCandidate > rightOfA) {
            rightOfA = xCandidate;
        } else if (xCandidate < leftOfA) {
            leftOfA = xCandidate;
        }
    }
    Vector2dd cornerOfIFP = {markedPointAbciss - leftOfA, topOfA - botOfA};
    cornerOfIFP += bin.corner;

    Vector2dd widthHeightOfIFP = {bin.width()- rightOfA + leftOfA, bin.height() - topOfA + botOfA};
    innerFP = Rectangled(cornerOfIFP.x(), cornerOfIFP.y(), widthHeightOfIFP.x(), widthHeightOfIFP.y()); //x,y,w,h
    innerFPPol = polFromRec(innerFP);
    doClockOrP(innerFPPol);
}

bool ConvexPolygonPlacer::checkInnerFP() const{
    return (innerFP.height() >= 0 && innerFP.width() >= 0);
}

bool ConvexPolygonPlacer::fittingFirstPolygon(Polygon& A) {
    if (checkInnerFP()) {
        Vector2dd topRightInitiate = getTopRightVertex(A);
        A.translate(innerFP.corner - topRightInitiate);
        placedPolygons.push_back(A);
        return true;
    }
    return false;
}

void ConvexPolygonPlacer::dumpNFPs(Polygon const &A) {
    nfps = {};
    for (auto& pol: placedPolygons) {
        nfps.push_back(ConvexPolygonPlacer::getSaturatedNFP(A, pol));
    }
}

void ConvexPolygonPlacer::dumpBinVertices(
        vector<Vector2dd> &positions) const {
    Polygon vertices = getSaturatedPolygon(innerFPPol, binSaturation);
    for (auto& vertix: vertices) {
        positions.push_back(vertix);
    }
}

void ConvexPolygonPlacer::dumpNfpsVertices(
        vector<Vector2dd> &positions) const {
    for (auto &pol: nfps) {
        for (auto& vertex: pol) {
            positions.push_back(vertex);
        }
    }
}

void failToPlace(size_t inputNumber) {
    using namespace std;
    cout << inputNumber << " polygon cannot be placed" << endl;
}

bool ConvexPolygonPlacer::positionIsValid(const Vector2dd &position) {
    if (!innerFP.contains(position)) {//внутри должен быть
        return false;
    }
    for (auto& pol :nfps) {
        if (isInInteriorROConvexPol(position, pol)) {
            return false;
        }
    }
    return true;
}

std::vector<Polygon> ConvexPolygonPlacer::blPlacement(
        std::vector<Polygon> &polygons) {
    using namespace std;
    size_t inputNumber = 0;

    placedPolygons = {};
    nfps = {};

    Polygon curPolygon = polygons[inputNumber];
    setInnerFitPolygon(curPolygon);
    while(!fittingFirstPolygon(curPolygon)
          && inputNumber != polygons.size()) {
        failToPlace(inputNumber);
        curPolygon = polygons[++inputNumber];
        setInnerFitPolygon(curPolygon);
    }
    ++inputNumber;

    while (inputNumber < polygons.size()) {
    curPolygon = polygons[inputNumber];
    setInnerFitPolygon(curPolygon);
    if (!checkInnerFP()) {
        failToPlace(inputNumber);
        ++inputNumber;
        continue;
    }

    dumpNFPs(curPolygon);

    vector<Vector2dd> positions;
    dumpBinVertices(positions);
    dumpNfpsVertices(positions);

    Polygon possiblePositions;
    for (auto& pos: positions) {
        if (positionIsValid(pos)) {
            possiblePositions.push_back(pos);
        }
    }

    if (possiblePositions.empty()) {
        failToPlace(inputNumber);
        ++inputNumber;
        continue;
    }

    Vector2dd bestPostion = getBotLeftVertex(possiblePositions);
    Vector2dd from = getTopRightVertex(curPolygon);
    curPolygon.translate(bestPostion - from);
    placedPolygons.push_back(curPolygon);
    ++inputNumber;
    }
    return placedPolygons;
}

void nfpTranslation(Polygon& A, Vector2dd& position) {
    Vector2dd from = getTopRightVertex(A);
    A.translate(position - from);
}

void ConvexPolygonPlacer::findBestPosition(
                      Polygon& possiblePositions,
                      Polygon curPolygon) {
    Vector2dd bestPosition = getBotLeftVertex(possiblePositions);
    nfpTranslation(curPolygon, bestPosition);
    placedPolygons.push_back(curPolygon);
}

void ConvexPolygonPlacer::findBestPositionRotations(vector<double> &angles,
                      Polygon& possiblePositions,
                      Polygon curPolygon) {
    int angleIndex = getBotLeftIndex(possiblePositions);
    double angle = angles[angleIndex];
    rotatePolAngle(curPolygon, angle);
    Vector2dd bestPosition = getBotLeftVertex(possiblePositions);
    nfpTranslation(curPolygon, bestPosition);
    placedPolygons.push_back(curPolygon);
}

std::vector<Polygon> ConvexPolygonPlacer::blPlacementWithRotations (
        std::vector<Polygon> &polygons, int rotations) {
    using namespace std;
    double pi = 3.1415;
    size_t inputNumber = 0;

    placedPolygons = {};
    nfps = {};

    Polygon curPolygon = polygons[inputNumber];
    setInnerFitPolygon(curPolygon);
    while(!fittingFirstPolygon(curPolygon)
          && inputNumber != polygons.size()) {
        failToPlace(inputNumber);
        curPolygon = polygons[++inputNumber];
        setInnerFitPolygon(curPolygon);
    }
    ++inputNumber;

    while (inputNumber < polygons.size()) {
        double step = 2 * pi / (double)rotations;
        curPolygon = polygons[inputNumber];
        Polygon possiblePositions;
        std::vector<double> angles;
        for (size_t i = 0; i < rotations; ++i) {
            auto curRotationPolygon = curPolygon;
            rotatePolAngle(curRotationPolygon, ((double)i) * step);
            setInnerFitPolygon(curRotationPolygon);
            if (!checkInnerFP()) {
                continue;
            }

            dumpNFPs(curRotationPolygon);

            vector<Vector2dd> positions;

            dumpBinVertices(positions);
            dumpNfpsVertices(positions);

            for (auto& pos: positions) {
                if (positionIsValid(pos)) {
                    possiblePositions.push_back(pos);
                    angles.push_back(i * step);
                }
            }
        }
        if (possiblePositions.empty()) {
            failToPlace(inputNumber);
            ++inputNumber;
            continue;
        }

        findBestPositionRotations(angles, possiblePositions, curPolygon);
        ++inputNumber;
    }
    return placedPolygons;
}

std::vector<Polygon> ConvexPolygonPlacer::blPRMassPriority(
        std::vector<Polygon> &polygons, int rotations) {
    using namespace std;
    double pi = 3.1415;
    size_t inputNumber = 0;

    placedPolygons = {};
    nfps = {};

    Polygon curPolygon = polygons[inputNumber];
    setInnerFitPolygon(curPolygon);
    while(!fittingFirstPolygon(curPolygon)
          && inputNumber != polygons.size()) {
        failToPlace(inputNumber);
        curPolygon = polygons[++inputNumber];
        setInnerFitPolygon(curPolygon);
    }
    ++inputNumber;

    while (inputNumber < polygons.size()) {
        double step = 2 * pi / (double)rotations;
        curPolygon = polygons[inputNumber];
        Polygon priorityPossiblePositions;
        Polygon possiblePositions;
        std::vector<double> angles;
        for (size_t i = 0; i < rotations; ++i) {
            auto curRotationPolygon = curPolygon;
            rotatePolAngle(curRotationPolygon, ((double)i) * step);
            setInnerFitPolygon(curRotationPolygon);
            if (!checkInnerFP()) {
                continue;
            }

            dumpNFPs(curRotationPolygon);

            vector<Vector2dd> positions;
            dumpBinVertices(positions);
            dumpNfpsVertices(positions);

            for (auto& pos: positions) {
                if (positionIsValid(pos)) {
                    if (i != 0) {
                    possiblePositions.push_back(pos);
                    angles.push_back(i * step);
                    } else {
                        priorityPossiblePositions.push_back(pos);
                    }
                }
            }
        }
        if (possiblePositions.empty() && priorityPossiblePositions.empty()) {
            failToPlace(inputNumber);
            ++inputNumber;
            continue;
        }

        if (possiblePositions.empty()) {
            findBestPosition(priorityPossiblePositions, curPolygon);
            ++inputNumber;
            continue;
        }

        if (priorityPossiblePositions.empty()) {
            findBestPositionRotations(angles, possiblePositions, curPolygon);
            ++inputNumber;
            continue;
        }


        Vector2dd bestPriorityPos = getBotLeftVertex(priorityPossiblePositions);
        auto priorityCandidate = curPolygon;
        nfpTranslation(priorityCandidate, bestPriorityPos);

        Vector2dd bestSimplePos = getBotLeftVertex(possiblePositions);
        int angleIndex = getBotLeftIndex(possiblePositions);
        double angle = angles[angleIndex];
        auto simpleCandidate = curPolygon;
        rotatePolAngle(simpleCandidate, angle);
        nfpTranslation(simpleCandidate, bestSimplePos);

        double polHeight = getPolygonHeight(curPolygon);
        double candidateMassCenterDif = (massCenter(priorityCandidate) - massCenter(simpleCandidate)).y();
        if (candidateMassCenterDif < polHeight * sigma) {
            findBestPosition(priorityPossiblePositions, curPolygon);
            ++inputNumber;
        } else {
            findBestPositionRotations(angles, possiblePositions, curPolygon);
            ++inputNumber;
        }
    }
    return placedPolygons;
}

std::vector<Polygon> ConvexPolygonPlacer::blPRVerticesMassPriority(
        std::vector<Polygon> &polygons, int rotations) {
    using namespace std;
    double pi = 3.1415;
    size_t inputNumber = 0;

    placedPolygons = {};
    nfps = {};

    Polygon curPolygon = polygons[inputNumber];
    setInnerFitPolygon(curPolygon);
    while(!fittingFirstPolygon(curPolygon)
          && inputNumber != polygons.size()) {
        failToPlace(inputNumber);
        curPolygon = polygons[++inputNumber];
        setInnerFitPolygon(curPolygon);
    }
    ++inputNumber;

    while (inputNumber < polygons.size()) {
        double step = 2 * pi / (double)rotations;
        curPolygon = polygons[inputNumber];
        Polygon priorityPossiblePositions;
        Polygon possiblePositions;
        std::vector<double> angles;
        for (size_t i = 0; i < rotations; ++i) {
            auto curRotationPolygon = curPolygon;
            rotatePolAngle(curRotationPolygon, ((double)i) * step);
            setInnerFitPolygon(curRotationPolygon);
            if (!checkInnerFP()) {
                continue;
            }

            dumpNFPs(curRotationPolygon);

            vector<Vector2dd> positions;
            dumpBinVertices(positions);
            dumpNfpsVertices(positions);

            for (auto& pos: positions) {
                if (positionIsValid(pos)) {
                    if (i != 0) {
                    possiblePositions.push_back(pos);
                    angles.push_back(i * step);
                    } else {
                        priorityPossiblePositions.push_back(pos);
                    }
                }
            }
        }
        if (possiblePositions.empty() && priorityPossiblePositions.empty()) {
            failToPlace(inputNumber);
            ++inputNumber;
            continue;
        }

        if (possiblePositions.empty()) {
            findBestPosition(priorityPossiblePositions, curPolygon);
            ++inputNumber;
            continue;
        }

        if (priorityPossiblePositions.empty()) {
            findBestPositionRotations(angles, possiblePositions, curPolygon);
            ++inputNumber;
            continue;
        }
        Vector2dd bestPriorityPos = getBotLeftVertex(priorityPossiblePositions);
        auto priorityCandidate = curPolygon;
        nfpTranslation(priorityCandidate, bestPriorityPos);

        Vector2dd bestSimplePos = getBotLeftVertex(possiblePositions);
        int angleIndex = getBotLeftIndex(possiblePositions);
        double angle = angles[angleIndex];
        auto simpleCandidate = curPolygon;
        rotatePolAngle(simpleCandidate, angle);
        nfpTranslation(simpleCandidate, bestSimplePos);

        double polHeight = getPolygonHeight(curPolygon);
        double candidateMassCenterDif = (verticesMassCenter(priorityCandidate)
                                         - verticesMassCenter(simpleCandidate)).y();
        if (candidateMassCenterDif < polHeight * sigma) {
            findBestPosition(priorityPossiblePositions, curPolygon);
            ++inputNumber;
        } else {
            findBestPositionRotations(angles, possiblePositions, curPolygon);
            ++inputNumber;
        }
    }
    return placedPolygons;
}

std::vector<Polygon> ConvexPolygonPlacer::blPRHeightPriority(
        std::vector<Polygon> &polygons, int rotations) {
    using namespace std;
    double pi = 3.1415;
    size_t inputNumber = 0;

    placedPolygons = {};
    nfps = {};

    Polygon curPolygon = polygons[inputNumber];
    setInnerFitPolygon(curPolygon);
    while(!fittingFirstPolygon(curPolygon)
          && inputNumber != polygons.size()) {
        failToPlace(inputNumber);
        curPolygon = polygons[++inputNumber];
        setInnerFitPolygon(curPolygon);
    }
    ++inputNumber;

    while (inputNumber < polygons.size()) {
        double step = 2 * pi / (double)rotations;
        curPolygon = polygons[inputNumber];
        Polygon priorityPossiblePositions;
        Polygon possiblePositions;
        std::vector<double> angles;
        for (size_t i = 0; i < rotations; ++i) {
            auto curRotationPolygon = curPolygon;
            rotatePolAngle(curRotationPolygon, ((double)i) * step);
            setInnerFitPolygon(curRotationPolygon);
            if (!checkInnerFP()) {
                continue;
            }

            dumpNFPs(curRotationPolygon);

            vector<Vector2dd> positions;
            dumpBinVertices(positions);
            dumpNfpsVertices(positions);

            for (auto& pos: positions) {
                if (positionIsValid(pos)) {
                    if (i != 0) {
                    possiblePositions.push_back(pos);
                    angles.push_back(i * step);
                    } else {
                        priorityPossiblePositions.push_back(pos);
                    }
                }
            }
        }
        if (possiblePositions.empty() && priorityPossiblePositions.empty()) {
            failToPlace(inputNumber);
            ++inputNumber;
            continue;
        }

        if (possiblePositions.empty()) {
            findBestPosition(priorityPossiblePositions, curPolygon);
            ++inputNumber;
            continue;
        }

        if (priorityPossiblePositions.empty()) {
            findBestPositionRotations(angles, possiblePositions, curPolygon);
            ++inputNumber;
            continue;
        }
        double polHeight = getPolygonHeight(curPolygon);
        Vector2dd bestPriorityPos = getBotLeftVertex(priorityPossiblePositions);
        Vector2dd bestSimplePos = getBotLeftVertex(possiblePositions);
        if ((bestPriorityPos - bestSimplePos).y() < polHeight * sigma) {
            findBestPosition(priorityPossiblePositions, curPolygon);
            ++inputNumber;
        } else {
            findBestPositionRotations(angles, possiblePositions, curPolygon);
            ++inputNumber;
        }
    }
    return placedPolygons;
}

ConvexPolygonPlacer::ConvexPolygonPlacer():
    saturation(5), binSaturation(200), sigma(0.2),
    bin({10, 10, 60, 60}) {}

ConvexPolygonPlacer::ConvexPolygonPlacer(size_t saturation):
    saturation(saturation), binSaturation(20 * saturation),
    sigma(0.2), bin({10, 10, 60, 60}) {}

ConvexPolygonPlacer::ConvexPolygonPlacer(size_t saturation,
                                          size_t binSaturation):
    saturation(saturation), binSaturation(binSaturation),
    sigma(0.2), bin({10, 10, 60, 60}) {}

ConvexPolygonPlacer::ConvexPolygonPlacer(size_t saturation,
                                          size_t binSaturation,
                                         const Rectangled& bin):
    saturation(saturation), binSaturation(binSaturation),
    sigma(0.2), bin(bin) {}

Polygon ConvexPolygonPlacer:: getSaturatedNFP
(const Polygon& A, const Polygon& B) const {
    return getSaturatedPolygon(corecvs::convexNFP(A, B), saturation);
}

void ConvexPolygonPlacer::setSaturation(size_t newSaturation) {
    saturation = newSaturation;
}

void ConvexPolygonPlacer::setBinSaturation(size_t newBinSaturation) {
    binSaturation = newBinSaturation;
}

void ConvexPolygonPlacer::setSigma(double newSigma) {
    sigma = newSigma;
}

void ConvexPolygonPlacer::setBin(const Rectangled &newBin) {
    bin = newBin;
}

size_t ConvexPolygonPlacer::getSaturation() const {
    return saturation;
}

size_t ConvexPolygonPlacer::getBinSaturation() const {
    return binSaturation;
}

double ConvexPolygonPlacer::getSigma() const {
    return sigma;
}

Rectangled ConvexPolygonPlacer::getBin() const {
    return bin;
}
} //namespace corecvs

//std::vector<Polygon> ConvexPolygonPlacer::blPRPriority(
//        std::vector<Polygon> &polygons, int rotations) {
//    using namespace std;
//    double pi = 3.1415;
//    size_t inputNumber = 0;

//    placedPolygons = {};
//    nfps = {};

//    Polygon curPolygon = polygons[inputNumber];
//    setInnerFitPolygon(curPolygon);
//    while(!fittingFirstPolygon(curPolygon)
//          && inputNumber != polygons.size()) {
//        failToPlace(inputNumber);
//        curPolygon = polygons[++inputNumber];
//        setInnerFitPolygon(curPolygon);
//    }
//    ++inputNumber;

//    while (inputNumber < polygons.size()) {
//        double step = 2 * pi / (double)rotations;
//        curPolygon = polygons[inputNumber];
//        Polygon priorityPossiblePositions;
//        Polygon possiblePositions;
//        std::vector<double> angles;
//        for (size_t i = 0; i < rotations; ++i) {
//            auto curRotationPolygon = curPolygon;
//            rotatePolAngle(curRotationPolygon, ((double)i) * step);
//            setInnerFitPolygon(curRotationPolygon);
//            if (!checkInnerFP()) {
//                continue;
//            }

//            dumpNFPs(curRotationPolygon);

//            vector<Vector2dd> positions;
//            dumpBinVertices(positions);
//            dumpNfpsVertices(positions);

//            for (auto& pos: positions) {
//                if (positionIsValid(pos)) {
//                    if (i != 0) {
//                    possiblePositions.push_back(pos);
//                    angles.push_back(i * step);
//                    } else {
//                        priorityPossiblePositions.push_back(pos);
//                    }
//                }
//            }
//        }
//        if (possiblePositions.empty() && priorityPossiblePositions.empty()) {
//            failToPlace(inputNumber);
//            ++inputNumber;
//            continue;
//        }

//        if (possiblePositions.empty()) {
//            findBestPosition(priorityPossiblePositions, curPolygon);
//            ++inputNumber;
//            continue;
//        }

//        if (priorityPossiblePositions.empty()) {
//            findBestPositionRotations(angles, possiblePositions, curPolygon);
//            ++inputNumber;
//            continue;
//        }
//        double polHeight = getPolygonHeight(curPolygon);
//        Vector2dd bestPriorityPos = getBotLeftVertex(priorityPossiblePositions);
//        Vector2dd bestSimplePos = getBotLeftVertex(possiblePositions);
//        int angleIndex = getBotLeftIndex(possiblePositions);
//        double angle = angles[angleIndex];
//        auto simpleCandidate = curPolygon;
//        auto priorityCandidate = curPolygon;
//        rotatePolAngle(simpleCandidate, angle);
//        nfpTranslation(simpleCandidate, bestSimplePos);
//        nfpTranslation(curPolygon, bestPriorityPos);

//        double candidateMassCenterDif = (verticesMassCenter(priorityCandidate)
//                                         - verticesMassCenter(simpleCandidate)).y();
//        if (candidateMassCenterDif < polHeight * sigma) {
//            findBestPosition(priorityPossiblePositions, curPolygon);
//            ++inputNumber;
//        } else {
//            findBestPositionRotations(angles, possiblePositions, curPolygon);
//            ++inputNumber;
//        }
//    }
//    return placedPolygons;
//}
