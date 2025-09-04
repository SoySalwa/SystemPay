#ifndef QLMESSAGE_H
#define QLMESSAGE_H

#include <QLabel>
#include <QPropertyAnimation>
#include <QTimer>

class QLMessage : public QLabel {
private:

public:

    void messageAlert(QWidget *parent, const QString &message) {
        if (!parent) {
            qDebug() << "No se encontró el Widget.";
            return;
        }

        static QLabel *msgIsActive = nullptr;

        if (msgIsActive) {
            return;
        }

        QLabel *msg = new QLabel(parent);
        msg->setStyleSheet("QLabel { color: #e03926; font-size: 12pt; background-color: #8e0f00; border-radius: 15px; padding: 10px; }");
        msg->setText(message);

        // Ajusta el tamaño del mensaje según el contenido
        msg->adjustSize();

        const int marginTop = 30; // Distancia desde la parte superior
        int x = (parent->width() - msg->width()) / 2; // Centrado horizontalmente
        int startY = -msg->height(); // Fuera de la ventana (invisible al inicio)
        int endY = marginTop; // Posición final del mensaje

        // Mueve el mensaje a su posición inicial (fuera de la vista)
        msg->move(x, startY);
        msg->show();

        msgIsActive = msg;

        // Animación de entrada
        QPropertyAnimation *animation = new QPropertyAnimation(msg, "pos");
        animation->setDuration(1000); // Duración de la animación en milisegundos
        animation->setStartValue(QPoint(x, startY));
        animation->setEndValue(QPoint(x, endY));
        animation->setEasingCurve(QEasingCurve::OutBounce); // Efecto de rebote al final
        animation->start(QAbstractAnimation::DeleteWhenStopped);

        // Oculta el mensaje después de 5 segundos
        QTimer::singleShot(5000, [msg, animation]() {
            // Animación de salida
            QPropertyAnimation *exitAnimation = new QPropertyAnimation(msg, "pos");
            exitAnimation->setDuration(1000);
            exitAnimation->setStartValue(msg->pos());
            exitAnimation->setEndValue(QPoint(msg->x(), -msg->height()));
            exitAnimation->setEasingCurve(QEasingCurve::InBack);

            // Elimina el mensaje después de la animación de salida
            QObject::connect(exitAnimation, &QPropertyAnimation::finished, msg, &QLabel::deleteLater);
            exitAnimation->start(QAbstractAnimation::DeleteWhenStopped);
            msgIsActive = nullptr;
        });
    }

    void messageSaves(QWidget *parent, const QString &message) {
        if (!parent) {
            qDebug() << "No se encontró el Widget.";
            return;
        }

        QLabel *msg = new QLabel(parent);
        msg->setStyleSheet("QLabel { color: green; font-size: 12pt; background-color: #003220; border-radius: 15px; padding: 10px; }");
        msg->setText(message);

        // Ajusta el tamaño del mensaje según el contenido
        msg->adjustSize();

        const int marginTop = 30; // Distancia desde la parte superior
        int x = (parent->width() - msg->width()) / 2; // Centrado horizontalmente
        int startY = -msg->height(); // Fuera de la ventana (invisible al inicio)
        int endY = marginTop; // Posición final del mensaje

        // Mueve el mensaje a su posición inicial (fuera de la vista)
        msg->move(x, startY);
        msg->show();

        // Animación de entrada
        QPropertyAnimation *animation = new QPropertyAnimation(msg, "pos");
        animation->setDuration(1000); // Duración de la animación en milisegundos
        animation->setStartValue(QPoint(x, startY));
        animation->setEndValue(QPoint(x, endY));
        animation->setEasingCurve(QEasingCurve::OutBounce); // Efecto de rebote al final
        animation->start(QAbstractAnimation::DeleteWhenStopped);

        // Oculta el mensaje después de 5 segundos
        QTimer::singleShot(2000, [msg, animation]() {
            // Animación de salida
            QPropertyAnimation *exitAnimation = new QPropertyAnimation(msg, "pos");
            exitAnimation->setDuration(1000);
            exitAnimation->setStartValue(msg->pos());
            exitAnimation->setEndValue(QPoint(msg->x(), -msg->height()));
            exitAnimation->setEasingCurve(QEasingCurve::InBack);

            // Elimina el mensaje después de la animación de salida
            QObject::connect(exitAnimation, &QPropertyAnimation::finished, msg, &QLabel::deleteLater);
            exitAnimation->start(QAbstractAnimation::DeleteWhenStopped);
        });
    }
};

#endif // QLMESSAGE_H
