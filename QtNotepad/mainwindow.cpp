#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QApplication *parent):

QMainWindow(),ui(new Ui::MainWindow) {
    ui->setupUi(this);
    //После этой строчки - наши действия!
    openAction = new QAction(tr("&Открыть"), this);
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));
    saveAction = new QAction(tr("&Сохранить"), this);
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));
    exitAction = new QAction(tr("&Выход"), this);
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
    fileMenu = this->menuBar()->addMenu(tr("&Файл"));
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);
    textEdit = new QTextEdit();
    setCentralWidget(textEdit);
    setWindowTitle(tr("Блокнот"));
}

MainWindow::~MainWindow() { delete ui; }

//Ниже - наши методы класса
void MainWindow::open() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Открыть файл"), "", tr("Текстовые файлы (*.txt);;Файлы C++ (*.cpp *.h)"));
    if (fileName != "") {
        QFile file(fileName);

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
    QString fileName = QFileDialog::getSaveFileName(this, tr("Сохранить файл"), "", tr("Текстовые файлы (*.txt);;Файлы C++ (*.cpp *.h)"));

    if (fileName != "") {
        QFile file(fileName);

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

