#pragma once

#include <QMainWindow>
#include <QtWidgets>

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow {
 Q_OBJECT

public:
     explicit MainWindow(QApplication *parent = 0);
     ~MainWindow();
private slots:
     void open(); //метод для открытия файла
     void save(); //метод для сохранения файла
private:
     Ui::MainWindow *ui;
     QTextEdit *textEdit; //указатель на поле ввода текста
     QAction *openAction; //указатели на действия "Открыть",
     QAction *saveAction; //"Сохранить"
     QAction *exitAction; //и "Выйти"
     QMenu *fileMenu; //Указатель на меню
};
