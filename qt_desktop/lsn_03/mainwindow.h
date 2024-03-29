#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDir>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_tsk1_open_clicked();

    void on_tsk1_save_clicked();

    void on_tsk2_parse_clicked();

    void on_tsk2_open_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
