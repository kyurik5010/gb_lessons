#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    text_wgt = new QPlainTextEdit(this);
    setCentralWidget(text_wgt);


    QMenu* menu_bar = menuBar() -> addMenu("Menu");


    QAction* open_pref = menu_bar->addAction("0ptions"); // есть какой-то баг не показывает кнопку если назвать Options или Settings видимо есть подобные стандартные и что-то блокируется
    open_pref->connect(open_pref, SIGNAL(triggered()), this, SLOT(open_pref_dialog()));


    QMenu* open_sub_menu = new QMenu("0pen file");
    QAction* open_file = open_sub_menu->addAction("0pen existing");
    QAction* create_new = open_sub_menu->addAction("Create new");
    open_file->connect(open_file, SIGNAL(triggered()), this, SLOT(open_clicked()));
    open_file->connect(create_new, SIGNAL(triggered()), this, SLOT(create_new_document()));
    menu_bar->addMenu(open_sub_menu);


    QMenu* save_sub_menu = new QMenu("Save");
    QAction* save_file = save_sub_menu->addAction("Save");
    QAction* save_as = save_sub_menu->addAction("Save as");
    save_file->connect(save_file, SIGNAL(triggered()), this, SLOT(save_clicked()));
    save_as->connect(save_as, SIGNAL(triggered()), this, SLOT(save_as()));
    menu_bar->addMenu(save_sub_menu);


    QAction* read_only = menu_bar->addAction("Read_only");
    read_only->setCheckable(true);
    read_only->connect(read_only, SIGNAL(triggered(bool)), this, SLOT(set_read_only(bool)));

    QAction* print = menu_bar->addAction("Print document");
    print->connect(print, SIGNAL(triggered(bool)), this, SLOT(print_doc()));

    QAction* exit = menu_bar->addAction("Close program");
    open_pref->connect(exit, SIGNAL(triggered()), this, SLOT(exit_program()));
    //здесь смена цветовой схемы и настройка автосохранений


    connect(this, SIGNAL(open()), this, SLOT(open_clicked()));
    connect(this, SIGNAL(save()), this, SLOT(save_as()));
    connect(this, SIGNAL(create_new()), this, SLOT(create_new_document()));
    connect(this, SIGNAL(exit()), this, SLOT(exit_program()));
    connect(this, SIGNAL(print()), this, SLOT(print_doc()));

    //сигнальная булька для автосохранения и окна настроек
    autoSaveStatus = true;

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
    cur_path = QDir::currentPath() + '/' + lastSave.fileName().mid(lastSave.fileName().indexOf('/')+1,lastSave.fileName().length()-lastSave.fileName().indexOf('/'));

    //вывод имени файла в заголовке окна
    setWindowTitle(lastSave.fileName().mid(lastSave.fileName().indexOf('/')+1,lastSave.fileName().length()-lastSave.fileName().indexOf('/')));

    //тестовая зона
//    QStyle* cur_style = MainWindow::style();
//    qDebug() << "Style:\n\n" << cur_style << "\n\n***";

}



MainWindow::~MainWindow()
{
    if(autoSaveStatus)
    {
        qDebug() << "Saving automaticaly";
        QString saved = text_wgt->toPlainText();
        if(!saved.isEmpty())
        {
            QFile saveFile("./autosave.txt");
            if(saveFile.open(QIODevice::WriteOnly))
            {
                QByteArray qb = saved.toUtf8();
                saveFile.write(qb);
            }
        }
    }
    else
        qDebug() << "Auto save not active";

    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
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

        else if(combo.key() == Qt::Key_P) emit print();

        else if(combo.key() == Qt::Key_Q) emit exit();
    }
}

void MainWindow::open_clicked()
{
    cur_path = QFileDialog().getOpenFileName();
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

void MainWindow::save_clicked()
{
    qDebug() << "Save / Current path: " << cur_path;
    if(cur_path.isEmpty())
    {
        MainWindow::save_as();
    }
    else
    {
        QFile file(cur_path);
        if(file.open(QIODevice::WriteOnly))
        {
            QString text = text_wgt->toPlainText();
            QByteArray qb = text.toUtf8();
            file.write(qb);
            file.close();
        }
        else
            qDebug() << "Could not open '" << cur_path << "'\n";
    }
}

void MainWindow::open_pref_dialog()
{

    prefMenu* pref = new prefMenu(this);

    QMessageBox dialog;

    dialog.layout()->addWidget(pref);
    dialog.setWindowTitle("Options");

    connect(pref, SIGNAL(set_dark_scheme()), this, SLOT(setDarkTheme()));
    connect(pref, SIGNAL(set_light_scheme()), this, SLOT(setLightTheme()));

    if(autoSaveStatus)
        emit auto_save_enabled();
    else
        emit auto_save_disabled();

    dialog.exec();
}

void MainWindow::open_document()
{
    qDebug() << "open_document()";
    return;
}

void MainWindow::save_as()
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
            file.close();
        }
        else
            qDebug() << "Could not open '" << path << "'\n";
    }
}

void MainWindow::set_read_only(bool b)
{
    text_wgt->setReadOnly(b);
    if(text_wgt->isReadOnly())
        qDebug() << "read only!";
}

void MainWindow::create_new_document()
{
    qDebug() << "create new";
    MainWindow::save_clicked();
    text_wgt->setPlainText("");

    QFile file("./new file.txt");
    file.open(QIODevice::ReadWrite);

}

void MainWindow::exit_program()
{
    qDebug() << "exit";
    MainWindow::save_clicked();
    this->close();
}

void MainWindow::clear_clicked()
{
    text_wgt->clear();
}

void MainWindow::setDarkTheme()
{
    qDebug() << "Theme dark";
    setStyleSheet("QPlainTextEdit { color: rgb(15,223,12) ; background-color: rgb(33,60,70) }"
                  "QMainWindow::separator { background-color: rgb(0,0,0) }"
                  "QMenu { background-color: rgb(20,0,0) }"
                  "QMenu::item { background-color: rgb(0,20,0) }"
                  );
}

void MainWindow::setLightTheme()
{
    qDebug() << "Theme light";
    setStyleSheet("QPlainTextEdit { color: black; background-color: rgb(237,233,238); selection-color: brown }"
                  "QPushButton { color: rgb(105, 109, 122); background-color: rgb(140, 194, 240); border-color: rgb(105, 109, 122); font: bold 13px; padding: 3px; border-style: outset; border-width: 2px; border-radius: 5px }"
                  "QPushButton:pressed{ color: rgb(200,200,200); background-color: rgb(100, 154, 200); border-color: rgb(120, 120, 120);  border-style: inset }"
                  "QMainWindow::separator { background: rgb(200,200,200) }"
                  );
}

void MainWindow::print_doc()
{
    qDebug() << "print_doc()";

    QPrinter printer;
    QPrintDialog dialog(&printer, this);

    dialog.setWindowTitle("Print document");

    if (text_wgt->textCursor().hasSelection())
        dialog.setOption(QAbstractPrintDialog::PrintSelection, true);
    if (dialog.exec() != QDialog::Accepted)
        return;
}

void MainWindow::enable_ASS()
{
    qDebug() << "enable_ASS()";
    autoSaveStatus = true;
}

void MainWindow::disable_ASS()
{
    qDebug() << "disable_ASS()";
    autoSaveStatus = false;
}

