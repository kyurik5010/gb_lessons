#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QDebug>
#include <QKeyEvent>
#include <QAction>

//layouts
#include <QGridLayout>
#include <QHBoxLayout>
#include <QMessageBox>

//widgets
#include <QWidget>
#include <QLabel>
#include <QFileDialog>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QMenu>
#include <QPrintDialog>
#include <QPrinter>
#include "prefMenu.h" // диалоговое окно с настройками



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void keyPressEvent(QKeyEvent* event) override;

signals:
    void open();

    void save();

    void create_new();

    void clear();

    void read_only();

    void exit();

    void print();

    void theme_change();

    void set_dark_scheme();

    void set_light_scheme();

    void auto_save_status(bool);

    void auto_save_enabled();

    void auto_save_disabled();


private slots:
    void open_clicked();

    void save_clicked();

    void open_pref_dialog();

    void open_document();

    void save_as();

    void set_read_only(bool);

    void create_new_document();

    void exit_program();

    void clear_clicked();

    void setDarkTheme();

    void setLightTheme();

    void print_doc();

    //Auto save

    void enable_ASS();

    void disable_ASS();

private:
    Ui::MainWindow *ui;
    QString cur_path;
    QPlainTextEdit* text_wgt;
    bool autoSaveStatus;
};
#endif // MAINWINDOW_H
