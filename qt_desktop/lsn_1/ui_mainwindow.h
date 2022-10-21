/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QFrame *line;
    QFrame *line_2;
    QLabel *tsk1_label;
    QLabel *tsk2_label;
    QLabel *tsk3_label;
    QLabel *tsk1_label_1;
    QLineEdit *tsk1_a_TB;
    QLineEdit *tsk1_b_TB;
    QLineEdit *tsk1_c_TB;
    QLineEdit *tsk1_result_TB;
    QLabel *tsk1_label_2;
    QPushButton *tsk1_compute;
    QLabel *tsk1_label_3;
    QFrame *tsk2_line_2;
    QFrame *tsk2_line_1;
    QLabel *tsk2_label_1;
    QLabel *tsk2_label_2;
    QLineEdit *tsk2_A_TB;
    QLineEdit *tsk2_B_TB;
    QLineEdit *tsk2_angle_TB;
    QLabel *tsk2_label_3;
    QRadioButton *tsk2_deg_RB;
    QRadioButton *tsk2_deg_RB_2;
    QPushButton *tsk2_compute;
    QLineEdit *tsk2_res_TB;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(839, 738);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        line = new QFrame(centralwidget);
        line->setObjectName("line");
        line->setGeometry(QRect(300, 0, 20, 341));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(centralwidget);
        line_2->setObjectName("line_2");
        line_2->setGeometry(QRect(-10, 330, 831, 20));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        tsk1_label = new QLabel(centralwidget);
        tsk1_label->setObjectName("tsk1_label");
        tsk1_label->setGeometry(QRect(110, 0, 61, 16));
        tsk2_label = new QLabel(centralwidget);
        tsk2_label->setObjectName("tsk2_label");
        tsk2_label->setGeometry(QRect(570, 0, 71, 16));
        tsk3_label = new QLabel(centralwidget);
        tsk3_label->setObjectName("tsk3_label");
        tsk3_label->setGeometry(QRect(360, 350, 71, 16));
        tsk1_label_1 = new QLabel(centralwidget);
        tsk1_label_1->setObjectName("tsk1_label_1");
        tsk1_label_1->setGeometry(QRect(30, 40, 201, 16));
        QFont font;
        font.setPointSize(18);
        tsk1_label_1->setFont(font);
        tsk1_a_TB = new QLineEdit(centralwidget);
        tsk1_a_TB->setObjectName("tsk1_a_TB");
        tsk1_a_TB->setGeometry(QRect(10, 39, 18, 21));
        tsk1_a_TB->setFont(font);
        tsk1_b_TB = new QLineEdit(centralwidget);
        tsk1_b_TB->setObjectName("tsk1_b_TB");
        tsk1_b_TB->setGeometry(QRect(64, 39, 18, 21));
        tsk1_b_TB->setFont(font);
        tsk1_c_TB = new QLineEdit(centralwidget);
        tsk1_c_TB->setObjectName("tsk1_c_TB");
        tsk1_c_TB->setGeometry(QRect(110, 39, 18, 21));
        tsk1_c_TB->setFont(font);
        tsk1_result_TB = new QLineEdit(centralwidget);
        tsk1_result_TB->setObjectName("tsk1_result_TB");
        tsk1_result_TB->setGeometry(QRect(10, 200, 291, 31));
        tsk1_result_TB->setFont(font);
        tsk1_label_2 = new QLabel(centralwidget);
        tsk1_label_2->setObjectName("tsk1_label_2");
        tsk1_label_2->setGeometry(QRect(12, 178, 91, 16));
        tsk1_label_2->setFont(font);
        tsk1_compute = new QPushButton(centralwidget);
        tsk1_compute->setObjectName("tsk1_compute");
        tsk1_compute->setGeometry(QRect(200, 120, 100, 41));
        QFont font1;
        font1.setPointSize(14);
        tsk1_compute->setFont(font1);
        tsk1_label_3 = new QLabel(centralwidget);
        tsk1_label_3->setObjectName("tsk1_label_3");
        tsk1_label_3->setGeometry(QRect(40, 31, 16, 16));
        tsk2_line_2 = new QFrame(centralwidget);
        tsk2_line_2->setObjectName("tsk2_line_2");
        tsk2_line_2->setGeometry(QRect(470, 180, 181, 20));
        tsk2_line_2->setSizeIncrement(QSize(10, 0));
        tsk2_line_2->setFrameShape(QFrame::HLine);
        tsk2_line_2->setFrameShadow(QFrame::Sunken);
        tsk2_line_1 = new QFrame(centralwidget);
        tsk2_line_1->setObjectName("tsk2_line_1");
        tsk2_line_1->setGeometry(QRect(460, 30, 20, 161));
        tsk2_line_1->setFrameShape(QFrame::VLine);
        tsk2_line_1->setFrameShadow(QFrame::Sunken);
        tsk2_label_1 = new QLabel(centralwidget);
        tsk2_label_1->setObjectName("tsk2_label_1");
        tsk2_label_1->setGeometry(QRect(363, 30, 91, 20));
        tsk2_label_2 = new QLabel(centralwidget);
        tsk2_label_2->setObjectName("tsk2_label_2");
        tsk2_label_2->setGeometry(QRect(580, 190, 91, 20));
        tsk2_A_TB = new QLineEdit(centralwidget);
        tsk2_A_TB->setObjectName("tsk2_A_TB");
        tsk2_A_TB->setGeometry(QRect(430, 30, 30, 21));
        tsk2_A_TB->setFont(font);
        tsk2_B_TB = new QLineEdit(centralwidget);
        tsk2_B_TB->setObjectName("tsk2_B_TB");
        tsk2_B_TB->setGeometry(QRect(650, 190, 30, 21));
        tsk2_B_TB->setFont(font);
        tsk2_angle_TB = new QLineEdit(centralwidget);
        tsk2_angle_TB->setObjectName("tsk2_angle_TB");
        tsk2_angle_TB->setGeometry(QRect(477, 163, 30, 21));
        tsk2_angle_TB->setFont(font);
        tsk2_label_3 = new QLabel(centralwidget);
        tsk2_label_3->setObjectName("tsk2_label_3");
        tsk2_label_3->setGeometry(QRect(510, 140, 91, 20));
        tsk2_deg_RB = new QRadioButton(centralwidget);
        tsk2_deg_RB->setObjectName("tsk2_deg_RB");
        tsk2_deg_RB->setGeometry(QRect(550, 120, 99, 20));
        QFont font2;
        font2.setItalic(true);
        tsk2_deg_RB->setFont(font2);
        tsk2_deg_RB->setChecked(true);
        tsk2_deg_RB_2 = new QRadioButton(centralwidget);
        tsk2_deg_RB_2->setObjectName("tsk2_deg_RB_2");
        tsk2_deg_RB_2->setGeometry(QRect(550, 140, 99, 20));
        tsk2_deg_RB_2->setFont(font2);
        tsk2_compute = new QPushButton(centralwidget);
        tsk2_compute->setObjectName("tsk2_compute");
        tsk2_compute->setGeometry(QRect(350, 220, 191, 32));
        tsk2_res_TB = new QLineEdit(centralwidget);
        tsk2_res_TB->setObjectName("tsk2_res_TB");
        tsk2_res_TB->setGeometry(QRect(350, 250, 113, 21));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 839, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Lesson_1", nullptr));
        tsk1_label->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\264\320\260\320\275\320\270\320\265 1", nullptr));
        tsk2_label->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\264\320\260\320\275\320\270\320\265 2", nullptr));
        tsk3_label->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\264\320\260\320\275\320\270\320\265 3", nullptr));
        tsk1_label_1->setText(QCoreApplication::translate("MainWindow", "x  +      x +       = 0", nullptr));
        tsk1_label_2->setText(QCoreApplication::translate("MainWindow", "\321\200\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202:", nullptr));
        tsk1_compute->setText(QCoreApplication::translate("MainWindow", "\320\262\321\213\321\207\320\270\321\201\320\273\320\270\321\202\321\214", nullptr));
        tsk1_label_3->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        tsk2_label_1->setText(QCoreApplication::translate("MainWindow", "\321\201\321\202\320\276\321\200\320\276\320\275\320\260 \320\220", nullptr));
        tsk2_label_2->setText(QCoreApplication::translate("MainWindow", "\321\201\321\202\320\276\321\200\320\276\320\275\320\260 \320\221", nullptr));
        tsk2_label_3->setText(QCoreApplication::translate("MainWindow", "\321\203\320\263\320\276\320\273", nullptr));
        tsk2_deg_RB->setText(QCoreApplication::translate("MainWindow", "\320\263\321\200\320\260\320\264\321\203\321\201\321\213", nullptr));
        tsk2_deg_RB_2->setText(QCoreApplication::translate("MainWindow", "\321\200\320\260\320\264\320\270\320\260\320\275\321\213", nullptr));
        tsk2_compute->setText(QCoreApplication::translate("MainWindow", "\321\200\320\260\321\201\321\201\321\207\320\270\321\202\320\260\321\202\321\214 \321\201\321\202\320\276\321\200\320\276\320\275\321\203 \320\222", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
