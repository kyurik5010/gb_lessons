Notes:

1) Модули Qt

Qt Core - библиотека основных классов. При сборке QMake подключается автоматически, в других
случаях нужно включать отдельно.

Qt GUI - библиотека классов для интеграции пользовательского интерфейса и обработки событий.
В нее интегрирован OpenGL и OpenGL ES (2д графика, шрифты и изображения).

Qt SQL - модуль поддержки баз данных SQL.

2) текстовые виджеты

динамические объекты передаваемые объектам виджетов (lineEdit и т.д.) отдельно удалять не 
требуется.


Защита полей ввода и вывода инф.(ui->lineEdit->setEchoMode(QlineEdit::EchoMode::Normal)),

3) Валидация:

#include <QintValidator>

ui->lineEdit->serValidator(new QintValidator(ui->lineEdit))

позволяет ограничивать ввод по диапазону числа.
Валидатор для дробей #include <QDoubleValidator> позволяет ограничивать точность числа после 
точки.

Маска ввода ui->виджет->setInputMask("009.009.009.009;_") знак '_' после ';' означает, что 
пустые места в итоговом шаблоне будут заполнены '-'. 


4) Списки, таблицы, деревья

5) Модель-представление/отображение
 
модель - непосредственно связана с представляемой структурой данных;

представление - визуальное представление модели -> виджеты отображающие эти 
данные

Объяснение от ChatGPT:
The Model-View-Controller (MVC) concept is a software design pattern used to separate the 
data layer (model) from the user interface layer (view) in a software application. Qt is an 
application framework that uses the MVC concept to create user interfaces. In Qt, the model 
is responsible for managing and storing data, while the view is responsible for displaying 
the data. The controller is responsible for handling user input and connecting the model and 
view layers. The controller also handles communication between the model and view layers, 
allowing them to interact with each other.

*) приведенные примеры:

парсинг текста с арифметическими выражениями,

рассмотренные функции:

QString:
.indexOf("sequence"/QString/char, int variable),
.mid("sequence"/QString/char, "sequence"/QString/char),
.insert(),
.remove(),
::number(int/double),
QString("Cell nr. %1, %2").arg(i).arg(j);

не рассмотренные:

QString:

.at(index) == [index],

QChar:

.isDigit(),
.unicode(),



