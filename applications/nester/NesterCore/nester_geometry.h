#ifndef NESTER_GEOMETRY_H
#define NESTER_GEOMETRY_H
#include "core/geometry/polygons.h"
// auxillary geometry I couldn't find or got used to
namespace corecvs {
Vector2dd verticesMassCenter(Polygon const &A);

Vector2dd massCenter        (Polygon &A);

double polygonLowBound      (const Polygon& A);

void rotatePolAngle         (Polygon &A, double Phi);

void lowerVertexMassCenter  (Polygon &A);

void lowerMassCenter        (Polygon &A);

size_t getTopRightIndex     (const Polygon &A);

size_t getBotLeftIndex      (const Polygon &A);

Vector2dd getTopRightVertex (const Polygon &A);

Vector2dd getBotLeftVertex  (const Polygon &A);


double OrientAreaTwice      (const Vector2dd &a,
                             const Vector2dd &b,
                             const Vector2dd &c);

bool isClockOrP             (const Polygon &A);

void doClockOrP             (Polygon &A);

Polygon convexNFP           (const Polygon &A,
                             const Polygon &B);

Polygon getSaturatedPolygon (const Polygon& A, size_t steps);

double getPolygonHeight     (const Polygon& A);


bool isInInteriorROConvexPol(const Vector2dd &point,
                             const Polygon &A);
}
#endif // NESTER_GEOMETRY_H
