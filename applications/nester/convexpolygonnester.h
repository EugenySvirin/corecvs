#ifndef CONVEXPOLYGONNESTER_H
#define CONVEXPOLYGONNESTER_H
#include <vector>
#include "core/geometry/polygons.h"
#include "nester_geometry.h"
#include "convexpolygonselector.h"
#include "convexpolygonplacer.h"

namespace corecvs {
class ConvexPolygonNester {
public:
    ConvexPolygonNester();
    ConvexPolygonNester(
            std::vector<Polygon>& inputPolygons,
            Rectangled& bin);

    void setBin(Rectangled& newBin);
    void setInputPolygons(
            std::vector<Polygon>& newInputPolygons);
    void setSigma(double sigma);
    void setSaturation(size_t sarutation);
    void setBinSaturation(size_t binSaturation);

    Rectangled getBin();
    std::vector<Polygon> getInputPolygons();
    std::vector<Polygon> getPlacedPolygons();
    double getSigma();
    size_t getSaturation();
    size_t getBinSaturation();

    void drawSVGPolygons(const string filename);

    //simple nesters
    void runBLP();
    void runBLP_LVM();
    void runBLP_LM();
    void run_FFI_BLPR(int rotations = 16);
    void run_FFD_BLPR(int rotations = 16);

    //effective ones
    void run_FFD_LM_BLPR(int rotations = 16);
    void run_FFD_LM_BLPR_H(int rotations = 16);
    void run_FFD_LM_BLPR_M(int rotations = 16);
    void run_FFD_LVM_BLPR_H(int rotations = 16);
    void run_FFD_LVM_BLPR_VM(int rotations = 16);

    vector<vector<Polygon>> getRunALLResults(int rotations = 16);
private:
    int runCheck();
    ConvexPolygonSelector selector;
    ConvexPolygonPlacer placer;
    Rectangled bin;
    std::vector<Polygon> inputPolygons;
    std::vector<Polygon> processingPolygons;
    std::vector<Polygon> placedPolygons;

    void FFI();
    void FFD();
    void LM();
    void LVM();
    void BLP();
    void BLPR(int rotations = 16);
    void BLPR_H(int rotations = 16);
    void BLPR_M(int rotations = 16);
    void BLPR_VM(int rotations = 16);
};

}
#endif // CONVEXPOLYGONNESTER_H
