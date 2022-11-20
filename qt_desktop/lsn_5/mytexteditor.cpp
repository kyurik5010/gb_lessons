#include "mytexteditor.h"


MyTextEditor::MyTextEditor(QWidget *parent)
    : QWidget{parent}
{
    theme_label = new QLabel("Color scheme:", this);
    rb_dark = new QRadioButton("Dark", this);
    rb_light = new QRadioButton("Light", this);

    theme_layout = new QHBoxLayout(this);
    theme_layout->addWidget(theme_label);
    theme_layout->addWidget(rb_dark);
    theme_layout->addWidget(rb_light);

    theme_bar = new QWidget(this);
    theme_bar->setLayout(theme_layout);

    btn_save = new QPushButton("save", this);
    btn_open = new QPushButton("open", this);
    btn_clear = new QPushButton("clear", this);
    chk_readOnly = new QCheckBox("read only", this);

    menu_layout = new QHBoxLayout(this);
    menu_layout->addWidget(btn_save);
    menu_layout->addWidget(btn_open);
    menu_layout->addWidget(chk_readOnly);
    menu_layout->addWidget(btn_clear);

    menu_bar = new QWidget(this);
    menu_bar->setLayout(menu_layout);

    text_wgt = new QPlainTextEdit(this);

    window_grid = new QGridLayout(this);

    window_grid->addWidget(menu_bar,0,0,1,6);
    window_grid->addWidget(text_wgt,1,0,8,8);
    window_grid->addWidget(theme_bar,10,0,1,6);

    setLayout(window_grid);

    connect(this, SIGNAL(open()), this, SLOT(open_document()));
    connect(this, SIGNAL(save()), this, SLOT(save_as()));
    connect(this, SIGNAL(create_new()), this, SLOT(create_new_document()));
    connect(this, SIGNAL(exit()), this, SLOT(exit_program()));

    btn_save->connect(btn_save, SIGNAL(clicked()), this, SLOT(on_save_clicked()));
    btn_clear->connect(btn_clear, SIGNAL(clicked()), this, SLOT(on_clear_clicked()));
    btn_open->connect(btn_open, SIGNAL(clicked()), this, SLOT(open_document()));

    rb_dark->connect(rb_dark, SIGNAL(toggled(bool)), this, SLOT(setDarkTheme()));
    rb_light->connect(rb_light, SIGNAL(toggled(bool)), this, SLOT(setLightTheme()));


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

    //инициализация переменной путем к файлу
    cur_path = QDir::currentPath() + lastSave.fileName().mid(lastSave.fileName().indexOf('/')+1,lastSave.fileName().length()-lastSave.fileName().indexOf('/'));

    //вывод имени файла в заголовке окна
    setWindowTitle(lastSave.fileName().mid(lastSave.fileName().indexOf('/')+1,lastSave.fileName().length()-lastSave.fileName().indexOf('/')));

}

MyTextEditor::~MyTextEditor()
{
    //автосохранение
    QString saved = text_wgt->toPlainText();
    if(!saved.isEmpty())
    {
        QFile saveFile("./SavedFile.txt");
        if(saveFile.open(QIODevice::WriteOnly))
        {
            QByteArray qb = saved.toUtf8();
            saveFile.write(qb);
        }
    }

    qDebug() << ((theme_bar == nullptr)? "mem freed" : "mem cluttered");
}

void MyTextEditor::keyPressEvent(QKeyEvent *event)
{
    //Note: On macOS, the CTRL value corresponds to the Command keys on the keyboard, and the META value corresponds to the Control keys.
    //Qt::SHIFT Qt::ShiftModifier
    //Qt::CTRL Qt::ControlModifier

    QKeyCombination combo(event->keyCombination().keyboardModifiers(), event->keyCombination().key());
    combo.toCombined();

    if(combo.keyboardModifiers() == Qt::ControlModifier)
    {
        if(combo.key() == Qt::Key_S) emit save();

        else if(combo.key() == Qt::Key_N) emit create_new();

        else if(combo.key() == Qt::Key_O) emit open();

        else if(combo.key() == Qt::Key_Q) emit exit();
    }
}

void MyTextEditor::on_open_clicked()
{
        QFileDialog dialog;

        if(chk_readOnly->isChecked())
        {
            dialog.setOption(QFileDialog::ReadOnly); // не работает, или работает не так как ожидалось
            text_wgt->setReadOnly(true);
            qDebug() << "read only - true \n";
        }

        cur_path = dialog.getOpenFileName();

        if(cur_path.isEmpty())
            return;
        else
        {
            QFile file(cur_path);


            if(file.open(QIODevice::ReadOnly))
            {
                QByteArray qb = file.readAll();
                QString text(qb);
                text_wgt->setPlainText(text);
                if(text_wgt->isReadOnly())
                    setWindowTitle(cur_path.mid(cur_path.lastIndexOf("/")+1, (cur_path.length() - cur_path.lastIndexOf("/"))) + " - read only");
                else
                    setWindowTitle(cur_path.mid(cur_path.lastIndexOf("/")+1, (cur_path.length() - cur_path.lastIndexOf("/"))));
            }
            else
                qDebug() << "Could not open '" << cur_path << "'\n";
        }
}

void MyTextEditor::on_save_clicked()
{
    if(cur_path.isEmpty())
    {
        save_as();
    }
    else
    {
        QFile file(cur_path);
        if(file.open(QIODevice::WriteOnly))
        {
            QString text = text_wgt->toPlainText();
            QByteArray qb = text.toUtf8();
            file.write(qb);
        }
        else
            qDebug() << "Could not open '" << cur_path << "'\n";
    }
}

void MyTextEditor::open_document()
{
        //qDebug() << sender()->
        qDebug() << "open";
        MyTextEditor::on_open_clicked();
}

void MyTextEditor::save_as()
{
        qDebug() << "save as";
        QString path = QFileDialog::getSaveFileName();
        if(path.isEmpty())
            return;
        else
        {
            QFile file(path);
            if(file.open(QIODevice::WriteOnly))
            {
                QString text = text_wgt->toPlainText();
                QByteArray qb = text.toUtf8();
                file.write(qb);
            }
            else
                qDebug() << "Could not open '" << path << "'\n";
        }
}

void MyTextEditor::create_new_document()
{
        qDebug() << "create new";
        MyTextEditor::on_save_clicked();
        text_wgt->setPlainText("");

        QFile file("./new file.txt");
        file.open(QIODevice::ReadWrite);

}

void MyTextEditor::exit_program()
{
        qDebug() << "exit";
        MyTextEditor::on_save_clicked();
        this->close();
}

void MyTextEditor::on_clear_clicked()
{
    text_wgt->clear();
}

void MyTextEditor::setDarkTheme()
{
    qDebug() << "Theme dark";
    setStyleSheet("QPlainTextEdit { color: green; background-color: black }"
                  "QPushButton { color: white }"

                  );

}

void MyTextEditor::setLightTheme()
{

    qDebug() << "Theme light";
    setStyleSheet("QPlainTextEdit { color: black; background-color: rgb(237,233,238); selection-color: brown }"
                  "QPushButton { color: rgb(105, 109, 122); background-color: rgb(140, 194, 240); border-color: rgb(105, 109, 122); font: bold 13px; padding: 3px; border-style: outset; border-width: 2px; border-radius: 5px }"
                  "QPushButton:pressed{ color: rgb(200,200,200); background-color: rgb(100, 154, 200); border-color: rgb(120, 120, 120);  border-style: inset }"
                  "QMainWindow::separator { background: rgb(200,200,200) }"
                  );

}


