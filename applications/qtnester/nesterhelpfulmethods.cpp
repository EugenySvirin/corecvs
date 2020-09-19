#include "nesterhelpfulmethods.h"
#include <fstream>
#include <list>
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
#include "NesterCore/nester_geometry.h"

namespace corecvs {
void drawPolygons(std::vector<Polygon> inputPolygons,
                  int h, int w, string bmpname)
{
    Rectangled area = Rectangled::Empty();
    for (Polygon& p: inputPolygons )
    {
        for (Vector2dd &v : p) {
            cout << "Point:" << v << endl;
            area.extendToFit(v);
        }
    }

    cout << "Surrounding Area " << area << endl;

    /* Some debug output */
    RGB24Buffer *buffer = new RGB24Buffer(h,w);
    Vector2dd scale(buffer->w, buffer->h);

    for (Polygon& p: inputPolygons )
    {
        for (size_t i = 0; i < p.size(); i++)
        {
            Vector2dd  p1 = ((p.getPoint    (i) - area.corner) / area.size) * scale;
            Vector2dd  p2 = ((p.getNextPoint(i) - area.corner) / area.size) * scale;

            cout << "Point:" << p.getPoint(i) << "=>" << (p.getPoint(i) - area.corner) << "=>" << p1 << endl;

            buffer->drawLine(
                        p1, p2,
                        RGBColor::parula((i + 1.0) / p.size()));
        }
    }

    BufferFactory::getInstance()->saveRGB24Bitmap(buffer, bmpname);
}

void drawSvgPolygons(vector<Polygon> inputPolygons, int h, int w, string svgName)
{
    using namespace std;
    std::ofstream file;
    file.open(svgName, std::ios::out);
    file.imbue(std::locale("C"));

    file << "<svg height=\""<< h <<"\" width=\""<< w <<"\">" << endl;
    for (size_t i = 0; i < inputPolygons.size(); i++)
    {
        Polygon &p = inputPolygons[i];

        RGBColor color = RGBColor::parula((double)i / inputPolygons.size());
        char colorStr[7];
        snprintf2buf(colorStr, "%02X%02X%02X", color.r(), color.g(), color.b());

        std::string style="style=\"stroke:#";
        style += colorStr;
        style += ";fill:none;stroke-width:1\"";


        file << "<polygon points=\"";
        for (Vector2dd &point : p)
        {
            file << point.x() << "," << point.y() << " ";
        }
        file << "\" " << style << "/>" << endl;
    }
    file << "</svg>" << endl;

    file.close();
}

void addSubPolygons (SvgShape *shape, vector<Polygon> &inputPolygons)
{
    cout << shape->type;
    SYNC_PRINT(("addSubPolygons(%s):called\n", SvgShape::getName(shape->type)));
    if (shape->type == SvgShape::POLYGON_SHAPE)
    {
        SvgPolygon *polygon = static_cast<SvgPolygon*>(shape);
        SYNC_PRINT(("adding polygon of %d sides\n", (int)polygon->polygon.size()));
        inputPolygons.push_back(polygon->polygon);
    }
    /*

    if (shape->type == SvgShape::PATH_SHAPE)
    {
        SYNC_PRINT(("Try to add Path\n"));
        SvgPath *path = static_cast<SvgPath*>(shape);
        Polygon p;
        if (path->toPolygon(p) == false)
            SYNC_PRINT(("Not a polygon"));
        else
            SYNC_PRINT(("adding polygon of %d sides\n", (int)p.size()));
        inputPolygons.push_back(p);
    }
    */

    if (shape->type == SvgShape::GROUP_SHAPE)
    {
        SvgGroup *group = static_cast<SvgGroup*>(shape);
        for (SvgShape * s : group->shapes)
        {
            addSubPolygons(s, inputPolygons);
        }
    }
}

static Vector2dd getNextPoint(std::list<DxfEntity*> &listOfPoints, const Vector2dd &curPoint) {
    double EPSIL =  0.0001;
    for (auto it = listOfPoints.begin(); it != listOfPoints.end(); ++it) {
        auto point = *it;
        auto entData = (DxfLineData)(dynamic_cast<DxfLineEntity*>(point)->data);
        double curX = entData.startPoint.x();
        double curY = entData.startPoint.y();
        Vector2dd candP = {curX, curY};
        if ((curPoint - candP).getLengthStable() < EPSIL) {
            listOfPoints.erase(it);
            return {entData.endPoint.x(), entData.endPoint.y()};
        }
    }
}

std::vector<Polygon> loadPolygonsDXF(const std::string name) {
    double EPSIL =  0.0001;
    std::vector<Polygon> polygons {};
    DxfBuilder builder;
    DxfLoader loader(builder);
    loader.load(name);
    auto layerEntitties = builder.layerEntities;
    for (auto &layer : layerEntitties) {
        auto listOfEntitites = layer.second;
        auto prevSize = listOfEntitites.size();
        auto first = listOfEntitites.begin();
        while(!listOfEntitites.empty()) {
            auto firstPtr = dynamic_cast<DxfLineEntity*>(*first);
            Polygon p {};
            auto entData = ((DxfLineData)(firstPtr->data));
            double firstX = entData.startPoint.x();
            double firstY = entData.startPoint.y();
            Vector2dd firstPoint = {firstX, firstY};
            p.push_back(firstPoint);

            double curX = entData.endPoint.x();
            double curY = entData.endPoint.y();
            Vector2dd curPoint = {curX, curY};
            listOfEntitites.erase(first);

            first = listOfEntitites.begin();
            if (auto firstPtr = dynamic_cast<DxfLineEntity*>(*first)) {
                while((curPoint - firstPoint).getLengthStable() > EPSIL) {
                    p.push_back(curPoint);
                    curPoint = getNextPoint(listOfEntitites, curPoint);
                }
                if (!listOfEntitites.empty())
                    first = listOfEntitites.begin();

                if (prevSize == listOfEntitites.size())
                    break;
                polygons.push_back(p);
                prevSize = listOfEntitites.size();
            }
        }
    }
    return polygons;
}

static void addPolygonsFromSVGShape(SvgShape* sh, std::vector<Polygon>& polygons) {
    if (sh->type == 2) {
        polygons.push_back(((SvgPolygon*)sh)->polygon);
    } else if (sh->type == 7) {
        for (auto s : ((SvgGroup*)sh)->shapes) {
            addPolygonsFromSVGShape(s, polygons);
        }
    }
}

vector<Polygon> loadPolygonsSVG(const std::string name) {
    using namespace std;
    vector<Polygon> polygons {};
    std::ifstream proxi(name, std::ifstream::binary);
    SvgFile svgFile;
    SvgLoader loader;
    loader.loadSvg(proxi, svgFile);
    for (auto sh : svgFile.shapes) {
        addPolygonsFromSVGShape(sh, polygons);
    }
    return polygons;
}

Polygon polFromRec(const Rectangled &R) { //rectangled is RO and corner is ll one, legacy code
    return {R.ulCorner(), R.llCorner(), R.lrCorner(), R.urCorner()};
}

double getTop(const vector<Polygon> &inputList) {
    double max = 0;
    for (auto &p : inputList) {
        if (getTopRightVertex(p).y() > max) {
            max = getTopRightVertex(p).y();
        }
    }
}
} // end of namespace corecvs
