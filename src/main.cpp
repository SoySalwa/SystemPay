#include <QApplication>
#include "mainwindow.h"

int main(int argc, char **argv)
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("The System Pay");
    w.resize(1280, 720);
    w.show();

    return QApplication::exec();
}
