#include "textparser.h"


TextParser::TextParser()
{
    symbols.insert("${CPW}","©");
    symbols.insert("${PML}","‰");
    symbols.insert("${TMK}","™");
    symbols.insert("${EUR}","€");
    symbols.insert("${CHK}","✔");
}

std::optional<QPair<int, QString>> TextParser::parse(QString str) // QChar слишком мал для таких символов
{

//    QTextStream cout(stdout); // для дебага

//    cout << "Получена строка: " << str << "\n";
//    cout.flush();

    if(str.length() < 6)
    {
        return std::nullopt;
    }

    auto fnd_f = str.indexOf("${");
    auto fnd_l = str.indexOf('}', fnd_f);

    if(-1 == fnd_f)
    {
        return std::nullopt;
    }
    else if(-1 == fnd_l)
    {
        return std::nullopt;
    }
    else
    {

        QString temp = "";

        temp.insert(0, &str[fnd_f], fnd_l-fnd_f+1);

        auto iter = symbols.find(temp);

        if(iter == symbols.end())
        {
            std::cout << "Ключ не найден" << std::endl;
            return std::nullopt;
        }

        return std::make_pair(fnd_f, iter.value());
    }
}

QString TextParser::reconstruct(QString str, QPair<int, QString> result)
{

//    QTextStream cout(stdout);

//    cout << "Начата пересборка строки\n" << str << " | " << result.first << " | " << result.second << "\n";
//    cout.flush();

    QString first_part, second_part = "", new_str = "";

    first_part.insert(0, &str[0], result.first);//-1

    if(result.first + 6 < str.length())
    {
        second_part.insert(0, &str[result.first+6]);
    }

    new_str += first_part + result.second + (QChar)32 + second_part;

    //new_str.insert(result.first-1, " ");

    return new_str;
}

