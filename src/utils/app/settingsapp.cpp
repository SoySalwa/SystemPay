#include "settingsapp.h"
// #include "MongoConnection.h"
#include <QSettings>
// #include "windowshandlers.h"
#include <QComboBox>
#include "ThemeManager.h"

SettingsApp::SettingsApp(QWidget *parent)
    : QDialog(parent)
{
    QComboBox *comboTheme = findChild<QComboBox *>("comboTheme");
    QDialogButtonBox *buttonBox = findChild<QDialogButtonBox *>("buttonBox");
    QPushButton *okButton = buttonBox->button(QDialogButtonBox::Ok);
    QPushButton *cancelButton = buttonBox->button(QDialogButtonBox::Cancel);

    // Leer tema guardado
    QSettings settings(QCoreApplication::applicationName());
    QString savedTheme = settings.value("themeName", "Tema Oscuro").toString();

    // Aplicar tema guardado al abrir el diálogo
    ThemeManager::instance()->setTheme(savedTheme);

    // Llenar combo con los nombres de tema y seleccionar el actual
    comboTheme->addItems(ThemeManager::instance()->allThemes().keys());
    comboTheme->setCurrentText(savedTheme);

    // Guardar y aplicar al pulsar OK
    connect(okButton, &QPushButton::clicked, this, [comboTheme]()
            {
        QString selectedTheme = comboTheme->currentText();

        QSettings settings(QApplication::organizationName(), QApplication::applicationName());
        settings.setValue("themeName", selectedTheme);
        settings.sync();

        ThemeManager::instance()->setTheme(selectedTheme); });

    // Cerrar diálogo al aceptar o cancelar
    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

/*
bool SettingsApp::SessionRemember(QVBoxLayout *mainLayout)
{
    QSettings settings("SPCEA - SystemPay");

    QString user_logged = settings.value("matricule").toString().trimmed();
    QString user_password = settings.value("password").toString().trimmed();

    qDebug() << "Usuario almacenado:" << user_logged;
    qDebug() << "Contraseña almacenada:" << user_password;

    if (!user_logged.isEmpty() && !user_password.isEmpty())
    {
        qDebug() << "Sesión iniciada automáticamente como:" << user_logged;
        if (MongoConnection::getInstance().validateLogin(user_logged, user_password))
        {
            qDebug() << "Login exitoso.";
            qDebug() << "Cargando interfaz...";

            WindowsHandlers *windows = new WindowsHandlers();
            windows->createInterfaceWindow(mainLayout);
            return true;
        }
        else
        {
            qDebug() << "Error al validar el login.";
        }
    }
    else
    {
        qDebug() << "No se encontró sesión guardada.";
    }
    return false;
} */