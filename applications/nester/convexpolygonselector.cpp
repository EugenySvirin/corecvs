#include "convexpolygonselector.h"
#include "nester_geometry.h"
#include <algorithm>

namespace corecvs {
static bool leftHasSmallerArea(Polygon& left, Polygon& right) { //Polygon::area not const
    using namespace std;
    return (left.area() < right.area());
}

static bool leftHasBiggerArea(Polygon& left, Polygon& right) { //Polygon::area not const
    using namespace std;
    return (left.area() > right.area());
}

ConvexPolygonSelector::ConvexPolygonSelector() {}

void ConvexPolygonSelector::sortByAreaIncrease(
        std::vector<Polygon> &placedPolygons) {
    std::sort(placedPolygons.begin(), placedPolygons.end(),
              leftHasSmallerArea);
}

void ConvexPolygonSelector::sortByAreaDecrease(
        std::vector<Polygon> &placedPolygons) {
    std::sort(placedPolygons.begin(), placedPolygons.end(),
              leftHasBiggerArea);
}

void ConvexPolygonSelector::randomSort(
        std::vector<Polygon> &placedPolygons) {

}

void ConvexPolygonSelector::lowerTheVertexMasses(
        std::vector<Polygon> &placedPolygons) {
    for (auto &pol : placedPolygons) {
        lowerVertexMassCenter(pol);
    }
}

void ConvexPolygonSelector::lowerTheMasses(std::vector<Polygon> &placedPolygons) {
    for (auto &pol : placedPolygons) {
        lowerMassCenter(pol);
    }
}

} // namespace corecvs
