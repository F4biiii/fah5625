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
        QIcon icon("../grid/thi_icon.png");
        setWindowTitle("Grid");
        setWindowIcon(icon);
        //resize(200, 25);
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
