#ifndef PREFMENU_H
#define PREFMENU_H

#pragma once
#include <QWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QRadioButton>
#include <QCheckBox>
#include <QVBoxLayout>



class prefMenu : public QWidget
{
    Q_OBJECT
public:
    explicit prefMenu(QWidget *parent = nullptr);

    bool autoSaveStatus;

    QCheckBox* cb_autosave;

signals:
    void set_dark_scheme();

    void set_light_scheme();

    void set_auto_save();

    void auto_save_enabled();

    void auto_save_disabled();

    void enable_ASS();

    void disable_ASS();

private slots:

    void set_ASS_checked();

    void set_ASS_unchecked();

    void setAutoSave();

    void end();
};

#endif // PREFMENU_H
