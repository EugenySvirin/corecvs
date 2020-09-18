#include <list>
#include <QPixmap>
#include <QMessageBox>
#include <QFileDialog>
#include <QDialog>
#include "pointListEditImageWidget.h"
#include "core/buffers/bufferFactory.h"
#include "core/buffers/rgb24/rgb24Buffer.h"
#include "core/buffers/converters/debayer.h"
#include "core/fileformats/ppmLoader.h"
#include "utils/corestructs/g12Image.h"
#include "nester.h"
#include "core/buffers/rgb24/rgb24Buffer.h"
#include "core/fileformats/svgLoader.h"
#include "gui_nester.h"
#include "ui_gui_nester.h"
#include "core/buffers/rgb24/rgb24Buffer.h"
#include "core/fileformats/svgLoader.h"

GUI_nester::GUI_nester(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GUI_nester)
{
    ui->setupUi(this);
}

GUI_nester::~GUI_nester() {
    delete ui;
}

void GUI_nester::on_Load_clicked() {
    BufferFactory::getInstance()->printCaps();
    QString name = QFileDialog::getOpenFileName(this, "Open file");
    if (name.isEmpty())
        return;
    if (name.endsWith(".svg")) {
        inputPolygons = loadPolygonListSVG(name.toStdString());
    } else if (name.endsWith("dxf")) {
        inputPolygons = loadPolygonListDXF(name.toStdString());
    }
    QPixmap picture1(name);
    ui->pic1->setPixmap(picture1.scaled(ui->pic1->height(), ui->pic1->width(), Qt::KeepAspectRatio));
}

void GUI_nester::on_Save_as_released() {
    QString name = QFileDialog::getSaveFileName(this, "save as");
    std::list<Polygon> inputPolygonsWithArea = inputPolygons;
    inputPolygonsWithArea.push_back(polFromRec(area));
    drawSvgPolygons(inputPolygonsWithArea, area.height(), area.width(), name.toStdString());
}

void GUI_nester::on_Run_nest_released() {
    if (!inputPolygons.empty()) {
        auto processingPolygons = inputPolygons;
        vinilPlacementNester(processingPolygons, area, indentSize, 1, 1, 0.2, rotationsAmount);
        processingPolygons.push_back(polFromRec(area));
        drawSvgPolygons(processingPolygons, area.height(), area.width(), "clicked.svg");
        QPixmap picture2("clicked.svg");
        ui->pic2->setPixmap(picture2.scaled(ui->pic1->height(), ui->pic1->width(), Qt::KeepAspectRatio));
        double verticalFullness = getMaxValueY(inputPolygons) / area.height();
        cout << verticalFullness;
        ui->Verctical_fullness->setPlainText(QString::number(verticalFullness));
    }
}

void GUI_nester::on_Rotations_textChanged() {
    rotationsAmount = ui->Rotations->toPlainText().toInt();
}

void GUI_nester::on_Indent_textChanged() {
     indentSize = ui->Indent->toPlainText().toDouble();
}

void GUI_nester::on_Height_textChanged() {
    area =  {area.corner.x(), area.corner.y(),
             ui->Width->toPlainText().toDouble(),
             ui->Height->toPlainText().toDouble()};
}

void GUI_nester::on_Width_textChanged() {
    area =  {area.corner.x(), area.corner.y(),
             ui->Width->toPlainText().toDouble(),
             ui->Height->toPlainText().toDouble()};
}
