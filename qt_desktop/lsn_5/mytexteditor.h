#ifndef MYTEXTEDITOR_H
#define MYTEXTEDITOR_H

#pragma once
#include <QWidget>
#include <QFileDialog>
#include <QDebug>

#include <QKeyEvent>

//кнопки и т.д.
#include <QRadioButton>
#include <QLabel>
#include <QCheckBox>
#include <QPushButton>

//раскладки
#include <QHBoxLayout>
#include <QGridLayout>

//прочее
#include <QPlainTextEdit>




class MyTextEditor : public QWidget
{
    Q_OBJECT
private:
    QLabel* theme_label;
    QRadioButton* rb_dark;
    QRadioButton* rb_light;
    QHBoxLayout* theme_layout;
    QWidget* theme_bar;

    QPushButton* btn_save;
    QPushButton* btn_open;
    QPushButton* btn_clear;
    QCheckBox* chk_readOnly;
    QHBoxLayout* menu_layout;
    QWidget* menu_bar;

    QPlainTextEdit* text_wgt;

    QGridLayout* window_grid;

    QString cur_path;

public:
    explicit MyTextEditor(QWidget *parent = nullptr);

    ~MyTextEditor();

    void keyPressEvent(QKeyEvent *event) override;

signals:
    void open();

    void save();

    void create_new();

    void clear();

    void read_only();

    void exit();

    void theme_change();

private slots:
    void on_open_clicked();

    void on_save_clicked();

    void open_document();

    void save_as();

    void create_new_document();

    void exit_program();

    void on_clear_clicked();

    //void change_theme();
    void setDarkTheme();

    void setLightTheme();
};

/**
    QLabel* theme_label = new QLabel("Color scheme:", this);
    QRadioButton* rb_dark = new QRadioButton("Dark", this);
    QRadioButton* rb_light = new QRadioButton("Light", this);

    QHBoxLayout* theme_layout = new QHBoxLayout(this);
    theme_layout->addWidget(theme_label);
    theme_layout->addWidget(rb_dark);
    theme_layout->addWidget(rb_light);

    QWidget* theme_bar = new QWidget(this);
    theme_bar->setLayout(theme_layout);

    QPushButton* btn_save = new QPushButton("save", this);
    QPushButton* btn_open = new QPushButton("open", this);
    QPushButton* btn_clear = new QPushButton("clear", this);

    QCheckBox* chk_readOnly = new QCheckBox("read only", this);

    QHBoxLayout* menu_layout = new QHBoxLayout(this);
    menu_layout->addWidget(btn_save);
    menu_layout->addWidget(btn_open);
    menu_layout->addWidget(chk_readOnly);
    menu_layout->addWidget(btn_clear);

    QWidget* menu_bar = new QWidget(this);
    menu_bar->setLayout(menu_layout);

    QPlainTextEdit* text_wgt = new QPlainTextEdit(this);

    QGridLayout* window_grid = new QGridLayout(this);

    window_grid->addWidget(menu_bar,0,0,1,6);
    window_grid->addWidget(text_wgt,1,0,8,8);
    window_grid->addWidget(theme_bar,10,0,1,6);

//    QWidget* text_editor = new QWidget(this);

//    text_editor->setLayout(window_grid);

//    setCentralWidget(text_editor);

    setLayout(window_grid);

    connect(this, SIGNAL(open()), this, SLOT(open_document()));
    connect(this, SIGNAL(save()), this, SLOT(save_as()));
    connect(this, SIGNAL(create_new()), this, SLOT(create_new_document()));
    connect(this, SIGNAL(exit()), this, SLOT(exit_program()));


    //Автоматическое открытие последнего автосохранения
    QFile lastSave("./autosave.txt");
    if(lastSave.open(QIODevice::ReadOnly))
    {
        QByteArray qb = lastSave.readAll();
        if(!qb.isEmpty())
            text_wgt->setPlainText(qb);
    }
    else
        qDebug() << "No recent saves available\n";

//    //инициализация переменной путем к файлу
//    cur_path = QDir::currentPath() + lastSave.fileName().mid(lastSave.fileName().indexOf('/')+1,lastSave.fileName().length()-lastSave.fileName().indexOf('/'));

//    //вывод имени файла в заголовке окна
//    setWindowTitle(lastSave.fileName().mid(lastSave.fileName().indexOf('/')+1,lastSave.fileName().length()-lastSave.fileName().indexOf('/')));

*/

#endif // MYTEXTEDITOR_H
