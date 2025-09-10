#ifndef SETTINGSAPP_H
#define SETTINGSAPP_H
#include <QVBoxLayout>
#include <QApplication>
#include <QPushButton>
#include <QDialog>
#include <QDialogButtonBox>
class SettingsApp : public QDialog
{
    Q_OBJECT
public:
    SettingsApp(QWidget *parent = nullptr);
    // bool SessionRemember(QVBoxLayout *mainLayout);
};

#endif // SETTINGSAPP_H
