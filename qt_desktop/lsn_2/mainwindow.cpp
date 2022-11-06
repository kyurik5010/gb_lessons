#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tsk1_TB_2->setPlainText("© - ${CPW}\n‰ - ${PML}\n™ - ${TMK}\n€ - ${EUR}\n✔ - ${CHK}");

    model = new QStandardItemModel(this); //инициализировать указатель на тип модели QStringListModel и передать ему указатель на класс


    model->appendRow(new QStandardItem(QIcon("./icons/Cpp.png"), "C++"));
    model->appendRow(new QStandardItem(QIcon("./icons/Java.png"), "Java"));
    model->appendRow(new QStandardItem(QIcon("./icons/Csharp.png"), "C#"));
    model->appendRow(new QStandardItem(QIcon("./icons/Python.png"), "Python"));
    model->appendRow(new QStandardItem(QIcon("./icons/PHP.png"), "PHP"));
    model->appendRow(new QStandardItem(QIcon("./icons/JS.png"), "JavaScript"));

    ui->tsk2_list->setModel(model); //задать виждету указатель на модель
    ui->tsk2_list->setIconSize(QSize(25,25));

    ui->tsk2_list->setEditTriggers(QAbstractItemView::EditTrigger::DoubleClicked);
    ui->tsk2_list->setDragDropMode(QAbstractItemView::DragDropMode::InternalMove);

    //QHorizontalHeaderView

    model2 = new QStringListModel(this);
    selectionModel = new QItemSelectionModel(model2, this);


    ui->tsk3_tableView->setModel(model2);
    ui->tsk3_tableView->setSelectionModel(selectionModel);

    QStringList list = {"Не работает", "no.", "Имя компьютера", "IP адрес", "MAC адрес"};

    model2->setStringList(list);
    model2->insertRow(1);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_tsk1_TB_textChanged()
{
    while(1)
    {
        QString text_to_parse = ui->tsk1_TB->toPlainText();
        std::optional<QPair<int, QString>> result = parser.parse(text_to_parse);
        if(result == std::nullopt)
            return;
        QString str = parser.reconstruct(text_to_parse, result.value());
        ui->tsk1_TB->setPlainText(str);

    }
}


void MainWindow::on_tsk2_checkBox_stateChanged()
{
    if(ui->tsk2_checkBox->isChecked())
    {
        ui->tsk2_list->clearPropertyFlags();
        ui->tsk2_list->setViewMode(QListView::IconMode);
    }
    else
    {
        ui->tsk2_list->clearPropertyFlags();
        ui->tsk2_list->setViewMode(QListView::ListMode);
    }
}


void MainWindow::on_tsk2_pushButton_clicked()
{
    model->appendRow(new QStandardItem(QIcon("./icons/new.png"), "new"));
}


void MainWindow::on_tsk2_pushButton_2_clicked()
{
    model->removeRow(ui->tsk2_list->currentIndex().row());
}


void MainWindow::on_tsk3_pushButton_clicked()
{
    if(!selectionModel->hasSelection())
        return;

    auto list = selectionModel->selectedIndexes();
    auto iter = list.begin();
    //auto size = list.size();

    for(; iter <= list.end(); ++iter)
    {
        model2->setData(*iter, QColor(Qt::yellow), Qt::BackgroundRole);
    }
}

