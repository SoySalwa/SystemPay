#include "Settings.h"
#include "ButtonStyle.h"
#include "ThemeManager.h"

Settings::Settings(QWidget *parent) : QDialog(parent)
{
    AppSettings.nameTitle = QApplication::applicationName();

#ifdef Q_OS_WIN
    osType.osName = "Windows";
#elif defined(Q_OS_LINUX)
    osType.osName = "Linux";
#endif
}

QDialog *Settings::createAppSettings()
{
    QLayout *layout = this->layout();
    if (layout)
    {
        QLayoutItem *item;
        while ((item = layout->takeAt(0)) != nullptr)
        {
            if (item->widget())
            {
                item->widget()->deleteLater();
            }
            delete item;
        }
        delete layout;
    }
    this->setWindowTitle("Configuración");
    this->resize(400, 300);
    QSettings settings(QApplication::applicationName());

    QGridLayout *hlayout = new QGridLayout(this);
    hlayout->setVerticalSpacing(40);
    systemButtons = new SystemButtons(this);
    QPushButton *newUser = systemButtons->createButton(":/icons/add.png", "Nuevo Usuario", "New User", [=]()
                                                       { this->createNewUser()->exec(); });
    newUser->setStyleSheet(ButtonStyle::buttonNormalColor());
    QLineEdit *appName = new QLineEdit(this);
    QComboBox *themeBox = new QComboBox(this);
    themeBox->setObjectName("comboTheme");
    themeBox->addItems({"Tema Oscuro",
                        "Tema Claro",
                        "Tema Pantano",
                        "Tema Cielo"});
    QString m_theme;
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    QPushButton *okButton = buttonBox->button(QDialogButtonBox::Ok);

    QString saveTheme = settings.value("Theme").toString().trimmed();
    int index = themeBox->findText(saveTheme);

    if (index != -1)
    {
        themeBox->setCurrentIndex(index);
    }

    connect(okButton, &QPushButton::clicked, this, [this, themeBox]()
            {
    QString theme = themeBox->currentText();
    ThemeManager::instance()->setTheme(theme); 
                accept(); });

    QString currentTheme = settings.value("currentTheme")
                               .toString()
                               .trimmed();
    themeBox->setCurrentText(currentTheme);
    QString chMessage = QString("Iniciar %1 en el inicio de %2.").arg(AppSettings.nameTitle).arg(osType.osName);
    QCheckBox *check = new QCheckBox(chMessage, this);

    buttonBox->setObjectName("buttonBox");

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    appName->setText(AppSettings.nameTitle);
    appName->setEnabled(false);
    hlayout->addWidget(appName, 0, 0);
    hlayout->addWidget(newUser, 0, 1);
    hlayout->addWidget(themeBox, 1, 0);
    hlayout->addWidget(check, 2, 0, 1, 2);
    hlayout->addWidget(buttonBox, 3, 0, 1, 2);
    return this;
}

QPixmap Settings::recolorPixmap(const QString &path, const QColor &color) const
{
    QPixmap pixmap(path);
    QPixmap colored(pixmap.size());
    colored.fill(Qt::transparent);

    QPainter painter(&colored);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.drawPixmap(0, 0, pixmap);
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.fillRect(colored.rect(), color);
    painter.end();

    return colored;
}

QDialog *Settings::createNewUser()
{
    QDialog *newUserDialog = new QDialog();
    newUserDialog->setWindowTitle("Añadir Nuevo Usuario");
    newUserDialog->resize(300, 200);

    QVBoxLayout *layout = new QVBoxLayout(newUserDialog);
    layout->setSpacing(15); // espacio entre widgets
    layout->setAlignment(Qt::AlignCenter);

    auto addCenteredWidget = [&](QWidget *w)
    {
        w->setFixedWidth(300); // opcional: limitar ancho
        QHBoxLayout *hLayout = new QHBoxLayout();
        hLayout->addStretch(1);
        hLayout->addWidget(w);
        hLayout->addStretch(1);
        layout->addLayout(hLayout);
    };

    QLineEdit *userName = new QLineEdit();
    userName->setPlaceholderText("Nombres");

    QLineEdit *jobTitle = new QLineEdit();
    jobTitle->setPlaceholderText("Cargo");

    QLineEdit *iDocument = new QLineEdit();
    iDocument->setPlaceholderText("Documento de identidad");

    QLineEdit *userPassword = new QLineEdit();
    userPassword->setPlaceholderText("Contraseña");

    QPushButton *createUserBtn = systemButtons->createButton(
        ":/icons/add.png", "Crear Usuario", "CreateUser", []() {});
    createUserBtn->setStyleSheet(ButtonStyle::buttonNormalColor());
    createUserBtn->setFixedWidth(150); // opcional

    // Agregar widgets centrados
    addCenteredWidget(userName);
    addCenteredWidget(jobTitle);
    addCenteredWidget(iDocument);
    addCenteredWidget(userPassword);
    addCenteredWidget(createUserBtn);

    return newUserDialog;
}
