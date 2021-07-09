#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QApplication *parent):

QMainWindow(),ui(new Ui::MainWindow) {
    ui->setupUi(this);

    openAction = new QAction(tr("&Открыть"), this); //Открыть
    connect(openAction, SIGNAL(triggered()), this, SLOT(open())); //Соединяем слот

    saveAction = new QAction(tr("&Сохранить"), this); //Сохранить
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save())); //Соединяем слот

    exitAction = new QAction(tr("&Выход"), this); //Выйти
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close())); //Соединяем слот

    fileMenu = this->menuBar()->addMenu(tr("&Файл")); //пункт меню

    //Тут действия
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addSeparator(); //вот эта полосочка графического характера
    fileMenu->addAction(exitAction);

    textEdit = new QTextEdit();
    setCentralWidget(textEdit);
    setWindowTitle(tr("Блокнот D and M"));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::open() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Открыть файл"), "", tr("Текстовые файлы (*.txt);"));
    if (fileName != "") {
        QFile file(fileName);

        //а тут у проверка на readmode
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Ошибка"), tr("Не могу открыть файл"));
            return;
        }

        QTextStream in(&file);
        textEdit->setText(in.readAll());
        file.close();
    }
}

void MainWindow::save() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Сохранить файл"), "", tr("Текстовые файлы (*.txt);"));

    if (fileName != "") {
        QFile file(fileName);

        //так же само, но на write
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox msgBox; msgBox.setText("Не могу записать файл"); msgBox.exec();
        } else {
            QTextStream stream(&file);
            stream << textEdit->toPlainText();
            stream.flush();
            file.close();
        }
    }
}

