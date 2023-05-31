#include "prefMenu.h"

prefMenu::prefMenu(QWidget *parent)
    : QWidget{parent}
{


    QRadioButton* rb_dark = new QRadioButton("dark", parent);
    QRadioButton* rb_light = new QRadioButton("light", parent);
    cb_autosave = new QCheckBox("enable auto save", parent);
    //QPushButton* btn_ok = new QPushButton("ok", this);


    rb_dark->connect(rb_dark, SIGNAL(toggled(bool)), this, SIGNAL(set_dark_scheme()));
    rb_light->connect(rb_light, SIGNAL(toggled(bool)), this, SIGNAL(set_light_scheme()));
    cb_autosave->connect(cb_autosave, SIGNAL(toggled(bool)), this, SLOT(setAutoSave())); // <-----------SLOT
    connect(parent, SIGNAL(auto_save_enabled()), this, SLOT(set_ASS_checked()));
    connect(parent, SIGNAL(auto_save_disabled()), this, SLOT(set_ASS_unchecked()));
    connect(this, SIGNAL(enable_ASS()), parent, SLOT(enable_ASS()));
    connect(this, SIGNAL(disable_ASS()), parent, SLOT(disable_ASS()));

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(rb_dark);
    layout->addWidget(rb_light);
    layout->addWidget(cb_autosave);
    //layout->addWidget(btn_ok);

    setLayout(layout);
    setWindowTitle("Options");
}

void prefMenu::set_ASS_checked()
{
    qDebug() << "prefMenu: ASS enabled in parent";
    cb_autosave->setChecked(true);
}

void prefMenu::set_ASS_unchecked()
{
    qDebug() << "prefMenu: ASS disabled in parent";
    cb_autosave->setChecked(false);
}

void prefMenu::setAutoSave()
{
    qDebug() << "Setting autosave";
    if(cb_autosave->isChecked())
        emit enable_ASS();
    else
        emit disable_ASS();
}

void prefMenu::end()
{
    this->close();
}
