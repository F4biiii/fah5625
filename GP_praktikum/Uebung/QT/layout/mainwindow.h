#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mainwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow()
    {
        QIcon icon("../layout/thi_icon.png");
        setWindowTitle("Layout");
        setWindowIcon(icon);
        resize(50,20);
        mainwidget = new MainWidget(this);
        setCentralWidget(mainwidget);
    }

    ~MainWindow()
    {
        delete mainwidget;
    }

private:
    MainWidget *mainwidget;
};

#endif // MAINWINDOW_H
