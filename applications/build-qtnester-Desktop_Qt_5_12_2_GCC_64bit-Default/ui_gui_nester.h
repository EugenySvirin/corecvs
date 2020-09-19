/********************************************************************************
** Form generated from reading UI file 'gui_nester.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI_NESTER_H
#define UI_GUI_NESTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_GUI_nester
{
public:
    QPushButton *Load;
    QPushButton *Save_as;
    QLabel *pic1;
    QLabel *pic2;
    QPushButton *Run_nest;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QTextEdit *Height;
    QTextEdit *Width;
    QTextEdit *Rotations;
    QTextEdit *Indent;
    QTextEdit *Verctical_fullness;

    void setupUi(QDialog *GUI_nester)
    {
        if (GUI_nester->objectName().isEmpty())
            GUI_nester->setObjectName(QString::fromUtf8("GUI_nester"));
        GUI_nester->resize(1213, 649);
        Load = new QPushButton(GUI_nester);
        Load->setObjectName(QString::fromUtf8("Load"));
        Load->setGeometry(QRect(1010, 10, 89, 25));
        Save_as = new QPushButton(GUI_nester);
        Save_as->setObjectName(QString::fromUtf8("Save_as"));
        Save_as->setGeometry(QRect(1110, 10, 89, 25));
        pic1 = new QLabel(GUI_nester);
        pic1->setObjectName(QString::fromUtf8("pic1"));
        pic1->setGeometry(QRect(50, 130, 551, 471));
        pic2 = new QLabel(GUI_nester);
        pic2->setObjectName(QString::fromUtf8("pic2"));
        pic2->setGeometry(QRect(620, 130, 541, 471));
        Run_nest = new QPushButton(GUI_nester);
        Run_nest->setObjectName(QString::fromUtf8("Run_nest"));
        Run_nest->setGeometry(QRect(10, 10, 89, 25));
        label = new QLabel(GUI_nester);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(130, 10, 111, 17));
        label_2 = new QLabel(GUI_nester);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(630, 10, 67, 17));
        label_3 = new QLabel(GUI_nester);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(710, 10, 67, 17));
        label_4 = new QLabel(GUI_nester);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(820, 10, 67, 17));
        label_5 = new QLabel(GUI_nester);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(920, 10, 67, 17));
        Height = new QTextEdit(GUI_nester);
        Height->setObjectName(QString::fromUtf8("Height"));
        Height->setGeometry(QRect(610, 30, 91, 31));
        Width = new QTextEdit(GUI_nester);
        Width->setObjectName(QString::fromUtf8("Width"));
        Width->setGeometry(QRect(700, 30, 91, 31));
        Rotations = new QTextEdit(GUI_nester);
        Rotations->setObjectName(QString::fromUtf8("Rotations"));
        Rotations->setGeometry(QRect(810, 30, 91, 31));
        Indent = new QTextEdit(GUI_nester);
        Indent->setObjectName(QString::fromUtf8("Indent"));
        Indent->setGeometry(QRect(900, 30, 91, 31));
        Verctical_fullness = new QTextEdit(GUI_nester);
        Verctical_fullness->setObjectName(QString::fromUtf8("Verctical_fullness"));
        Verctical_fullness->setGeometry(QRect(130, 30, 111, 31));

        retranslateUi(GUI_nester);
        QObject::connect(Rotations, SIGNAL(windowIconTextChanged(QString)), GUI_nester, SLOT(on_Rotations_windowIconTextChanged(QString)));

        QMetaObject::connectSlotsByName(GUI_nester);
    } // setupUi

    void retranslateUi(QDialog *GUI_nester)
    {
        GUI_nester->setWindowTitle(QApplication::translate("GUI_nester", "Dialog", nullptr));
        Load->setText(QApplication::translate("GUI_nester", "Load", nullptr));
        Save_as->setText(QApplication::translate("GUI_nester", "Save as", nullptr));
        pic1->setText(QString());
        pic2->setText(QString());
        Run_nest->setText(QApplication::translate("GUI_nester", "Run nest", nullptr));
        label->setText(QApplication::translate("GUI_nester", "Vertical fullness", nullptr));
        label_2->setText(QApplication::translate("GUI_nester", "Height", nullptr));
        label_3->setText(QApplication::translate("GUI_nester", "    Width", nullptr));
        label_4->setText(QApplication::translate("GUI_nester", "Rotations", nullptr));
        label_5->setText(QApplication::translate("GUI_nester", "Indent", nullptr));
        Height->setHtml(QApplication::translate("GUI_nester", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">300</p></body></html>", nullptr));
        Width->setHtml(QApplication::translate("GUI_nester", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">300</p></body></html>", nullptr));
        Rotations->setHtml(QApplication::translate("GUI_nester", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">4</p></body></html>", nullptr));
        Indent->setHtml(QApplication::translate("GUI_nester", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"> 0</p></body></html>", nullptr));
        Verctical_fullness->setHtml(QApplication::translate("GUI_nester", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">0</p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GUI_nester: public Ui_GUI_nester {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_NESTER_H
