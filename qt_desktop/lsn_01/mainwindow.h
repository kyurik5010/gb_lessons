#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int compute_discriminant(int a, int b, int c);

    QString compute_equasion(int a, int b, int c);


private slots:
    void on_tsk1_compute_clicked();

    void on_tsk2_compute_clicked();

    void on_tsk3_add_clicked();

    void on_tsk3_copy_clicked();

    void on_tsk3_random_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
