#include <QtWidgets/QApplication>
#include "ui_window.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    w.show();
    return app.exec();
}
