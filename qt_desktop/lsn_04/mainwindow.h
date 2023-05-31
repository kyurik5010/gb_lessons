#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
//#include <QDir>
#include <QDebug>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void keyPressEvent(QKeyEvent *event) override;

signals:
    void open();

    void save();

    void create_new();

    void exit();

private slots:
    void on_tsk1_open_clicked();

    void on_tsk1_save_clicked();

    void open_document();

    void save_as();

    void create_new_document();

    void exit_program();


private:
    Ui::MainWindow *ui;
    QString cur_path; // для быстрого сохранения без 'save as'
};
#endif // MAINWINDOW_H
