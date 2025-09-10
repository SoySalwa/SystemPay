#include <QApplication>
#include "mainwindow.h"
#include "ThemeManager.h"
#include <QSettings>

int main(int argc, char **argv)
{
    QCoreApplication::setApplicationName("The System Pay");
    QCoreApplication::setOrganizationName("System");

    QApplication a(argc, argv);
    QApplication::setStyle("Fusion");

    // Leer tema guardado
    QSettings settings(QApplication::applicationName());
    QString savedTheme = settings.value("Theme", "Tema Oscuro").toString().trimmed();

    // Aplicar el tema primero
    if (ThemeManager::instance()->allThemes().contains(savedTheme))
    {
        ThemeManager::instance()->setTheme(savedTheme);
    }
    else
    {
        ThemeManager::instance()->setTheme("Tema Oscuro");
    }
    // Ahora crear el MainWindow
    MainWindow w;
    w.resize(1280, 720);
    w.setMinimumSize(w.size());
    w.setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
    w.show();

    return QApplication::exec();
}
