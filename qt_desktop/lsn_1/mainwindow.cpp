#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QtMath>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//____________________________Задание 1________________________________

int MainWindow::compute_discriminant(int a, int b, int c)
{
    int result = (qPow(b, 2) - (4*a*c));
    return result;
}

QString MainWindow::compute_equasion(int a, int b, int c)
{
    int d = compute_discriminant(a, b, c);
    QString res;
    if (a == 0)
    {
        if (b != 0)
        {
            res = "Уравнение линейное, х = " + QString::number(-1. * c / b);
        }
        else if (c == 0)
        {
            res = "x - любое число.";
        }
        else
        {
            res = "Нет решений.";
        }
    }
    else
    {
        if(d > 0)
        {
            res = "Два корня: " + QString::number((-b + qSqrt(d)) / (2 * a)) + " и " + QString::number((-b - qSqrt(d)) / (2 * a));
        }
        else if(d < 0)
        {
            res = "Корней нет";
        }
        else
        {
            res = "Корень: " + QString::number(-b / (a * 2));
        }
    }
    return res;
}

void MainWindow::on_tsk1_compute_clicked()
{
    int a, b, c;
    a = ui->tsk1_a_TB->text().toInt();
    b = ui->tsk1_b_TB->text().toInt();
    c = ui->tsk1_c_TB->text().toInt();

   QString result = compute_equasion(a, b, c);

   ui->tsk1_result_TB->setText(result);

}


//____________________________Задание 2________________________________

void MainWindow::on_tsk2_compute_clicked()
{
    double x = ui->tsk2_angle_TB->text().toDouble();
    int a = ui->tsk2_A_TB->text().toInt();
    int b = ui->tsk2_B_TB->text().toInt();
    if(ui->tsk2_deg_RB_2->isChecked()) // если включены радианы - перевести в градусы (1 радиана == 57.2958 градусов)
    {
        x *= 57.2958;
        std::cout << "Угол в градусах: " << x << std::endl;
    }

    double c = qSqrt((a*a) + (b*b) - (2*a*b) * qCos(x));

    std::cout << "Результат: " << c << std::endl;
    ui->tsk2_res_TB->setText(QString::number(c, 'g', 2));

}

