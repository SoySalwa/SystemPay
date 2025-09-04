#include "settingsapp.h"
#include "MongoConnection.h"
#include <QSettings>
#include "windowshandlers.h"

SettingsApp::SettingsApp() {}

bool SettingsApp::SessionRemember(QVBoxLayout* mainLayout) {
    QSettings settings("SPCEA - SystemPay");

    QString user_logged = settings.value("matricule").toString().trimmed();
    QString user_password = settings.value("password").toString().trimmed();

    qDebug() << "Usuario almacenado:" << user_logged;
    qDebug() << "Contraseña almacenada:" << user_password;

    if (!user_logged.isEmpty() && !user_password.isEmpty()) {
        qDebug() << "Sesión iniciada automáticamente como:" << user_logged;
        if (MongoConnection::getInstance().validateLogin(user_logged, user_password)) {
            qDebug() << "Login exitoso.";
            qDebug() << "Cargando interfaz...";

            WindowsHandlers *windows = new WindowsHandlers();
            windows->createInterfaceWindow(mainLayout);
            return true;
        } else {
            qDebug() << "Error al validar el login.";
        }
    } else {
        qDebug() << "No se encontró sesión guardada.";
    }
    return false;
}

