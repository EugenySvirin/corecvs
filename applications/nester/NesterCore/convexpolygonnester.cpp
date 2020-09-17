#include "NesterCore/convexpolygonnester.h"
namespace corecvs {
ConvexPolygonNester::ConvexPolygonNester() {}

ConvexPolygonNester::ConvexPolygonNester(
        std::vector<Polygon>& inputPolygons,
        Rectangled& bin): bin(bin),
        inputPolygons(inputPolygons) {}

void ConvexPolygonNester::run_FFI_BLPR(int rotations) {
    runNester(OrderMethod::FFI, MassesMethod::noMassesMethod,
              PlacementMethod::blPlacementWithRotations, rotations);
}

void ConvexPolygonNester::run_FFD_BLPR(int rotations) {
    runNester(OrderMethod::FFD, MassesMethod::noMassesMethod,
              PlacementMethod::blPlacementWithRotations, rotations);
}

void ConvexPolygonNester::run_FFD_LM_BLPR(int rotations) {
    runNester(OrderMethod::FFD, MassesMethod::masses,
              PlacementMethod::blPlacementWithRotations, rotations);
}

void ConvexPolygonNester::run_FFD_LM_BLPR_H(int rotations) {
    runNester(OrderMethod::FFD, MassesMethod::masses,
              PlacementMethod::blPRHeightPriority, rotations);
}

void ConvexPolygonNester::run_FFD_LM_BLPR_M(int rotations) {
    runNester(OrderMethod::FFD, MassesMethod::masses,
              PlacementMethod::blPRMassPriority, rotations);
}

void ConvexPolygonNester::run_FFD_LVM_BLPR_H(int rotations) {
    runNester(OrderMethod::FFD, MassesMethod::verticesMasses,
              PlacementMethod::blPRHeightPriority, rotations);
}

void ConvexPolygonNester::run_FFD_LVM_BLPR_VM(int rotations) {
    runNester(OrderMethod::FFD, MassesMethod::verticesMasses,
              PlacementMethod::blPRVerticesMassPriority, rotations);
}

void ConvexPolygonNester::runNester(OrderMethod orderMethod, MassesMethod massesMethod,
                                    PlacementMethod placementMethod, int rotations) {
    int check = runCheck();
    if (check < 0) {
        return;
    }
    processingPolygons = inputPolygons;
    selector.setOrderMethod(orderMethod);
    selector.setMassesMethod(massesMethod);
    selector.runSelection(processingPolygons);
    placer.setPlacementMethod(placementMethod);
    placer.runPlacement(processingPolygons, rotations);
    placedPolygons = placer.getPlacedPolygons();
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
} //namespace corecvs
