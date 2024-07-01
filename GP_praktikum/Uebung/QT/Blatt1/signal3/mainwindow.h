#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QPushButton>
#include <string>
#include <iostream>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

private:
    void resizeEvent(QResizeEvent *event);
    QPushButton *button;
};

#endif // MAINWINDOW_H
