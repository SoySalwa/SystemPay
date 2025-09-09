#include <QApplication>
#include "mainwindow.h"
#include "ThemeManager.h"

int main(int argc, char **argv)
{
    QApplication a(argc, argv);
    a.setStyle("Fusion");
    a.setPalette(ThemeManager::instance()->allThemes()["Tema Oscuro"].palette);
    QApplication::setApplicationName("The System Pay");
    MainWindow w;
    w.resize(1280, 720);
    w.show();

    return QApplication::exec();
}
