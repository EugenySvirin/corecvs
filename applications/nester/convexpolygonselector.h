#ifndef CONVEXPOLYGONSELECTOR_H
#define CONVEXPOLYGONSELECTOR_H
#include <vector>
#include "core/geometry/polygons.h"

namespace corecvs {
class ConvexPolygonSelector {
public:
    ConvexPolygonSelector();

    void sortByAreaIncrease(std::vector<Polygon> &placedPolygons);
    void sortByAreaDecrease(std::vector<Polygon> &placedPolygons);
    void randomSort(std::vector<Polygon> &placedPolygons); // will be implemented later

    void lowerTheVertexMasses(std::vector<Polygon> &placedPolygons);
    void lowerTheMasses(std::vector<Polygon> &placedPolygons);

//private:
};
} // namespace corecvs
#endif // CONVEXPOLYGONSELECTOR_H
