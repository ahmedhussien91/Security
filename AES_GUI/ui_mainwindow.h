/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionExit;
    QWidget *centralwidget;
    QPushButton *Encrypt_Button;
    QPushButton *Decrypt_Button;
    QPushButton *Input_button;
    QLabel *label;
    QLineEdit *InLine;
    QLabel *label_2;
    QLineEdit *OutLine;
    QPushButton *OutBrowse;
    QComboBox *SizeCombo;
    QFrame *line;
    QFrame *line_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QComboBox *comboBox;
    QLabel *label_6;
    QTextEdit *KeyLine;
    QCheckBox *RFCcheckBox;
    QMenuBar *menubar;
    QMenu *menufile;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        Encrypt_Button = new QPushButton(centralwidget);
        Encrypt_Button->setObjectName(QString::fromUtf8("Encrypt_Button"));
        Encrypt_Button->setGeometry(QRect(590, 370, 171, 61));
        Decrypt_Button = new QPushButton(centralwidget);
        Decrypt_Button->setObjectName(QString::fromUtf8("Decrypt_Button"));
        Decrypt_Button->setGeometry(QRect(590, 440, 171, 61));
        Input_button = new QPushButton(centralwidget);
        Input_button->setObjectName(QString::fromUtf8("Input_button"));
        Input_button->setGeometry(QRect(420, 90, 93, 28));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 90, 101, 21));
        QFont font;
        font.setPointSize(10);
        label->setFont(font);
        InLine = new QLineEdit(centralwidget);
        InLine->setObjectName(QString::fromUtf8("InLine"));
        InLine->setGeometry(QRect(110, 90, 271, 22));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 130, 91, 20));
        label_2->setFont(font);
        OutLine = new QLineEdit(centralwidget);
        OutLine->setObjectName(QString::fromUtf8("OutLine"));
        OutLine->setGeometry(QRect(110, 130, 271, 22));
        OutBrowse = new QPushButton(centralwidget);
        OutBrowse->setObjectName(QString::fromUtf8("OutBrowse"));
        OutBrowse->setGeometry(QRect(420, 130, 93, 28));
        SizeCombo = new QComboBox(centralwidget);
        SizeCombo->addItem(QString());
        SizeCombo->addItem(QString());
        SizeCombo->addItem(QString());
        SizeCombo->setObjectName(QString::fromUtf8("SizeCombo"));
        SizeCombo->setGeometry(QRect(110, 350, 73, 22));
        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(20, 260, 741, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(centralwidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(490, 290, 16, 231));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 290, 151, 31));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        label_3->setFont(font1);
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(30, 350, 55, 16));
        QFont font2;
        font2.setPointSize(9);
        label_4->setFont(font2);
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(30, 390, 55, 16));
        label_5->setFont(font2);
        comboBox = new QComboBox(centralwidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(110, 390, 73, 22));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 170, 91, 20));
        label_6->setFont(font);
        KeyLine = new QTextEdit(centralwidget);
        KeyLine->setObjectName(QString::fromUtf8("KeyLine"));
        KeyLine->setGeometry(QRect(110, 170, 271, 51));
        RFCcheckBox = new QCheckBox(centralwidget);
        RFCcheckBox->setObjectName(QString::fromUtf8("RFCcheckBox"));
        RFCcheckBox->setEnabled(true);
        RFCcheckBox->setGeometry(QRect(30, 430, 141, 20));
        RFCcheckBox->setChecked(false);
        RFCcheckBox->setTristate(false);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        menufile = new QMenu(menubar);
        menufile->setObjectName(QString::fromUtf8("menufile"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menufile->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menufile->addSeparator();
        menufile->addAction(actionExit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        Encrypt_Button->setText(QCoreApplication::translate("MainWindow", "Encrypt", nullptr));
        Decrypt_Button->setText(QCoreApplication::translate("MainWindow", "Decrypt", nullptr));
        Input_button->setText(QCoreApplication::translate("MainWindow", "Browse", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Input File", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Output File", nullptr));
        OutBrowse->setText(QCoreApplication::translate("MainWindow", "Browse", nullptr));
        SizeCombo->setItemText(0, QCoreApplication::translate("MainWindow", "128", nullptr));
        SizeCombo->setItemText(1, QCoreApplication::translate("MainWindow", "192", nullptr));
        SizeCombo->setItemText(2, QCoreApplication::translate("MainWindow", "256", nullptr));

        label_3->setText(QCoreApplication::translate("MainWindow", "Configurations", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "AES Size", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Mode", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "CBC", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "ECB", nullptr));

        label_6->setText(QCoreApplication::translate("MainWindow", "Key", nullptr));
        RFCcheckBox->setText(QCoreApplication::translate("MainWindow", " RFC 5652", nullptr));
        menufile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("MainWindow", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
