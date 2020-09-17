#ifndef CONVEXPOLYGONPLACER_H
#define CONVEXPOLYGONPLACER_H
#include <vector>
#include "core/geometry/polygons.h"

namespace corecvs {
enum class PlacementMethod{
    blPlacementWithRotations,
    blPRMassPriority,
    blPRVerticesMassPriority,
    blPRHeightPriority
};

class ConvexPolygonPlacer {
public:
   ConvexPolygonPlacer();
   ConvexPolygonPlacer  (size_t saturation);
   ConvexPolygonPlacer  (size_t saturation, size_t binSaturation);
   ConvexPolygonPlacer  (size_t saturation, size_t binSaturation,
                         const Rectangled& bin);

   void blPlacement             (vector<Polygon> &polygons);
   void blPlacementWithRotations(vector<Polygon> &polygons,
                                 int rotations);
   void blPRMassPriority        (vector<Polygon> &polygons,
                                 int rotations);
   void blPRVerticesMassPriority(vector<Polygon> &polygons,
                                 int rotations);
   void blPRHeightPriority      (vector<Polygon> &polygons,
                                 int rotations);
   void runPlacement            (vector<Polygon> &polygons,
                                 int rotations);

   size_t getSaturation() const;
   size_t getBinSaturation() const;
   double getSigma() const;
   Rectangled getBin() const;
   PlacementMethod getPlacementMethod() const;
   vector<Polygon> getPlacedPolygons() const;

   void setSaturation            (size_t newSaturation);
   void setBinSaturation         (size_t newBinSaturation);
   void setSigma                 (double newSigma);
   void setBin                   (const Rectangled& bin);
   void setPlacementMethod       (PlacementMethod newPlacementMethod);

private:
    size_t saturation;
    size_t binSaturation;
    double sigma;
    PlacementMethod placementMethod = PlacementMethod::blPlacementWithRotations;

    std::vector<Polygon> nfps;
    std::vector<Polygon> placedPolygons;
    Rectangled bin;
    Rectangled innerFP;
    Polygon innerFPPol; //костыль да

    void setInnerFitPolygon (const Polygon &A);
    bool checkInnerFP() const;
    bool fittingFirstPolygon(Polygon& A);
    Polygon getSaturatedNFP (const Polygon& A,
                             const Polygon& B) const;
    void dumpNFPs           (Polygon const &A);
    void dumpBinVertices    (vector<Vector2dd> &positions) const;
    void dumpNfpsVertices   (vector<Vector2dd> &positions) const;
    bool positionIsValid    (const Vector2dd &position);
    void findBestPosition   (Polygon& possiblePositions,
                             Polygon curPolygon);
    void findBestPositionRotations
                            (vector<double>& angles,
                             Polygon& possiblePositions,
                             Polygon curPolygon);
};

} // namespace corecvs
#endif // CONVEXPOLYGONPLACER_H
