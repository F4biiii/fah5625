#include "mainwindow.h"

MainWindow::MainWindow()
{
    QIcon icon("../signal/thi_icon.png");
    setWindowTitle("Signal");
    setWindowIcon(icon);
    button = new QPushButton("Hello world");
    setCentralWidget(button);
    connect(button, SIGNAL(pressed()), this, SLOT(changeText()));
    connect(button, SIGNAL(released()), this, SLOT(changeText()));
}

MainWindow::~MainWindow()
{
    delete button;
}

void MainWindow::changeText()
{
    toggle = !toggle;
    if(toggle) {
        button->setText(QString::fromStdString(text));
    } else {
        button->setText("Hello world");
    }
}
