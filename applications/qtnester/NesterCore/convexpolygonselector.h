#ifndef CONVEXPOLYGONSELECTOR_H
#define CONVEXPOLYGONSELECTOR_H
#include <vector>
#include "core/geometry/polygons.h"

namespace corecvs {
enum class OrderMethod {
    noOrderMethod,
    FFI,
    FFD
};

enum class MassesMethod {
    noMassesMethod,
    masses,
    verticesMasses
};

class ConvexPolygonSelector {
public:
    ConvexPolygonSelector();
    ConvexPolygonSelector(OrderMethod orderMethod,
                          MassesMethod massesMethod);

    void runSelection(std::vector<Polygon> &placedPolygons);

    OrderMethod getOrderMethod() const;
    MassesMethod getMassesMethod() const;
    void setOrderMethod  (OrderMethod newOrderMethod);
    void setMassesMethod (MassesMethod newMassesMethod);

private:
    void sortByAreaIncrease(vector<Polygon> &placedPolygons);
    void sortByAreaDecrease(vector<Polygon> &placedPolygons);
    void randomSort(vector<Polygon> &placedPolygons); // will be implemented later

    void lowerTheVertexMasses(vector<Polygon> &placedPolygons);
    void lowerTheMasses(vector<Polygon> &placedPolygons);

    OrderMethod orderMethod = OrderMethod::noOrderMethod;
    MassesMethod massesMethod = MassesMethod::noMassesMethod;
};
} // namespace corecvs
#endif // CONVEXPOLYGONSELECTOR_H
