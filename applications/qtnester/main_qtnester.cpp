/**
 * \file main_qt_recorder.cpp
 * \brief Entry point for the recorder application
 *
 * \date Sep 17, 2010
 * \author Sergey Levi
 */

#include <string>
#include <iostream>
#include "nester.h"
#include <QtGui/QtGui>
#include <QApplication>

#include "core/utils/global.h"

#include "core/utils/utils.h"
#include "qtFileLoader.h"
//#include "imageViewMainWindow.h"
#include "gui_nester.h"
int main(int argc, char *argv[])
{
    SET_HANDLERS();

    Q_INIT_RESOURCE(main);

    SYNC_PRINT(("Starting ImageView...\n"));

    QApplication app(argc, argv);
    GUI_nester mainWindow;
    QTG12Loader::registerMyself();
    QTRGB24Loader::registerMyself();
    mainWindow.show();
    app.exec();
    SYNC_PRINT(("Exiting ImageView application...\n"));
}
