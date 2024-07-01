#include "mainwindow.h"

MainWindow::MainWindow()
{
    QIcon icon("../hello/thi_icon.png");
    setWindowTitle("Hello");
    setWindowIcon(icon);
    button = new QPushButton("Hello world");
    setCentralWidget(button);
}

MainWindow::~MainWindow()
{
    delete button;
}
