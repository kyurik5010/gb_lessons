#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QStringListModel>
#include <QItemSelectionModel>
#include <QHeaderView>
#include "textparser.h"

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
    void on_tsk1_TB_textChanged();


    void on_tsk2_checkBox_stateChanged();

    void on_tsk2_pushButton_clicked();

    void on_tsk2_pushButton_2_clicked();

    void on_tsk3_pushButton_clicked();

private:
    TextParser parser;
    Ui::MainWindow *ui;
    QStandardItemModel *model;
    QStringListModel *model2;
    QItemSelectionModel *selectionModel;
};
#endif // MAINWINDOW_H
