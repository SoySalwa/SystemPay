#include "Settings.h"
#include "systembuttons.h"
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

    QGridLayout *hlayout = new QGridLayout(this);
    hlayout->setVerticalSpacing(40);
    SystemButtons *systemButtons = new SystemButtons(this);
    QPushButton *newUser = systemButtons->createButton(":/icons/add.png", "Nuevo Usuario", "New User", []()
                                                       {
                                                           // This lambda is intentionally left empty for now.
                                                       });
    newUser->setStyleSheet(ButtonStyle::buttonNormalColor());
    QLineEdit *appName = new QLineEdit(this);
    QComboBox *themeBox = new QComboBox(this);
    themeBox->addItems({"Tema Oscuro",
                        "Tema Claro",
                        "Tema Pantano",
                        "Tema Cielo"});

    connect(themeBox, &QComboBox::currentTextChanged, this, [=](const QString &theme)
            { ThemeManager::instance()->setTheme(theme); });

    QString chMessage = QString("Iniciar %1 en el inicio de %2.").arg(AppSettings.nameTitle).arg(osType.osName);
    QCheckBox *check = new QCheckBox(chMessage, this);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
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
