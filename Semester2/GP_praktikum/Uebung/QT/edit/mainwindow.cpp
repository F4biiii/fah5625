#include "mainwindow.h"

MainWindow::MainWindow()
{
    QIcon icon("../edit/thi_icon.png");
    setWindowTitle("Edit");
    setWindowIcon(icon);
    resize(200, 25);
    edit = new QLineEdit();
    setCentralWidget(edit);
    connect(edit, SIGNAL(returnPressed()), this, SLOT(changeText()));
}

MainWindow::~MainWindow()
{
    delete edit;
}

void MainWindow::changeText()
{
    setWindowTitle(edit->text());
}
