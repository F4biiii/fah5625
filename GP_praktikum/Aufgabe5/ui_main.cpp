#include "ui_window.h"

MainWindow::MainWindow()
{
    QIcon icon("../layout/thi_icon.png");
    setWindowTitle("Ufo");
    setWindowIcon(icon);
    resize(200,0);
    mainwidget = new MainWidget(this);
    setCentralWidget(mainwidget);

}

MainWindow::~MainWindow()
{
    delete mainwidget;
}

