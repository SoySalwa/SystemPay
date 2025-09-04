#ifndef SYSTEMCOLORS_H
#define SYSTEMCOLORS_H

#include <QObject>
#include <QString>

class SystemColors : public QObject{
    Q_OBJECT
public:
    SystemColors();

    static QString bg_colorBlack();
    static QString bg_colorPastelBlack();
    static QString bg_colorTonteBlack();

    static QString bg_buttonToolbar();
    static QString bg_buttonHoverToolbar();
    static QString bg_buttonFocusToolbar();
    static QString bg_colorBlackYems();
};

#endif // SYSTEMCOLORS_H
