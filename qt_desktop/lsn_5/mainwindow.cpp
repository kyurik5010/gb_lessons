#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mytexteditor.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MyTextEditor* textEditor_wgt = new MyTextEditor(this);

    setCentralWidget(textEditor_wgt);
}

MainWindow::~MainWindow()
{
    delete ui;
}

