Заметки
=======


__1) QWidget. Виды виджетов. Иерархия виджетов__
------------------------------------------------

Класс `QWidget` — базовый класс всех объектов пользовательского интерфейса. Виджет — основа 
пользовательского интерфейса. Виджет не только отображает компоненты, но и обрабатывает 
события мыши и клавиатуры.  

Виджет без родительского виджета всегда является независимым окном 
(виджетом верхнего уровня). Для таких виджетов методы `setWindowTitle()` и `setWindowIcon()` 
устанавливают заголовок окна и иконку.  

Если виджет используется как контейнер, объединяющий дочерние виджеты, он называется комбинированным виджетом. Такой виджет может быть создан на 
основе виджета, который имеет определенные визуальные свойства — как, например, __QFrame__, 
— а его дочерние виджеты можно разместить в нем с помощью компоновщика или __QMainWindow__, 
который является контейнером для всех виджетов графического интерфейса.

Если нужно отловить щелчок мыши в дочернем виджете, вызовите его функцию `underMouse()` 
внутри функции `mousePressEvent()` виджета.


__2) Подключение OpenGL и других сторонних библиотек__
------------------------------------------------------

Подключение любой библиотеки происходит по одному шаблону:
● указываем компилятору путь к заголовкам подключаемой библиотеки (для некоторых библиотек 
утилита qmake автоматически определяет путь к заголовкам);
● указываем линковщику путь к статическим библиотекам;
● указываем линковщику, какие именно статические библиотеки нужно добавить в сборку 
проекта.
<pre><code>
LIBS +=-lOpenGL32
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin 
!isEmpty(target.path): 
INSTALLS += target
</pre></code>
Для работы с функциями OpenGL нужно подключить статическую библиотеку: для ОС Windows —
OpenGL32, для Linux — libGL. Чтобы подключить библиотеку, нужно в фай̆ле проекта добавить ее
к переменной̆̆ `LIBS` с параметром `-l`. Следующим шагом отредактировать класс главного окна. 
Поменяем родительский̆̆ класс на Window, а также наследуем методы от класса 
__QOpenGLFunctions__  

Наименования функций __OpenGL__ имеют отличительные черты позволяющие легко их отличать от
функций других библиотек. Например: `glColor3f()`, в которой 3f означает что у функции
имеются 3 параметра типа float.

При разработке приложений под Qt с использованием библиотеки OpenGL необходимо подключить 
`<QGLWidget>`, отнаследовать класс `MainWindow` от `QGLWidget` и переопределить методы 
`void initializeGL() override;`, `void resizeGL(int, int) override;` и `void paintGL() 
override;`. (`00.24:50`)

`initializeGL()` для инициализации контекста OpenGL и настройки параметров отображения. Эта 
функция вызывается один раз при создании виджета и должна содержать все необходимые команды 
OpenGL для настройки контекста, включая выбор версии OpenGL, установку параметров 
сглаживания, задание цвета фона и настройку освещения. Функция initializeGL() является 
обязательной для реализации при создании приложений с использованием Qt и OpenGL.

resizeGL() используется в OpenGL для изменения размеров окна вывода. Она вызывается каждый 
раз, когда размер окна изменяется, и позволяет обновить параметры проекции, такие как 
соотношение сторон и угол обзора. Внутри функции resizeGL() можно задать новые параметры 
проекции и перерисовать сцену с новыми размерами.

`paintGL()` используется для отрисовки содержимого виджета с помощью команд OpenGL. 
Эта функция вызывается каждый раз, когда виджет нужно перерисовать, например, при первом 
показе, изменении размера или когда он был закрыт и затем открыт повторно. Функция paintGL() 
должна содержать все необходимые команды OpenGL для визуализации сцены, включая установку 
матриц проекции и моделирования, определение геометрии объектов и применение текстур и 
освещения. Это важная функция для создания интерактивных 3D-графических приложений с 
использованием Qt и OpenGL.

`Qt::GlobalColor` - перечисление, которое содержит предопределенные цвета в Qt;  

`qglClearColor(Qt::GlobalColor::black)` - используется в библиотеке Qt для установки цвета 
очистки буфера изображения в OpenGL. Она принимает четыре параметра: значения красного, 
зеленого, синего и альфа-каналов, которые задают цвет очистки в формате RGBA. При вызове 
этой функции OpenGL сохраняет установленный цвет очистки в своем контексте, и при каждом 
вызове функции glClear() для очистки буфера изображения будет использоваться заданный цвет. 
Это позволяет установить фоновый цвет для сцены, которая будет отображаться на экране;  
  
`glMatrixMode(GL_PROJECTION)` - используется в OpenGL для указания, какой стек матриц 
является целевым для последующих операций с матрицами. Существует три возможных режима 
матриц: `GL_MODELVIEW`, `GL_PROJECTION` и `GL_TEXTURE`. Стек матриц __GL_MODELVIEW__ 
используется для преобразования объектов из пространства модели в пространство мира, а стек матриц 
__GL_PROJECTION__ используется для выполнения перспективной проекции. Стек матриц 
__GL_TEXTURE__ используется для преобразования координат текстуры. Вызов `glMatrixMode()` с 
одним из этих режимов в качестве аргумента позволяет последующим вызовам функций, таких как 
`glLoadIdentity()`, `glTranslate()`, `glRotate()` и `glScale()`, воздействовать на 
соответствующий стек матриц.;  

`glLoadIdentity()` - function used in OpenGL to reset the current matrix to its __default 
state__. It replaces the current matrix with the identity matrix, which is a matrix awith 
all elements set to `0`, __except__ for the elements on the main diagonal, which are set to 
`1`. This effectively resets any transformations that have been applied to the current matrix.  

`glViewport(0,0,(GLint)w,(GLint)h)` - "устанавливает видовое окно", используется в OpenGL 
для определения области экрана, где будет происходить рендеринг. Она принимает __четыре__ 
параметра: координаты `x` и `y` __нижнего левого__ угла области просмотра, а также `ширину` 
и `высоту` области просмотра. Область просмотра определяет систему координат, используемую 
для рендеринга, и может быть настроена для различных размеров окон или соотношений сторон. 
 
`glOrtho(0,200,200,-1,-1)` - используется в OpenGL для определения ортогональной матрицы 
проекции. Она принимает шесть параметров, которые определяют область видимости, и 
используется для трансформации графического объекта в экранные координаты. Она часто 
используется совместно с glViewport(), чтобы установить область видимости для рендеринга.  
<pre><code>
void glOrtho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble nearVal, 
GLdouble farVal);

- left: координата левой границы видимости.
- right: координата правой границы видимости.
- bottom: координата нижней границы видимости.
- top: координата верхней границы видимости.
- nearVal: расстояние до ближайшей плоскости отсечения.
- farVal: расстояние до дальней плоскости отсечения.
</pre></code>

`glClear()` используется в OpenGL для очистки буфера изображения. Она вызывается для 
удаления предыдущего изображения и подготовки буфера для новой отрисовки. Внутри функции 
glClear() можно задать параметры очистки, такие как цвет и глубину.  
API: void glClear(GLbitfield mask);
<pre><code>
//Параметры:

- mask: битовая маска, которая указывает, какие буферы нужно очистить. Может быть 
комбинацией следующих значений:
  - GL_COLOR_BUFFER_BIT: очистить буфер цвета
  - GL_DEPTH_BUFFER_BIT: очистить буфер глубины
  - GL_STENCIL_BUFFER_BIT: очистить буфер трафарета

Пример использования:

// Очистить буфер цвета и глубины
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
</pre></code>

'glBegin()' - функция в OpenGL, которая начинает определение графического примитива, 
такого как точка, линия или треугольник. Если верить ChatGPT:
<pre><code>
glBegin() is a legacy function that has been deprecated in modern versions of OpenGL. It is 
no longer supported and should not be used in new code. Instead, you should use more modern 
approaches such as Vertex Buffer Objects (VBOs) or Vertex Array Objects (VAOs). These 
provide better performance and are more flexible than the old glBegin() function.  
</pre></code> 

Функция `glEnd()` в OpenGL используется для завершения определения геометрической фигуры, 
начатой с помощью функции `glBegin()`. Она не принимает никаких аргументов и не возвращает 
никаких значений. После вызова glEnd() OpenGL заканчивает рисование текущей фигуры и 
переходит к следующей команде. Однако, в современных версиях OpenGL рекомендуется 
использовать более новые способы рисования, такие как __Vertex Buffer Objects (VBO)__ или 
Vertex __Array Objects (VAO)__, а не glBegin() и glEnd().

Система координат OpenGL:  

![https://moluch.ru/conf/blmcbn/6212/image003.png](https://moluch.ru/conf/blmcbn/6212/image003.png)


__3) Виджеты компоновщики__
---------------------------

Виджеты-компоновщики / Слои — это контейнеры для виджетов. Они используются для компоновки 
виджетов на форме или других виджетах. Есть три основных вида слоев: для вертикальной 
компоновки, горизонтальной компоновки и компоновки по сетке. Нужно это для динамической 
перекомпоновки виджетов при масштабировании окна.

<pre><code>
QPushButton* b1 = new QPushButton("A", this);
QPushButton* b2 = new QPushButton("B", this);
QPushButton* b3 = new QPushButton("C", this);
QPushButton* b3 = new QPushButton("C", this);

QVBoxLayout* layout = new QVBoxLayout(this); //основной слой
QBoxLayout* layout2 = new QBoxLayout(QBoxLayout::Direction::LeftToRight, this);

layout->setMargin(70);     // установка отступов по 70 пикселей со всех сторон

layout2->addWidget(b1, 1); //2й параметр - strech - размер кнопки (динамично изменяется)
layout2->addStrech(1);     //установка растяжителя между кнопками

layout2->addWidget(b2, 2); 

layout->addWidget(b3); 
layout->addLayout(layout2); // добавляем второй слой на первый
layout->addWidget(b4); 

QWidget* wgt = new QWidget(this); // вспомогательный виджет
wgt->setLayout(layout);           //накидываем на него слой 
setCentralWidget(wgt);            //устанавливаем в качестве центрального
</pre></code>

Вместо обобщенного `QBoxLayout` можно использовать специализированные классы `QHBoxLayout` и 
`QVBoxLayout`.

Пример для QGridLayout:
<pre><code>
QPushButton* b1 = new QPushButton("A", this);
QPushButton* b2 = new QPushButton("B", this);
QPushButton* b3 = new QPushButton("C", this);
QPushButton* b3 = new QPushButton("C", this);

QGridLayout* layout = new QGridLayout(this);

layout->addWidget(b1, 0, 0, 1 , 1); //кнопка левая
//addwidget(QWidget*, int row, int column, int rowSpan, int columnSpan, Qt::Alignment = 
Qt::Alignment())
layout->addWidget(b2, 0, 1, 1 , 1); // кнопка правая
layout->addWidget(b3, 1, 0, 1 , 2); // длинная
layout->addWidget(b4, 2, 0, 2, 1);  // высокая
</pre></code>


__4) таблицы стилей__
---------------------

Таблица стилей похожа на CSS-разметку в веб-программировании. Таблицы стилей — текстовые 
спецификации, которые могут быть установлены для всего приложения с помощью 
QApplication::setStyleSheet() или для определенного виджета (и его потомков) посредством 
QWidget::setStyleSheet(). Если на различных уровнях установлено несколько таблиц стилей, то 
Qt сводит их в одну. Это называется каскадированием.

<pre><code>
setStyleSheet("QPushButton {font: bold 14 px; background-color: red;}
QPushButton:pressed{background-color: yellow;}  // для нажатого состояния
QMainWindow{background-color:grey}");

b1->setStyleSheet("QPushButton{background-color: blue;}"); //стиль для отдельной кнопки

</pre></code>

Все виджеты в Qt содержат палитру и используют ее для отрисовки. Основные классы для работы 
с палитрой — `QColor` и `QPalette`.

Конструктор QColor создает цвет на основе значений RGB. Чтобы создать QColor на основе 
значений HSV или CMYK, используйте функции `toHsv()` и `toCmyk()` соответственно. Эти 
функции возвращают копию цвета, используя нужный формат. Кроме того, статические функции 
`fromRgb()`, `fromHsv()` и `fromCmyk()` создают цвета из указанных значений. Цвет может быть 
преобразован в любой из трех форматов с помощью функции `convertTo()` (возвращающей копию 
цвета в нужном формате) или функций `setRgb()`, `setHsv()` и `setCmyk()`, изменяющих цветовой
формат.  
Функция `spec()` сообщает, как был указан цвет. Цвет можно установить, передав 
строку RGB (например __#ffffff__ — белый цвет, __#000000__ — черный) или строку ARGB 
(например __#ff112233__) или имя цвета (например blue) в функцию `setNamedColor()`. 
Названия цветов взяты из имен цветов SVG 1.0. Функция `name()` возвращает название цвета 
в формате #RRGGBB.  

Цвета также могут быть установлены с помощью setRgb(), setHsv() и setCmyk(). Чтобы получить 
более светлый или более темный цвет, используются функции lighter() и darker() 
соответственно.


__5) Создание виджетов__
------------------------  

Базовый класс QWidget, подключить __QWidget__, добавить __QObject__.  

QString().setNum() - метод setNum() класса QString преобразует число в строку и 
устанавливает полученную строку как значение объекта QString. Он принимает целое или 
вещественное число в качестве аргумента и может также принимать необязательное основание 
(например, 2, 10 или 16) для преобразования. Например, вызов setNum(42) на объекте QString 
установит его значение равным "42".


__Идея для текстового редактора__ 
---------------------------------

Реализовать парсер для своего синтаксиса, который позволит разнообразить визуализацию 
набираемого текста:  
- Жирный текст, курсив;
- Коментарии;
- Выделение слов, строк и символов.

Реализовать открытие и создание новых документов с помощью вкладок (Многодокументный 
интерфейс - урок 6)

Реализовать шаблоны по примеру Word