#include "core/geometry/polygons.h"
#include <vector>
#include <algorithm>
#define _USE_MATH_DEFINES
// auxillary geometry I couldn't find or got used to
namespace corecvs {
double polygonLowBound(const Polygon& A) {
    double lowBound = A[0].y();
    for (auto &v : A) {
        if (lowBound > v.y())
            lowBound = v.y();
    }
    return lowBound;
}

void rotatePolAngle(Polygon &A, double Phi) {
    for (auto &v : A) {
        auto d = v.x() * cos(Phi) - v.y() * sin(Phi);
        v.y() = v.x() * sin(Phi) + v.y() * cos(Phi);
        v.x() = d;
    }
}

Vector2dd verticesMassCenter(Polygon const &A) {
    auto vertexAmount = A.size();
    Vector2dd massCenter = {0, 0};
    for (auto& v: A) {
        massCenter += v;
    }
    massCenter /= (double)vertexAmount;
    return massCenter;
}

Vector2dd massCenter(Polygon &A) {
    if (A.size() <= 3) {
        return verticesMassCenter(A);
    }
    auto vertexAmount = A.size();
    Vector2dd innerPoint = (A[0] + A[2]) / 2;

    Polygon triangle = {A[vertexAmount - 1], A[0], innerPoint};
    Vector2dd triangleMassCenter = verticesMassCenter(triangle);
    Vector2dd massCenter = abs(triangle.area()) * triangleMassCenter;

    for (size_t i = 0; i < vertexAmount - 1; ++i) {
        triangle = {A[i], A[i + 1], innerPoint};
        triangleMassCenter = verticesMassCenter(triangle);
        massCenter += abs(triangle.area()) * triangleMassCenter;
    }
    massCenter /= (double)A.area();
    return massCenter;
}

void lowerVertexMassCenter(Polygon &A) {

    Polygon polygonToRotate = A;
    size_t stepsAmount = 64;
    double step = (2 * M_PI) / (double)stepsAmount;
    size_t bestAngleIndex = 0;
    double bestMassCenterHeight = 1000 * 1000;
    for (size_t i = 0; i < stepsAmount; ++i) {
        rotatePolAngle(polygonToRotate, (double)i * step);
        double curMSy = verticesMassCenter(polygonToRotate).y();
        double curLowBound = polygonLowBound(polygonToRotate);
        double massCenterHeight = curMSy - curLowBound;
        if (bestMassCenterHeight > massCenterHeight) {
            bestMassCenterHeight = massCenterHeight;
            bestAngleIndex = i;
        }
        polygonToRotate = A;
    }
    if (bestAngleIndex != 0) {
        rotatePolAngle(A, bestAngleIndex * step);
    }
}

void lowerMassCenter(Polygon& A) { //copypast of lowerVertexMassCenter except double curMSy = massCenter(polygonToRotate).y();
    Polygon polygonToRotate = A;
    size_t stepsAmount = 64;
    double step = (2 * M_PI) / (double)stepsAmount;
    size_t bestAngleIndex = 0;
    double bestMassCenterHeight = 1000 * 1000;
    for (size_t i = 0; i < stepsAmount; ++i) {
        rotatePolAngle(polygonToRotate, i * step);
        double curMSy = massCenter(polygonToRotate).y();
        double curLowBound = polygonLowBound(polygonToRotate);
        double massCenterHeight = curMSy - curLowBound;
        if (bestMassCenterHeight > massCenterHeight) {
            bestMassCenterHeight = massCenterHeight;
            bestAngleIndex = i;
        }
        polygonToRotate = A;
    }
    if (bestAngleIndex != 0) {
        rotatePolAngle(A, bestAngleIndex * step);
    }
}

size_t getTopRightIndex(const Polygon& A) {
    size_t result = 0;
    Vector2dd topVertex = A[0];
    for (size_t i = 1; i < A.size(); ++i) {
        Vector2dd curVertex = A[i];
        if (topVertex.y() < curVertex.y()) {
            topVertex = curVertex;
            result = i;
        } else if (topVertex.y() == curVertex.y()) {
            if (topVertex.x() < curVertex.x()) {
                topVertex = curVertex;
                result = i;
            }
        }
    }
    return result;
}

size_t getBotLeftIndex(const Polygon &A) {
    size_t result = 0;
    Vector2dd bottomVertex = A[0];
    for (size_t i = 1; i < A.size(); ++i) {
        Vector2dd curVertex = A[i];
        if (bottomVertex.y() > curVertex.y()) {
            bottomVertex = curVertex;
            result = i;
        } else if (bottomVertex.y() == curVertex.y()) {
            if (bottomVertex.x() > curVertex.x()) {
                bottomVertex = curVertex;
                result = i;
            }
        }
    }
    return result;
}

Vector2dd getTopRightVertex(const Polygon &A) {
    return A[getTopRightIndex(A)];
}

Vector2dd getBotLeftVertex(const Polygon &B) {
    return B[getBotLeftIndex(B)];
}

template<typename T1, typename T2>
static T1 getPositiveReserve(T1 m, T2 n) {
    T1 r = m % n;
    if (m >= 0)
        return r;
    else if (n < 0) {
        return (-n + r) % n;
    } else {
        return (n + r) % n;
    }
}

static Vector2dd getPointByGenInd(const Polygon &A, int i) {
    return A[getPositiveReserve(i, A.size())];
}

static Vector2dd getLastVertex(const Polygon& A) {
    return A[A.size() - 1];
}

double OrientAreaTwice (const Vector2dd &a,
                        const Vector2dd &b,
                        const Vector2dd &c) {
    return (a.x() - b.x()) * (c.y() - a.y()) - (a.x() - c.x()) * (b.y() - a.y());
}

bool isClockOrP(const Polygon &A) {
    return (OrientAreaTwice(A.getPoint(0), A.getPoint(1), A.getPoint(2)) >= 0);
}

void doClockOrP(Polygon &A) {
    if(!isClockOrP(A)) {
        A.reverse();
    }
}

//static void dumpROEdges(const Polygon &A, std::vector<Vector2dd> &edges) {
//    for (size_t i = 1; i < A.size(); ++i) {
//        edges.push_back(A[i] -  A[i - 1]);
//    }
//    Vector2dd lastEdge = A[0] - getLastVertex(A);
//    edges.push_back(lastEdge);
//}

//static void dumpCROEdges(const Polygon &A, std::vector<Vector2dd> &edges) {
//    for (size_t i = 1; i < A.size(); ++i) {
//        edges.push_back(A[i - 1] - A[i]);
//    }
//    Vector2dd lastEdge = getLastVertex(A) - A[0];
//    edges.push_back(lastEdge);
//}

//Polygon convexNFP(const Polygon &A,
//                  const Polygon &B) {
//    using namespace std;

//    std::vector<Vector2dd> edges;
//    dumpROEdges(A, edges);
//    dumpCROEdges(B, edges);

//    sort(edges.begin(), edges.end(), leftOXAngleIsSmaller);

//    Polygon nfp = {edges[0]};
//    for (size_t i = 1; i < edges.size(); ++i) {
//        nfp.push_back(edges[i] + nfp[i - 1]);
//    }
//    doClockOrP(nfp);
//    nfp.translate(getBotLeftVertex(B) - getBotLeftVertex(nfp));
//    return nfp;
//}

static bool isRightOriented(const Vector2dd &left,
                            const Vector2dd &right) {
    double orientation = OrientAreaTwice({0, 0}, left, right);
    return (orientation >= 0);
}

Polygon convexNFP(const Polygon &A, const Polygon &B)
//A walks around B, begining in his bottom-left point going counterclockwise(clockwise actually),
//top-right point of A leaves the trace.
//assuming both Polygons are RO
{
    Polygon convexNFP;
    size_t i = getTopRightIndex(A);
    size_t j = getBotLeftIndex(B);
    convexNFP.push_back(getPointByGenInd(B, j));
    size_t length1 = A.size() + i;
    size_t length2 = B.size() + j;
    size_t nfpPlace = 0;
    while(i < length1 && j < length2 ) {
        Vector2dd candidateFromA = -getPointByGenInd(A, i + 1) + getPointByGenInd(A, i);
        Vector2dd candidateFromB = getPointByGenInd(B, j + 1) - getPointByGenInd(B, j);
        if (isRightOriented(candidateFromA, candidateFromB)) {
            convexNFP.push_back(convexNFP[nfpPlace] + candidateFromA);
            ++nfpPlace;
            ++i;
        } else {
            convexNFP.push_back(convexNFP[nfpPlace] + candidateFromB);
            ++nfpPlace;
            ++j;
        }
    }

    for (; i < length1; ++i, ++nfpPlace) {
        Vector2dd candidateFromA = -getPointByGenInd(A, i + 1) + getPointByGenInd(A,i);
        convexNFP.push_back(convexNFP[nfpPlace] + candidateFromA);
    }
    for (; j < length2; ++j, ++nfpPlace) {
        Vector2dd candidateFromB = getPointByGenInd(B, j + 1) - getPointByGenInd(B, j);
        convexNFP.push_back(convexNFP[nfpPlace] + candidateFromB);
    }
    convexNFP.pop_back(); // not to dublicate first vertex
    doClockOrP(convexNFP);
    //convexNFP.translate(getBotLeftVertex(B) - getBotLeftVertex(convexNFP)); //sometimes dat is mistake duno why
    return convexNFP;
}

Polygon getSaturatedPolygon(const Polygon& A, size_t steps = 5) {
    Polygon saturatedPolygon {A[0]};
    for (size_t i = 1; i < A.size(); ++i) {
        for (size_t step = 1; step <= steps; ++step) {
            Vector2dd edgeStep = (A[i] - A[i - 1]) / (double)steps;
            saturatedPolygon.push_back(getLastVertex(saturatedPolygon) + edgeStep);
        }
    }
    for (size_t step = 1; step < steps; ++step) { // < cause exclude dublicate
        Vector2dd edgeStep = (A[0] - getLastVertex(A)) / (double)steps;
        saturatedPolygon.push_back(getLastVertex(saturatedPolygon) + edgeStep);
    }
    return saturatedPolygon;
}

double getPolygonHeight(const corecvs::Polygon& pol) {
    return (getTopRightVertex(pol) - getBotLeftVertex(pol)).y();
}

bool isInInteriorROConvexPol(const Vector2dd &point,
                         const Polygon &A) {
    double oldsign = (A.getPoint(1) - A.getPoint(0)).rightNormal() & (point - A.getPoint(0)); //need to initialized
    int len = A.size();
    for (size_t i = 1; i < len; i++) {
        const Vector2dd &curr = A.getPoint(i);
        const Vector2dd &next = A.getNextPoint(i);
        const Vector2dd normal = (next - curr).rightNormal();
        Vector2dd diff = point - curr;
        double sign = diff & normal;
        if (oldsign >= 0  && sign <= 0) //may be EPSIL better
            return false;
        if (oldsign <= 0  && sign >= 0)
            return false;
        oldsign = sign;
    }
    return true;
}

//bool isInInteriorROConvexPolBinSearch(const Vector2dd &point, //may be one day better to rewrite that and switch to it
//                                    const Polygon &A)
//{
//    double Epsil = 0.0005;
//    size_t len = A.size();
//    Vector2dd O = A.getPoint(0);
//    if (distL1(point, O) < EPSIL)
//        return false;
//    size_t left = 1;
//    size_t mid = A.size() / 2;
//    size_t right = A.size() - 1;
//    Vector2dd diff = point - O;
//    Vector2dd normal;
//    while(right - left > 1)
//    {
//        normal = (A.getPoint(mid) - O).rightNormal();
//        if ((diff & normal) >= 0)
//        {
//            left = mid;
//            mid = (right + mid) / 2;
//        }
//        else
//        {
//            right = mid;
//            mid = (mid + left) / 2;
//        }

//    }
//    Vector2dd leftP = A.getPoint(left);
//    Vector2dd rightP = A.getPoint(right);
//    normal = ( rightP - leftP).rightNormal();
//    return ((normal & (point - leftP)) > 0 &&
//           ((A.getPoint(1) - O).rightNormal() & diff) > EPSIL &&
//           ((A.getPoint(len - 1) - O).leftNormal() & diff) > EPSIL);
//}

} //namespace corecvs
