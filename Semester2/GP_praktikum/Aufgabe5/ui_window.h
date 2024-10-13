#ifndef UI_WINDOW_H
#define UI_WINDOW_H

#include <QMainWindow>
#include "ui_widget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow()
    {
        QIcon icon("D:/daten/Informatik/repos/fah5625/GP_praktikum/Aufgabe5/thi_icon.png");
        setWindowTitle("Ufo");
        setWindowIcon(icon);
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

#endif // UI_WINDOW_H
