#ifndef CONVEXPOLYGONPLACER_H
#define CONVEXPOLYGONPLACER_H
#include <vector>
#include "core/geometry/polygons.h"

namespace corecvs {



class ConvexPolygonPlacer {
private:
    size_t saturation;
    size_t binSaturation;
    double sigma;

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

//    std::vector<Polygon> blPRPriority(
//            std::vector<Polygon> &polygons, int rotations);
//    std::vector<Polygon> &polygons, int rotations, function handler);

//
//    blPRMassPriority, blPRVerticesMassPriority, blPRHeightPriority are same
//    except for choosing best position predicate, may be one day this class
//    will be reengineered to stratefy pattern, or at least to give preedicates
//    as arguments to blPRPriority
//
public:
   ConvexPolygonPlacer();
   ConvexPolygonPlacer  (size_t saturation);
   ConvexPolygonPlacer  (size_t saturation, size_t binSaturation);
   ConvexPolygonPlacer  (size_t saturation, size_t binSaturation,
                         const Rectangled& bin);

   void setSaturation   (size_t newSaturation);
   void setBinSaturation(size_t newBinSaturation);
   void setSigma        (double newSigma);
   void setBin          (const Rectangled& bin);
   size_t getSaturation() const;
   size_t getBinSaturation() const;
   double getSigma() const;
   Rectangled getBin() const;

   std::vector<Polygon> blPlacement(
           std::vector<Polygon> &polygons);

   std::vector<Polygon> blPlacementWithRotations(
           std::vector<Polygon> &polygons, int rotations);

   std::vector<Polygon> blPRMassPriority(
           std::vector<Polygon> &polygons, int rotations);

   std::vector<Polygon> blPRVerticesMassPriority(
           std::vector<Polygon> &polygons, int rotations);

   std::vector<Polygon> blPRHeightPriority(
           std::vector<Polygon> &polygons, int rotations);
};

} // namespace corecvs
#endif // CONVEXPOLYGONPLACER_H
