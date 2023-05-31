#ifndef TEXTPARSER_H
#define TEXTPARSER_H

#pragma once
#include <QMap>
#include <QPair>
#include <QMainWindow>
#include <iostream>
#include <QTextStream>

class TextParser
{
private:
    QString text;
    QMap<QString, QString> symbols;
    QString substitute;

public:
    TextParser();

    std::optional<QPair<int, QString>> parse(QString str); // парсит строку, в случае неудачи возвращает нульопт

    QString reconstruct(QString str, QPair<int, QString>); // вызывается только при удачном парсинге строки и возвращает новую строку с симоволом

    //QString get_symbols();
};

#endif // TEXTPARSER_H
