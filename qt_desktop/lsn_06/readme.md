__Заметки__
==========

__1) Многодокументный интерфейс__
----------------------------------------  

Главное окно предоставляет структуру для создания пользовательского интерфейса приложения. Класс главного окна __QMainWindow__ имеет свой собственный макет, к которому можно добавить __QToolBars__, __QDockWidgets__, __QMenuBar__ и __QStatusBar__. Центральная область макета может быть занята любым виджетом. Центральным обычно является стандартный виджет Qt, такой как QTextEdit или QGraphicsView.  
Для расширенных приложений также могут быть использованы пользовательские виджеты. Центральный виджет устанавливается функцией `setCentralWidget()`. Главные окна имеют как однодокументный так и многодокументный интерфейс. В качестве центрального виджета для многодокументного интерфейса выбирается QMdiArea.

Создаем центральный виджет, создаем слой и прикрепляем его к центральному виджету. Создаем виджет QMdiArea. С помощью метода __QMdiArea::addSubWindow(QWidget *)__ добавляем два виджета __QTextEdit__. Добавим кнопку и слот. При нажатии кнопки в активный документ запишется слово «Hello». Добавим кнопку в заголовочный файл QMdiSubWindow.
`activeSubWindow()` -  метод получения активного окна виджета __QMdiArea__.
<pre><code>
//cpp
mdi = new QMdiArea(this);
QWidget* wgt = new QWidget(this);
setCentralWidget(wgt);
QGridLayout* layout = new QGridLayout(this);
wgt->setLayout(layout);
layout->addWidget(mdi, 1,0,10,1);
mdi->addSubWindow(new QTextEdit(this));
mdi->addSubWindow(new QTextEdit(this));
QPushButton* btn = new QPushButton("Click me", this);
layout->addWidget(btn, 0,0,1,1);
connect(btn, SIGNAL(clicked()), this, SLOT(on_btn_clicked()));

MyClass::on_btn_clicked(){
    QMdiSubWindow* sub = mdi->activeSubWindow();
    QWidget* widget = sub->widget();
    QTextEdit* textEdit = (QTextEdit*)widget;
    textEdit->append("Hello world");
}

//header
private slots:
    void on_btn_clicked();
</pre></code>  

`QMdiArea::ViewMode()` - режим отображения элементов многодокументного интерфейса. (можно сделать вкалдками, как в браузерах) см.справку

Родительским экраном является любой виджет, если установлено свойство parent = NULL. В этом случае виджет представляет собой окно. Дочерним является окно, способное во время работы блокировать работу родительского окна. К ним относятся диалоговые окна (их также называют модальными). Подкласс QDialog служит для создания собственных диалоговых окон — например для заполнения формы регистрации или окон настройки приложения.

__2) Панель инструментов__
-------------------------------  
Реализуется с помощью класса __QToolBar__ создаваемого через метод `addToolBar()` класса QMainWindow, возвращающий указатель на соответствующий объект. В аргументы метода передается название создаваемого элемента интерфейса. 
<pre><code>
QToolBar* tBar = addToolBar("Menu");
//впоследствии память освобождать не нужно равно как и передавать this в аргументы, т.к. это метод QMainWindow
</pre></code>  

Для добавления какого-то элемента на панель инструментов необходимо добавить действие, что осуществляется через метод `addAction()`, возвращающий объект типа __QAction__:

<pre><code>
QAction* tbAcrion  = tBar -> addAction("some Action");
</pre></code>  

Для использования этого действия нужно подключить сигнал (__triggered()__) к какому-нибудь слоту основного окна:

<pre><code>
connect(tbAcrion, SIGNAL(triggered()), this, SLOT(on_btn_clicked)));
</pre></code>  

Можно разделить область панели инструментов, вставив разрыв панели инструментов (аналогично разрыву строки при редактировании текста) с помощью `addToolBarBreak()` или `insertToolBarBreak()`.   

Также можно ограничить или запретить пользователю возможность перемещение панелей инструментов с помощью `QToolBar::setAllowedAreas()` и `QToolBar::setMovable()`.

Размер значков панели инструментов можно получить с помощью `iconSize()`. Размеры зависят от платформы. Можно установить фиксированный размер функцией `setIconSize()`, а также изменить внешний вид всех кнопок инструментов на панелях инструментов можно с помощью `setToolButtonStyle()`.  

__3) Строка состояния__
---------------------------  
Строка состояния отображает маловажную информацию, например режим работы приложения, в нижней части окна. Для строки состояния используется метод `statusBar()`, возвращающий объект класса __QStatusBar__.
<pre><code>
QStatusBar* statusBar = this->statusBar();
//this т.к. компилятор заподозрит ошибку из-за одинаковых имен указателя и метода
QLabel label = new QLabel(this);
label->setText("test");
QProgressBar* pBar = new QProgressBar(this, "status"); //возможно в аргументы строки не передаются
pBar->setValue(50);
statusBar->addWidget(label);
statusBar->addWidget(pBar);
</pre></code>    

__4) Создание меню__
------------------------  
include QMenuBar
include QApplication
Базовое меню создается объектом класса __QMenu__, возвращаемым методом `menuBar()->addMenu()`.  
<pre><code>
QMenu* menu = menuBar()->addMenu("Menu");
QAction* about = menu->addAction("About");

connect(about, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

menu->addSeparator();
QAction* checkableAction = menu->addAction("checkable action");
checkableAction->setCheckable(true);
checkableAction->setChecked(true);
QAction* imgAction = menu->addAction("Image");
imgAction->setIcon(QPixmap(":/image/my_image.png"));
QAction* disabledAction = menu->addAction("Disabled");
disabledAction->setEnabled(false);
menu->addSeparator();
menu->addAction("Exit", qApp, SLOT(quit())); // такой вариант без сохранения указателя и с эрзац соединением
</pre></code>  

Пример создания подменю:
<pre><code>
QMenu* subMenu = new QMenu("SubMenu");
QAction* subAction1 = subMenu -> addAction("subaction 1");
QAction* subAction2 = subMenu -> addAction("subaction 2");
menu->addAction(subMenu);
</pre></code>

__Часть кнопок может не отображаться из-за глюков__ нужно поиграть с названиями, например "0pen" вместо "Open".  


__5) Выпадающее меню__
----------------------------  

<pre><code>
QPushButton* button = new QPushButton("кнопа", this);
QMenu* someMenu = menuBar()->addMenu("Menu");
QAction* someAction = menu->addAction("Some Action");
button->setMenu()
</pre></code>

Остается только эту кнопку где-то разместить.


__6) Контекстное меню__
----------------------------  

Создадим это в новом виджете (в примере создается новый класс, наследуемый от QTextEdit, т.к. у этого класса уже есть свое контекстное меню. Также необходимо подключить QObject):
<pre><code>
//В целом нужно переопределить событие контекстного меню
//В заголовочнике класса следующий конструктор:
    RusTextEdit(QWidget* parent = nullptr); // - подразумевает, что это самостоятельное окно, которое может блокировать работу основного... кажется как-то так. В последующем, при создании объекта, в конструктор будет передаваться `this`.

protected:
    void contextMenuEvent(QContextMenuEvent* e) override;

private:
    QMenu* menu;

pivate slots:
    void copyText();
    void pasteText();

//В срр:
RusTextEdit::RusTextEdit(QWidget* parent) : QTextEdit(parent) // сюда передается `this` и уходит в кнструктор QTextEdit, от которого наследуется этот виджет
{
    menu = new QMenu(this)
    QAction* copy  = menu->addAction("Копировать");
    QAction* paste = menu->addAction("Вставить");
    connect(copy, SIGNAL(triggered()), this, SLOT(copyText()));
    connect(paste, SIGNAL(triggered()), this, SLOT(pasteText()));
} 


void RusTextEdit::contextMenuEvent(QContextMenuEvent* e)
{
    menu->exec(event->globalPos());
}

// реализация копирования и вставки:

void RusTextEdit::copyText() 
{
    QString str = this->textCursor().selectedText();
    qApp->clipboard()->setText(str);
}

void RusTextEdit::pastText() 
{
    QString str = qApp->clipboard()->text(); 
    this->textCursor().insertText(str);
}
</pre></code>   


__7) Диалоговые окна__
--------------------------  

Демонстрация на примере диалогового окна, вызываемого при закрытии основного окна программы:
<pre><code>
void QMainWindow::clode Event(QCloseEvent* e)
{
    QMessageBox msg(this);
    msg.setText("Вы уверены?");
    msg.setIcon(QMessageBox::Icon::Question);
    msg.addButton("Yes", QMessageBox::YesRole);
    msg.addButton("No", QMessageBox::NoRole);
    msg.addButton("Cancel", QMessageBox::ButtonRole::RejectRole);

    int result = msg.exec(); //запуск через exec() а не show(), т.к. пользователь должен дать ответ

    if(!result) // т.е. "Да"
        e->accept();
    else if(result) // No
        e->ignore();
    else
        e->ignore();
}
</pre></code>

При вызове диалогового окна через метод show нужно привязывать его сигнал finished().


__8) Вывод документов на печать__
--------------------------------------  

Сначала необходимо подключть модкуль `print support`, а также заголовочники `QPrinter` и `QPrintDialog`
<pre><code>
QT  += core gui printsupport
</pre></code>

На примере вызова через некую кнопку:
<pre><code>
void on_SomeButtonClicked()
{
    QPrinter printer;
    QPrintDialog pdiag(&printer, this);
    pdiag.setWindowTitle("Print");
    if(pdiag.exec() != QDialog::Accepted)
        return;
    else
        textEdit->print(&printer);