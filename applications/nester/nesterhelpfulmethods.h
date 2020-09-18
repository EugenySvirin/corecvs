#ifndef NESTERHELPFULMETHODS_H
#define NESTERHELPFULMETHODS_H
#include "core/buffers/rgb24/abstractPainter.h"

namespace corecvs {
void drawPolygons(vector<Polygon> inputPolygons,
                  int h, int w, string bmpname);
void drawSvgPolygons(vector<Polygon> inputPolygons,
                     int h, int w, string svgName);
vector<Polygon> loadPolygonsDXF(const string name);
vector<Polygon> loadPolygonsSVG(const string name);
} //namespace corecvs
#endif // NESTERHELPFULMETHODS_H
