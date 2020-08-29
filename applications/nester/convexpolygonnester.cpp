#include "convexpolygonnester.h"
namespace corecvs {
ConvexPolygonNester::ConvexPolygonNester() {}

ConvexPolygonNester::ConvexPolygonNester(
        std::vector<Polygon>& inputPolygons,
        Rectangled& bin): bin(bin),
        inputPolygons(inputPolygons) {}

void ConvexPolygonNester::setBin(Rectangled& newBin) {
    bin = newBin;
    placer.setBin(newBin);
}
void ConvexPolygonNester::setInputPolygons(
        std::vector<Polygon>& newInputPolygons) {
    inputPolygons = newInputPolygons;
}

void ConvexPolygonNester::setSigma(double sigma) {
    placer.setSigma(sigma);
}

void ConvexPolygonNester::setSaturation(size_t saturation) {
    placer.setSaturation(saturation);
}

void ConvexPolygonNester::setBinSaturation(size_t binSaturation) {
    placer.setBinSaturation(binSaturation);
}

double ConvexPolygonNester::getSigma() {
    return placer.getSigma();
}

size_t ConvexPolygonNester::getSaturation() {
    return placer.getSaturation();
}

size_t ConvexPolygonNester::getBinSaturation() {
    return placer.getBinSaturation();
}

vector<Polygon> ConvexPolygonNester::getPlacedPolygons() {
    return placedPolygons;
}

int ConvexPolygonNester::runCheck() {
    using namespace std;
    if (inputPolygons.empty()) {
        cerr << "empty input list" << endl;
        return -1;
    }
    for (auto& pol : inputPolygons) {
        doClockOrP(pol);
    }
    return 0;
}

void ConvexPolygonNester::FFI() {
    selector.sortByAreaIncrease(processingPolygons);
}

void ConvexPolygonNester::FFD() {
    selector.sortByAreaDecrease(processingPolygons);
}

void ConvexPolygonNester::LM() {
    selector.lowerTheMasses(processingPolygons);
}

void ConvexPolygonNester::LVM() {
    selector.lowerTheVertexMasses(processingPolygons);
}

void ConvexPolygonNester::BLP() {
    placedPolygons = placer.blPlacement(processingPolygons);
}

void ConvexPolygonNester::BLPR(int rotations) {
    placedPolygons = placer.blPlacementWithRotations(processingPolygons, rotations);
}

void ConvexPolygonNester::BLPR_H(int rotations) {
    placedPolygons = placer.blPRHeightPriority(processingPolygons, rotations);
}

void ConvexPolygonNester::BLPR_M(int rotations) {
    placedPolygons = placer.blPRMassPriority(processingPolygons, rotations);
}
void ConvexPolygonNester::BLPR_VM(int rotations) {
    placedPolygons = placer.blPRVerticesMassPriority(processingPolygons, rotations);
}

void ConvexPolygonNester::runBLP() {
    int check = runCheck();
    if (check < 0) {
        return;
    }
    processingPolygons = inputPolygons;
    BLP();
}

void ConvexPolygonNester::runBLP_LM() {
    int check = runCheck();
    if (check < 0) {
        return;
    }
    processingPolygons = inputPolygons;
    LM();
    BLP();
}

void ConvexPolygonNester::runBLP_LVM(){
    int check = runCheck();
    if (check < 0) {
        return;
    }
    processingPolygons = inputPolygons;
    LVM();
    BLP();
}

void ConvexPolygonNester::run_FFD_BLPR(int rotations) {
    int check = runCheck();
    if (check < 0) {
        return;
    }
    processingPolygons = inputPolygons;
    FFD();
    BLPR(rotations);
}

void ConvexPolygonNester::run_FFD_LM_BLPR(int rotations) {
    int check = runCheck();
    if (check < 0) {
        return;
    }
    processingPolygons = inputPolygons;
    FFD();
    BLPR(rotations);
}

void ConvexPolygonNester::run_FFI_BLPR(int rotations) {
    int check = runCheck();
    if (check < 0) {
        return;
    }
    processingPolygons = inputPolygons;
    FFI();
    BLPR(rotations);
}

void ConvexPolygonNester::run_FFD_LM_BLPR_H(int rotations) {
    int check = runCheck();
    if (check < 0) {
        return;
    }
    processingPolygons = inputPolygons;
    FFD();
    LM();
    BLPR_H(rotations);
}

void ConvexPolygonNester::run_FFD_LM_BLPR_M(int rotations) {
    int check = runCheck();
    if (check < 0) {
        return;
    }
    processingPolygons = inputPolygons;
    FFD();
    LM();
    BLPR_M(rotations);
}

void ConvexPolygonNester::run_FFD_LVM_BLPR_VM(int rotations) {
    int check = runCheck();
    if (check < 0) {
        return;
    }
    processingPolygons = inputPolygons;
    FFD();
    LVM();
    BLPR_VM(rotations);
}

void ConvexPolygonNester::run_FFD_LVM_BLPR_H(int rotations) {
    int check = runCheck();
    if (check < 0) {
        return;
    }
    processingPolygons = inputPolygons;
    FFD();
    LVM();
    BLPR_H(rotations);
}

} //namespace corecvs
