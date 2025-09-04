#ifndef SYSTEMBUTTONS_H
#define SYSTEMBUTTONS_H

#include <QObject>
#include <QPushButton>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include "QLMessage.h"
#include "mainwindow.h"

class SystemButtons : QObject
{
    Q_OBJECT
private:
    QPushButton *addStudentBtn;
    QVBoxLayout *mainLayout;
    QWidget *contentArea;

public:
    explicit SystemButtons(QObject *parent);
    QPushButton *active_button = nullptr;
    QLMessage message;
signals:
    void buttonDeactivated(QPushButton *oldButton);

public slots:
    void onAddStudentClicked();
    void onUpdStudentClicked();
    void onReportsClicked();
    void onPayStudent();
    void onBtnInscriptionClicked();
    void onBtnCloseClicked();
    QWidget *onlogoutButton();

    QPushButton *createButton(const QString &icon_path, const QString &label, const QString &objectName, const std::function<void()> &onClick = nullptr);
};

#endif // SYSTEMBUTTONS_H
