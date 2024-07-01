#include "mainwindow.h"
#include "qevent.h"

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

void MainWindow::resizeEvent(QResizeEvent *event) {
    QSize a = event->size();
    QString output = QString::number(a.width()) + "/" + QString::number(a.height());
    button->setText(output);
}
