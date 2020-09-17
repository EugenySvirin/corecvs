#include "NesterCore/convexpolygonselector.h"
#include "nester_geometry.h"
#include <algorithm>

namespace corecvs {
static bool leftHasSmallerArea(Polygon& left, Polygon& right) { //Polygon::area not const
    return (left.area() < right.area());
}

static bool leftHasBiggerArea(Polygon& left, Polygon& right) { //Polygon::area not const
    return (left.area() > right.area());
}

ConvexPolygonSelector::ConvexPolygonSelector() {}

ConvexPolygonSelector::ConvexPolygonSelector(
         OrderMethod orderMethod, MassesMethod massesMethod):
         orderMethod(orderMethod), massesMethod(massesMethod) {}

void ConvexPolygonSelector::runSelection(std::vector<Polygon> &placedPolygons) {
    switch(massesMethod) {
    case MassesMethod::noMassesMethod:
        break;
    case MassesMethod::masses:
       lowerTheMasses(placedPolygons);
        break;
    case MassesMethod::verticesMasses:
        lowerTheVertexMasses(placedPolygons);
        break;
    }
    switch(orderMethod) {
    case OrderMethod::noOrderMethod:
        break;
    case OrderMethod::FFI:
        sortByAreaIncrease(placedPolygons);
        break;
    case OrderMethod::FFD:
        sortByAreaDecrease(placedPolygons);
        break;
    }
}

OrderMethod ConvexPolygonSelector::getOrderMethod() const {
    return orderMethod;
}

MassesMethod ConvexPolygonSelector::getMassesMethod() const {
    return massesMethod;
}

void ConvexPolygonSelector::setOrderMethod(OrderMethod newOrderMethod) {
    orderMethod = newOrderMethod;
}

void ConvexPolygonSelector::setMassesMethod(MassesMethod newMassesMethod) {
    massesMethod = newMassesMethod;
}

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
