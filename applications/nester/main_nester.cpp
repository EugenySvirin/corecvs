#include <fstream>
#include <list>

#include "core/utils/utils.h"
#include "core/buffers/rgb24/abstractPainter.h"
#include "core/buffers/rgb24/rgb24Buffer.h"
#include "core/buffers/bufferFactory.h"
#include "core/fileformats/svgLoader.h"
#include "core/reflection/commandLineSetter.h"
#include "core/fileformats/dxf_support/dxfLoader.h"
#include <algorithm>
#include "NesterCore/convexpolygonnester.h"
#include "nesterhelpfulmethods.h"
#include "Tests/NesterTests.h"
using namespace corecvs;
using namespace std;

template <typename T>
void printCont(T cont) {
    for (auto &p : cont) {
        std :: cout << p << ' ';
    }
    std :: cout << endl;
}

int main(int argc, char **argv) {
    RunTests();
}
