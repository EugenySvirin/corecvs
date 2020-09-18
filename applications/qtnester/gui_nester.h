#ifndef GUI_NESTER_H
#define GUI_NESTER_H
#include "core/buffers/rgb24/rgbTBuffer.h"
#include "core/buffers/g12Buffer.h"
#include "core/buffers/converters/debayer.h"
#include "core/fileformats/svgLoader.h"
#include <list>
#include <QDialog>

using namespace corecvs;
namespace Ui {
class GUI_nester;
}

class GUI_nester : public QDialog
{
    Q_OBJECT
        MetaData meta;
        G12Buffer *bayer;
        SvgFile* svgFileP = nullptr;
        SvgLoader svgLoader;
        std::list<Polygon> inputPolygons;
    public:
        Rectangled area = Rectangled(0, 0, 300, 300);
        double indentSize = 0;
        size_t rotationsAmount = 4;

    public:
        explicit GUI_nester(QWidget *parent = nullptr);
        ~GUI_nester();

private slots:
    void on_Load_clicked();

    void on_Save_as_released();

    void on_Run_nest_released();

    void on_Rotations_textChanged();

    void on_Indent_textChanged();

    void on_Height_textChanged();

    void on_Width_textChanged();

private:
    Ui::GUI_nester *ui;
};

#endif // GUI_NESTER_H
