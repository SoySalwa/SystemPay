#include <QApplication>
#include "mainwindow.h"

int main(int argc, char **argv)
{
    QApplication a(argc, argv);
    QApplication::setApplicationName("The System Pay");
    MainWindow w;
    w.resize(1280, 720);
    w.show();

    return QApplication::exec();
}
