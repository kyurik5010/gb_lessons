#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(this, SIGNAL(open()), this, SLOT(open_document()));
    connect(this, SIGNAL(save()), this, SLOT(save_as()));
    connect(this, SIGNAL(create_new()), this, SLOT(create_new_document()));
    connect(this, SIGNAL(exit()), this, SLOT(exit_program()));

    //Автооткрытие последнего сохранения для Задания 1
    QFile lastSave("./SavedFile.txt");
    if(lastSave.open(QIODevice::ReadOnly))
    {
        QByteArray qb = lastSave.readAll();
        if(!qb.isEmpty())
            ui->tsk1_plainTextEdit->setPlainText(qb);
    }
    else
        qDebug() << "No recent saves available\n";

    setWindowTitle(lastSave.fileName());

//    if(ui->tsk1_plainTextEdit->isReadOnly())
//        setWindowTitle(cur_path.mid(cur_path.lastIndexOf("/")+1, (cur_path.length() - cur_path.lastIndexOf("/"))) + " - read only");
//    else
//        setWindowTitle(cur_path.mid(cur_path.lastIndexOf("/")+1, (cur_path.length() - cur_path.lastIndexOf("/"))));



}

MainWindow::~MainWindow()
{
    //Auto save on exit для Задания 1
    QString saved = ui->tsk1_plainTextEdit->toPlainText();
    if(!saved.isEmpty())
    {
        QFile saveFile("./SavedFile.txt");
        if(saveFile.open(QIODevice::WriteOnly))
        {
            QByteArray qb = saved.toUtf8();
            saveFile.write(qb);
        }
    }

    delete ui;
}

//Note: On macOS, the CTRL value corresponds to the Command keys on the keyboard, and the META value corresponds to the Control keys.
//Qt::SHIFT Qt::ShiftModifier
//Qt::CTRL Qt::ControlModifier

void MainWindow::keyPressEvent(QKeyEvent *event) // modifier
{
    //QKeyCombination combo(Qt::SHIFT, Qt::Key_N);
    //event->modifiers();
    QKeyCombination combo(event->keyCombination().keyboardModifiers(), event->keyCombination().key());
    combo.toCombined();

    if(combo.keyboardModifiers() == Qt::ControlModifier)
    {
        //qDebug() << "ctrl";
        if(combo.key() == Qt::Key_S)
        {
            emit save();
            qDebug() << "ctrl+S";
        }
        else if(combo.key() == Qt::Key_N)
        {
            emit create_new();
            qDebug() << "ctrl+N";
        }

        else if(combo.key() == Qt::Key_O)
        {
            emit open();
            qDebug() << "ctrl+O";
        }

        else if(combo.key() == Qt::Key_Q)
        {
            emit exit();
            qDebug() << "ctrl+Q";
    }
    }
}

void MainWindow::on_tsk1_open_clicked()
{
    QFileDialog dialog;

    if(ui->checkBox_RO->isChecked())
    {
        dialog.setOption(QFileDialog::ReadOnly); // не работает, или работает не так как ожидалось
        ui->tsk1_plainTextEdit->setReadOnly(true);
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
            ui->tsk1_plainTextEdit->setPlainText(text);
            if(ui->tsk1_plainTextEdit->isReadOnly())
                setWindowTitle(cur_path.mid(cur_path.lastIndexOf("/")+1, (cur_path.length() - cur_path.lastIndexOf("/"))) + " - read only");
            else
                setWindowTitle(cur_path.mid(cur_path.lastIndexOf("/")+1, (cur_path.length() - cur_path.lastIndexOf("/"))));
        }
        else
            qDebug() << "Could not open '" << cur_path << "'\n";

    }
}

void MainWindow::on_tsk1_save_clicked() // это который не 'save as'
{
    if(cur_path.isEmpty())
    {
        MainWindow::save_as();
    }

    else
    {
        QFile file(cur_path);
        if(file.open(QIODevice::WriteOnly))
        {
            QString text = ui->tsk1_plainTextEdit->toPlainText();
            QByteArray qb = text.toUtf8();
            file.write(qb);
        }
        else
            qDebug() << "Could not open '" << cur_path << "'\n";
    }

}

void MainWindow::open_document()
{
    //qDebug() << sender()->
    qDebug() << "open";
    MainWindow::on_tsk1_open_clicked();
}

void MainWindow::create_new_document()
{
    qDebug() << "create new";
    MainWindow::on_tsk1_save_clicked();
    ui->tsk1_plainTextEdit->setPlainText("");

    QFile file("./new file.txt");
    file.open(QIODevice::ReadWrite);


    //QDir dir
    //QString path = QFileDialog::get
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
            QString text = ui->tsk1_plainTextEdit->toPlainText();
            QByteArray qb = text.toUtf8();
            file.write(qb);
        }
        else
            qDebug() << "Could not open '" << path << "'\n";
    }
}

void MainWindow::exit_program()
{
    qDebug() << "exit";
    MainWindow::on_tsk1_save_clicked();
    ui->centralwidget->close();
}


