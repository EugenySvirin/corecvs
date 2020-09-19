#ifndef CONVEXPOLYGONNESTER_H
#define CONVEXPOLYGONNESTER_H
#include <vector>
#include "core/geometry/polygons.h"
#include "NesterCore/nester_geometry.h"
#include "NesterCore/convexpolygonselector.h"
#include "NesterCore/convexpolygonplacer.h"

namespace corecvs {
class ConvexPolygonNester {
public:
    ConvexPolygonNester();
    ConvexPolygonNester(const vector<Polygon>& inputPolygons,
                        const Rectangled& bin);

    void run_FFI_BLPR(int rotations = 16);
    void run_FFD_BLPR(int rotations = 16);
    void run_FFD_LM_BLPR(int rotations = 16);
    void run_FFD_LM_BLPR_H(int rotations = 16);
    void run_FFD_LM_BLPR_M(int rotations = 16);
    void run_FFD_LVM_BLPR_H(int rotations = 16);
    void run_FFD_LVM_BLPR_VM(int rotations = 16);

    Rectangled getBin();
    vector<Polygon> getInputPolygons() const;
    vector<Polygon> getPlacedPolygons() const;
    double getSigma();
    size_t getSaturation();
    size_t getBinSaturation();

    void setBin(const Rectangled& newBin);
    void setInputPolygons(const vector<Polygon>& newInputPolygons);
    void setSigma(double sigma);
    void setSaturation(size_t sarutation);
    void setBinSaturation(size_t binSaturation);

private:
    void runNester(OrderMethod orderMethod, MassesMethod massesMethod,
                   PlacementMethod placementMethod, int rotations);
    int runCheck();
    ConvexPolygonSelector selector;
    ConvexPolygonPlacer placer;
    Rectangled bin;
    vector<Polygon> inputPolygons;
    vector<Polygon> processingPolygons;
    vector<Polygon> placedPolygons;
};
}
#endif // CONVEXPOLYGONNESTER_H
