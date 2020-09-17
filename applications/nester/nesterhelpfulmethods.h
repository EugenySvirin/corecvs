#ifndef NESTERHELPFULMETHODS_H
#define NESTERHELPFULMETHODS_H
#include "core/utils/utils.h"
#include "core/buffers/rgb24/abstractPainter.h"
#include "core/buffers/rgb24/rgb24Buffer.h"
#include "core/fileformats/svgLoader.h"
#include "core/utils/utils.h"
#include "core/buffers/rgb24/abstractPainter.h"
#include "core/buffers/rgb24/rgb24Buffer.h"
#include "core/fileformats/svgLoader.h"
#include <core/reflection/commandLineSetter.h>
#include <algorithm>
#include <core/buffers/bufferFactory.h>
#include "core/fileformats/dxf_support/dxfLoader.h"

namespace corecvs {
void drawPolygons(vector<Polygon> inputPolygons,
                  int h, int w, string bmpname);
void drawSvgPolygons(vector<Polygon> inputPolygons,
                     int h, int w, string svgName);
vector<Polygon> loadPolygonsDXF(const string name);
vector<Polygon> loadPolygonsSVG(const string name);
}
#endif // NESTERHELPFULMETHODS_H
