#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Автооткрытие последнего сохранения для Задания 1
    QFile lastSave("./SavedFile.txt");
    if(lastSave.open(QIODevice::ReadOnly))
    {
        QByteArray qb = lastSave.readAll();
        if(!qb.isEmpty())
            ui->tsk1_plainTextEdit->setPlainText(qb);
    }
    else
        qDebug() << "Could not open last save\n";

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


//Задание 1

void MainWindow::on_tsk1_open_clicked()
{
    QString path = QFileDialog::getOpenFileName();
    if(path.isEmpty())
        return;
    else
    {
        QFile file(path);
        if(file.open(QIODevice::ReadOnly))
        {
            QByteArray qb = file.readAll();
            QString text(qb);
            ui->tsk1_plainTextEdit->setPlainText(text);
        }
        else
            qDebug() << "Could not open '" << path << "'\n";

    }
}


void MainWindow::on_tsk1_save_clicked()
{
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

void MainWindow::on_tsk2_open_clicked()
{
    QString path = QFileDialog::getOpenFileName();
    if(path.isEmpty())
        return;
    else
        ui->tsk2_addr->setText(path);
}


void MainWindow::on_tsk2_parse_clicked()
{
    QString address = ui->tsk2_addr->text();
    QFile source(address);
    if(source.open(QIODevice::ReadOnly))
    {
        QByteArray qb = source.readAll();
        QString text(qb);

        //<span title="ощущается как +3°" class="weather__temp svelte-dp8sbw" data-testid="weather-temp">+12°</span>
        QString temp_trait = "weather-temp\">";
        auto temp_first = text.indexOf(temp_trait);
        if(-1 != temp_first)
        {
            QString temp_info = text.mid(temp_first+temp_trait.length(), 3);
            ui->tsk2_temp->setText(temp_info);
        }
        else
        {
            ui->tsk2_temp->setText("Error");
        }

        QString USD_trait = "\"USD\",\"rate\":";
        auto USD_first = text.indexOf(USD_trait);
        if(-1 != USD_first)
        {
            QString USD_info = text.mid(USD_first+USD_trait.length(), 5);
            ui->tsk2_dlr->setText(USD_info);
        }
        else
        {
            ui->tsk2_dlr->setText("Error");
        }

        QString EUR_trait = "\"EUR\",\"rate\":";
        auto EUR_first = text.indexOf(EUR_trait);
        if(-1 != EUR_first)
        {
            QString EUR_info = text.mid(EUR_first+EUR_trait.length(), 5);
            ui->tsk2_eur->setText(EUR_info);
        }
        else
        {
            ui->tsk2_eur->setText("Error");
        }


    }
    else
        return;


    //:[
    //{"region":"RUB","title":"Курс ЦБ РФ","link":"https://news.mail.ru/currency/charcode/USD/","type":"USD","rate":60.22,"sign":"minus","change":1.03,"id":644327},
    //{"region":"RUB","title":"Курс ЦБ РФ","link":"https://news.mail.ru/currency/charcode/EUR/","type":"EUR","rate":61.54,"sign":"plus","change":0.54,"id":644327},
    //{"region":"USD","title":"Нефть марки Brent","link":"https://news.mail.ru/currency/lme/OIL2/","type":"OIL","rate":96.92,"sign":"plus","change":2.22,"id":644327}
    //]},

}



