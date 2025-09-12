#include "Profile.settings.h"

Profile::Profile(QWidget *parent) : QDialog(parent) {
}

QDialog* Profile::createUserProfile() {
    QDialog *dialog = new QDialog();
    dialog->setWindowTitle("Perfil de Usuario");
    dialog->resize(1000, 460);
    dialog->setMinimumSize(dialog->size());
    // --- Layout principal ---
    QGridLayout* gridLayout = new QGridLayout(dialog);

    // --- Tarjeta de perfil ---
    QFrame *card = new QFrame(dialog);
    const Theme &t = ThemeManager::instance()->allThemes()[ThemeManager::instance()->currentTheme()];

    card->setStyleSheet(WidgetStyle::widgetNavBarColor(t.toolBarColor));
    card->setMinimumSize(550, 280);  // tamaño cómodo

    QGridLayout *cardLayout = new QGridLayout(card);
    cardLayout->setContentsMargins(20, 20, 20, 20);  // margen amplio y uniforme
    cardLayout->setSpacing(15);                      // buen respiro entre avatar e info

    // --- Crear un QPixmap circular ---
    QPixmap rounded = PixmapUtils::createCircularPixmap(":/av/default");
    QLabel *avatar = new QLabel(card);
    avatar->setPixmap(rounded);
    avatar->setFixedSize(220, 220);

    QVBoxLayout* infoLayout = new QVBoxLayout();
    infoLayout->setContentsMargins(15, 0, 0, 0);
    infoLayout->setSpacing(8);

    QLabel *username = new QLabel("Nombre de Usuario");
    username->setStyleSheet("font-weight: bold; font-size: 20px;");

    QLabel *licencia = new QLabel("Licencia: <font color='lightgreen'>Gratuita</font>");
    licencia->setStyleSheet("font-size: 16px;");

    QLabel *cargo    = new QLabel("Cargo: <font color='lightgreen'>Administrador</font>");
    cargo->setStyleSheet("font-size: 16px;");

    QPushButton *btnLicencia = new QPushButton("⤴ Cambiar Licencia");
    QPushButton *btnPassword = new QPushButton("Cambiar Contraseña");

    btnLicencia->setStyleSheet("color: #1e90ff; background: transparent; border: none; text-align: left; font-size: 14px;");
    btnPassword->setStyleSheet("color: #1e90ff; background: transparent; border: none; text-align: left; font-size: 14px;");

    infoLayout->addWidget(username);
    infoLayout->addWidget(licencia);
    infoLayout->addWidget(cargo);
    infoLayout->addSpacing(10);
    infoLayout->addWidget(btnLicencia);
    infoLayout->addWidget(btnPassword);
    infoLayout->addStretch();

    cardLayout->addWidget(avatar, 0, 0, Qt::AlignCenter);
    cardLayout->addLayout(infoLayout, 0, 1, Qt::AlignVCenter);

    QPushButton *changeAvatar = new QPushButton("Cambiar Avatar");
    changeAvatar->setStyleSheet(" background: transparent; border: none; font-size: 14px;");
    changeAvatar->setIcon(PixmapUtils::recolorPixmap(":/icons/camera.png", t.iconColor));
    
    QVBoxLayout *avatarColumn = new QVBoxLayout();
    avatarColumn->addWidget(card, 0, Qt::AlignTop);
    avatarColumn->addWidget(changeAvatar, 0, Qt::AlignLeft);
    avatarColumn->addStretch();

    QVBoxLayout* formLayout = new QVBoxLayout();
    QLineEdit* email = new QLineEdit();
    email->setPlaceholderText("Correo Electrónico");
    QLineEdit* phoneNumber = new QLineEdit();
    phoneNumber->setPlaceholderText("Número Telefónico");
    QLineEdit* iDocument = new QLineEdit();
    iDocument->setPlaceholderText("Documento de Identidad");

    formLayout->addWidget(email);
    formLayout->addWidget(phoneNumber);
    formLayout->addWidget(iDocument);
    formLayout->setSpacing(15);
    formLayout->addStretch();

    gridLayout->addLayout(avatarColumn, 0, 0, Qt::AlignTop);
    gridLayout->addLayout(formLayout, 0, 1, Qt::AlignTop);
    
    connect(changeAvatar, &QPushButton::clicked, this, [=]() mutable {
    QString fileName = QFileDialog::getOpenFileName(dialog,
                        "Seleccionar imagen de avatar",
                        QDir::homePath(),
                        "Imágenes (*.png *.jpg *.jpeg *.bmp)");

    if (!fileName.isEmpty()) {
        QPixmap newAvatar = PixmapUtils::createCircularPixmap(fileName);
        if (!newAvatar.isNull()) {
            avatar->setPixmap(newAvatar);
        }
    }
});
    return dialog;
}