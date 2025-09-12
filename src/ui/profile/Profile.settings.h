#ifndef PROFILESETTINGS_H
#define PROFILESETTINGS_H

#include <QDialog>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include <QFrame>
#include <QGridLayout>
#include <QLineEdit>
#include <QPainter>
#include <QPainterPath>
#include <QFileDialog>
#include <QDir>
#include <ThemeManager.h>
#include "WidgetStyle.h"
#include "PixmapUtils.h"

class Profile : public QDialog
{
    Q_OBJECT

public:
    Profile(QWidget *parent = nullptr);
    ~Profile() override = default;
    QDialog *createUserProfile();
private:
};

#endif // PROFILESETTINGS_H