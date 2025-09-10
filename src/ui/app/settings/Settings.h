
#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLineEdit>
#include <QCheckBox>
#include <QDialogButtonBox>
#include <QApplication>
#include <QPixmap>
#include <QPainter>
#include <QSettings>
#include "systembuttons.h"
class SystemButtons;
struct OSType
{
    QString osName;
};

struct App
{
    QString nameTitle;
};

class Settings : public QDialog
{
    Q_OBJECT
public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings() override = default;
    QDialog *createAppSettings();
    QDialog *createNewUser();
    void applyTheme(const QString &themeName) const;
    QPixmap recolorPixmap(const QString &path, const QColor &color) const;

private:
    App AppSettings;
    OSType osType;
    SystemButtons *systemButtons;
};

#endif // SETTINGS_H