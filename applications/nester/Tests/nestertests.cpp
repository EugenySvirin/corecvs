#include <vector>
#include <NesterCore/convexpolygonnester.h>
#include <LegacyCode/nester.h>
namespace corecvs {
template<typename T1, typename T2>
static void putInConteiner(T1& conteiner, const T2& obj, int amount) {
    for (int i = 0; i < amount; ++i) {
        conteiner.push_back(obj);
    }
}

static double getMaxValueY(const vector<corecvs::Polygon> &inputList) {
    double max = 0;
    for (auto &p : inputList) {
        if (max < getTopRightVertex(p).y()) {
            max = getTopRightVertex(p).y();
        }
    }
    return max;
}

void runTest(string filename, vector<Polygon>& polygons,
             Rectangled bin) {
     using namespace std;
     ConvexPolygonNester nester;
     nester.setBin(bin);
     nester.setInputPolygons(polygons);

     nester.run_FFD_LM_BLPR(16);
     auto placedPolygons = nester.getPlacedPolygons();
     cout << filename + " FFD_LM_BLPR16 value:" << getMaxValueY(placedPolygons) / bin.height() << endl;
     placedPolygons.push_back(polFromRec(bin));
     drawSvgPolygons(placedPolygons, bin.height(), bin.width(), filename + " FFD_LM_BLPR16.svg");


     nester.run_FFD_LM_BLPR(32);
     placedPolygons = nester.getPlacedPolygons();
     cout << filename + " FFD_LM_BLPR32 value:" <<getMaxValueY(placedPolygons) / bin.height()  << endl;
     placedPolygons.push_back(polFromRec(bin));
     drawSvgPolygons(placedPolygons, bin.height(), bin.width(), filename + " FFD_LM_BLPR32.svg");


     nester.run_FFD_LM_BLPR_H(4);
     placedPolygons = nester.getPlacedPolygons();
     cout << filename + " FFD_LM_BLPR_H16 value:" << (getMaxValueY(placedPolygons) - bin.corner.y())/ bin.height()  << endl;
     placedPolygons.push_back(polFromRec(bin));
     drawSvgPolygons(placedPolygons, 20 + bin.height(), 20 + bin.width(), filename + " FFD_LM_BLPR_H16.svg");

     nester.run_FFD_LM_BLPR_H(32);
     placedPolygons = nester.getPlacedPolygons();
     cout << filename + " FFD_LM_BLPR_H32 value:" <<getMaxValueY(placedPolygons) / bin.height()  << endl;
     placedPolygons.push_back(polFromRec(bin));
     drawSvgPolygons(placedPolygons, bin.height(), bin.width(), filename + " FFD_LM_BLPR_H32.svg");

     nester.run_FFD_LM_BLPR_M(4);
     placedPolygons = nester.getPlacedPolygons();
     cout << filename + " FFD_LM_BLPR_M16 value:" << (getMaxValueY(placedPolygons) - bin.corner.y()) / bin.height() << endl;
     placedPolygons.push_back(polFromRec(bin));
     drawSvgPolygons(placedPolygons, 20 + bin.height(), 20 + bin.width(), filename + " FFD_LM_BLPR_M16.svg");

     nester.run_FFD_LM_BLPR_M(32);
     placedPolygons = nester.getPlacedPolygons();
     cout << filename + " FFD_LM_BLPR_M32 value:" <<getMaxValueY(placedPolygons) / bin.height()  << endl;
     drawSvgPolygons(placedPolygons, bin.height(), bin.width(), filename + " FFD_LM_BLPR_M32.svg");
     placedPolygons.push_back(polFromRec(bin));


     nester.run_FFD_LVM_BLPR_H(16);
     placedPolygons = nester.getPlacedPolygons();
     cout << filename + " FFD_LVM_BLPR_H16 value:" <<getMaxValueY(placedPolygons) / bin.height()  << endl;
     placedPolygons.push_back(polFromRec(bin));
     drawSvgPolygons(placedPolygons, bin.height(), bin.width(), filename + " FFD_LVM_BLPR_H16.svg");


     nester.run_FFD_LVM_BLPR_H(32);
     placedPolygons = nester.getPlacedPolygons();
     cout << filename + " FFD_LVM_BLPR_H32 value:" <<getMaxValueY(placedPolygons) / bin.height() << endl;
     placedPolygons.push_back(polFromRec(bin));
     drawSvgPolygons(placedPolygons, bin.height(), bin.width(), filename + " FFD_LVM_BLPR_H32.svg");
     cout << endl << endl;
}

void RunTests() {
    using namespace std;
    Vector2dd point1(-2, 3);
    Vector2dd point2(-2, 1);
    Vector2dd point3(0, 1.5);
    Vector2dd point4(0, 2);

    Vector2dd point5(-2, 1);
    Vector2dd point6(-2, -1);
    Vector2dd point7(-1, -2);
    Vector2dd point8(1, -2);
    Vector2dd point9(5, -0.5);
    Vector2dd point10(5, 0.5);
    Vector2dd point11(1, 2);
    Vector2dd point12(-1, 2);

    Vector2dd point13(0, 0);
    Vector2dd point14(0, 100);
    Vector2dd point15(150, 100);
    Vector2dd point16(150, 0);

    Vector2dd point17(0, 0);
    Vector2dd point18(5, 1.5);
    Vector2dd point19(6.5, 0);

    Vector2dd point20(0, 0);
    Vector2dd point21(0, 5.4);
    Vector2dd point22(7.8, 5.4);
    Vector2dd point23(7.8, 0);

    Polygon rectanglePN1 {point13, point14, point15, point16};

    Polygon eightanglePN2 {point5, point6, point7, point8, point9, point10, point11, point12};
    Polygon trapetsiaPN2 {point1, point2, point3, point4};
    Polygon sixteenRPN2 = Polygon::RegularPolygon(16, Vector2dd::Zero(), 2.51, 0);

    Polygon trianglePN3 {point17, point18, point19};
    Polygon rectanglePN3 {point20, point21, point22, point23};

    trapetsiaPN2 = getHomotheticPolygon(trapetsiaPN2, 62.5);
    sixteenRPN2 = getHomotheticPolygon(sixteenRPN2, 40);
    eightanglePN2 = getHomotheticPolygon(eightanglePN2, 14.7);


    trianglePN3 = getHomotheticPolygon(trianglePN3, 19);
    rectanglePN3 = getHomotheticPolygon(rectanglePN3, 19);

    vector<Polygon> ProNest1;
    putInConteiner(ProNest1, rectanglePN1, 61);
    Rectangled areaPN1(0, 0, 750, 1500);

    vector<Polygon> ProNest2;
    putInConteiner(ProNest2, trapetsiaPN2, 30);
    putInConteiner(ProNest2, sixteenRPN2, 10);
    putInConteiner(ProNest2, eightanglePN2 , 46);
    Rectangled areaPN2(0, 0, 750, 2250);

    vector<Polygon> ProNest3;
    putInConteiner(ProNest3, rectanglePN3, 49);//49
    putInConteiner(ProNest3, trapetsiaPN2, 20);//32
    putInConteiner(ProNest3, trianglePN3, 20);//57
    Rectangled areaPN3(0, 0, 750, 1500);

    Polygon urod1 = {{0, 0}, {0, 5}, {3, 2}, {2, 0}};
    Polygon urod2 = {{0, 0}, {2, 2}, {4, 1}, {5, 0}};
    Polygon urod3 = {{0, 0}, {1, 4}, {5, 5}, {6 , 3}, {6 ,1}, {3, 0}};
    Polygon urod4 = {{0, 0}, {1, 2}, {6, 7}, {4, 2}, {3, 1}};
    Polygon urodishe1 = getHomotheticPolygon(urod1, 2);
    Polygon urodishe2 = getHomotheticPolygon(urod2, 2);
    Polygon urodishe3 = getHomotheticPolygon(urod3, 2);
    Polygon urodishe4 = getHomotheticPolygon(urod4, 2);

    Polygon triangleR = Polygon::RegularPolygon(3, Vector2dd::Zero(), 12, 0);
    Polygon quad = Polygon::RegularPolygon(4, Vector2dd::Zero(), 10, 0);
    Polygon pentaR = Polygon::RegularPolygon(5, Vector2dd::Zero(), 10, 0);
    Polygon geksaR = Polygon::RegularPolygon(5, Vector2dd::Zero(), 10, 0);

    Polygon longRectangler = {{0, 0}, {0, 5}, {20, 5}, {20, 0}};
    Polygon simpleRectangler = {{0, 0}, {0, 7}, {15, 7}, {15, 0}};

    Polygon triangle1 = {{0, 0}, {0 , 6}, {10, 0}};
    Polygon triangle2 = {{0, 0}, {2 , 10}, {4, 0}};
    Polygon triangle3 = {{0, 0}, {2 , 8}, {8, 0}};
    Polygon smallTriangle1 = getHomotheticPolygon(triangle1, 0.25);
    Polygon smallTriangle2 = getHomotheticPolygon(triangle2, -2);
    Polygon smallTriangle3 = getHomotheticPolygon(triangle2, -2);

    Polygon A {{10, 0}, {0, -10}, {-10, 0}, {0, 10}};
    Polygon B {{0, 0}, {10, 20}, {20, 0}};
    Polygon C {{0, 0}, {3.5, 2.5}, {4, 0}};

    Rectangled area1 (10, 10, 135, 75);
    Rectangled area2 (10, 10, 105, 105);

    vector<Polygon> inputList1;
    putInConteiner(inputList1, triangle1, 20);
    putInConteiner(inputList1, triangle2, 30);
    putInConteiner(inputList1, triangle3, 30);
    putInConteiner(inputList1, quad, 10);
    putInConteiner(inputList1, urod1, 10);
    putInConteiner(inputList1, smallTriangle1, 20);

    vector<Polygon> inputList2;
    //putInConteiner(inputList2, smallTriangle1, 20);
    putInConteiner(inputList2, getHomotheticPolygon(urod1, 2.5), 10);
    putInConteiner(inputList2, quad, 10);
    putInConteiner(inputList2, triangleR, 15);

    vector<Polygon> inputList3;
    putInConteiner(inputList3, smallTriangle1, 8);
    putInConteiner(inputList3, urodishe3, 8);
    putInConteiner(inputList3, urodishe2, 9);
    putInConteiner(inputList3, getHomotheticPolygon(urodishe1, 2.5), 10);

    vector<Polygon> inputList4;
    putInConteiner(inputList4, quad, 8);
    putInConteiner(inputList4, getHomotheticPolygon(urod4, 2.5), 8);
    putInConteiner(inputList4, smallTriangle1, 9);
    putInConteiner(inputList4, smallTriangle2, 10);

    vector<Polygon> inputList5;
    putInConteiner(inputList5, getHomotheticPolygon(urod1, 2.5) , 8);
    putInConteiner(inputList5, getHomotheticPolygon(urod2, 2.5), 8);
    putInConteiner(inputList5, getHomotheticPolygon(urod3, 2.5), 9);
    putInConteiner(inputList5, getHomotheticPolygon(urodishe1, 2.5), 5);

    vector<Polygon> inputList6;
    putInConteiner(inputList6, getHomotheticPolygon(urodishe1, 1.5), 8);
    putInConteiner(inputList6, getHomotheticPolygon(urodishe2, 1.5), 8);
    putInConteiner(inputList6, getHomotheticPolygon(urodishe3, 1.5), 9);
    putInConteiner(inputList6, getHomotheticPolygon(urodishe4, 1.5), 10);
    runTest("testPronest1", ProNest1, areaPN1);
    runTest("testPronest2", ProNest2, areaPN2);
    runTest("testPronest3", ProNest3, areaPN3);
    runTest("test5", inputList1, area2);
    runTest("test6", inputList2, area2);
    runTest("test7", inputList3, area1);
    runTest("test8", inputList4, area1);
    runTest("test9", inputList5, area1);

    runTest("test10", inputList6, area1);
}
} //namespace cvs
