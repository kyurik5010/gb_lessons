Notes:

Работа с данными в Qt: последовательные и ассоциативные контейнеры, итераторы  
Итераторы в стиле джава и stl  
QMap, QString, QStringList  

QString y = "AbcDefGhiJklMnoPqrStuVwzYz";  

y.indexOf("jkl", 0, Qt::CaseSensitivity::CaseInsensitive);  
При изменении case sensitivity нужно учитывать, что это enum и, если задать не все 
параметры метода .indexOf(QLatin1StringView str, qsizetype from = 0, Qt::CaseSensitivity cs 
= Qt::CaseSensitive)), а, например, задать только искомую подстроку и 
Qt::CaseSensitivity::CaseInsensitive (==1), то он воспримет это, как аргументы 1му и 2му 
(qsizetype from = 0) параметрам, не изменив при этом 3й - Qt::CaseSensitivity

Парсинг текста с использованием стандартных методов и регулярных выражений

2) Работа с изображениями  
QPixmap pix("picture.png"); // неполный путь, т.к. файл вместе с исполняемым находится  
вариант_1:  
	QPallete pal;  
	pal.setbrush(QPallete::Background, pix);  
	setPallete(pal);  
вариант_2:  
	pix = pix.scaled(ui->label->width(), ui->label->height(), Qt::AspectRatioMode); // 
привязка масштаба к размерам лейбла  
	ui->label->setPixmap(pix);  

3) Ресурсы программы  
Добавить новый - Qt - Файл ресурсов Qt (qrc)  
Добавить префикс (как отдельная папка)  
Добавить файлы  
Скопировать путь до ресурса в буфер обмена   
Вставить строку в конструктор объекта QPixmap  

Файлы размещаемые в ресурсах программы неизменяемы, доступны только для чтения  

4) Работа с файлами  
#include <QDir>  

получение содержимого дирректории:  

QDir dir; // в конструктор объекта QDir можно передавать строку с путем к интересующей 
дирректории  
dir.setFilter(QDir::Files | QDir::Hidden | QDir::Dirs);  
QFileInfoList list = dir.entryInfoList();  
foreach(QFileInfo item, list)  
	qDebug() << item.filename();  

открыть, закрыть, создавать и читать файлы  

    
	//This code opens a file called "myfile.txt" in write-only mode and writes the 
contents of a plain text edit box to the file.   
	QFile myFile("./myfile.txt"); //Create QFile object to open the file  
	
	//Check if the file is opened in write-only mode  
	if(myFile.open(QIODevice::WriteOnly | QIODevice::Text))  
	{  
    		//Store the contents of the plain edit box in a QString object  
		QString text = ui->plainTextEdit->toPlainText();  
    		
		//Convert the contents of the plain text edit box UTF-8 encoded string  
    		QByteArray ba = text.toUtf8();   
    
    		//Write the UTF-8 encoded string to the file  
		myFile.write(ba, ba.length);  
    
		//Close the file  
    		myFile.close();  
	}   
    
	
	еще вариант использовать QTextStream вместо ByteArray:  

        // Create a QTextStream object to write to the file  
        QTextStream out(&myFile);  

        // Write some text to the file  
        out << "This is some text that I am writing to the file.";  


Выбор пользователем файла (файловый диалог)  

QString filepath = QFileDialog::getOpenFileName();  
если путь пустой - значит пользователь нажал "отмена"  

QFileDialog::getSaveFileName(); - для диалогового окна для сохранения  
