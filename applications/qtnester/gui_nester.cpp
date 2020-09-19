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
#include "core/buffers/rgb24/rgb24Buffer.h"
#include "core/fileformats/svgLoader.h"
#include "gui_nester.h"
#include "ui_gui_nester.h"
#include "core/buffers/rgb24/rgb24Buffer.h"
#include "core/fileformats/svgLoader.h"
#include "NesterCore/convexpolygonnester.h"
#include "nesterhelpfulmethods.h"

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
        nester.setInputPolygons(loadPolygonsSVG(name.toStdString()));
    } else if (name.endsWith("dxf")) {
         nester.setInputPolygons(loadPolygonsDXF(name.toStdString()));
    }
    QPixmap picture1(name);
    ui->pic1->setPixmap(picture1.scaled(ui->pic1->height(), ui->pic1->width(), Qt::KeepAspectRatio));
}

void GUI_nester::on_Save_as_released() {
    QString name = QFileDialog::getSaveFileName(this, "save as");
    auto result = nester.getPlacedPolygons();
    result.push_back(polFromRec(area));
    drawSvgPolygons(result, area.height(), area.width(), name.toStdString());
}

void GUI_nester::on_Run_nest_released() {
    if (!nester.getInputPolygons().empty()) { //add new method
        nester.setBin(area);                        //add up these
        nester.run_FFD_LVM_BLPR_H(rotationsAmount); //two methods
        auto result = nester.getPlacedPolygons();
        double verticalFullness = getTop(result)/area.height(); // rewrite
        ui->Verctical_fullness->setPlainText(QString::number(verticalFullness));
        result.push_back(polFromRec(area));
        drawSvgPolygons(result, area.height(), area.width(), "clicked.svg");
        QPixmap picture2("clicked.svg");
        ui->pic2->setPixmap(picture2.scaled(ui->pic1->height(), ui->pic1->width(), Qt::KeepAspectRatio));
    }
}

void GUI_nester::on_Rotations_textChanged() {
    rotationsAmount = ui->Rotations->toPlainText().toInt();
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
