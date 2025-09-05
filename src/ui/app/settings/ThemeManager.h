#pragma once
#include <QObject>
#include <QString>
#include <QMap>
#include <QPalette>
#include <QColor>
#include <QApplication>

struct Theme
{
    QPalette palette;
    QColor iconColor;
    QColor toolBarColor;
    QString styleSheet;
};

class ThemeManager : public QObject
{
    Q_OBJECT
public:
    static ThemeManager *instance()
    {
        static ThemeManager manager;
        return &manager;
    }

    QString currentTheme() const { return m_theme; }
    const QMap<QString, Theme> &allThemes() const { return themes; }

public slots:
    void setTheme(const QString &themeName)
    {
        if (m_theme == themeName || !themes.contains(themeName))
            return;

        m_theme = themeName;

        QApplication::setPalette(themes[themeName].palette);
        qApp->setStyleSheet(themes[themeName].styleSheet);
        emit themeChanged(m_theme);
    }

signals:
    void themeChanged(const QString &newTheme);

private:
    ThemeManager()
    {
        initThemes();
    }

    void initThemes()
    {
        QPalette lightPalette;
        lightPalette.setColor(QPalette::Window, QColor(245, 245, 245));
        lightPalette.setColor(QPalette::WindowText, Qt::black);
        lightPalette.setColor(QPalette::Base, Qt::white);
        lightPalette.setColor(QPalette::AlternateBase, QColor(230, 230, 230));
        lightPalette.setColor(QPalette::ToolTipBase, Qt::black);
        lightPalette.setColor(QPalette::ToolTipText, Qt::white);
        lightPalette.setColor(QPalette::Disabled, QPalette::Text, QColor(128, 128, 128));
        lightPalette.setColor(QPalette::Active, QPalette::Text, Qt::black);
        lightPalette.setColor(QPalette::Button, QColor(220, 220, 220));
        lightPalette.setColor(QPalette::ButtonText, Qt::black);
        lightPalette.setColor(QPalette::BrightText, Qt::red);
        lightPalette.setColor(QPalette::Link, QColor(0, 120, 215));
        lightPalette.setColor(QPalette::Highlight, QColor(0, 120, 215));
        lightPalette.setColor(QPalette::HighlightedText, Qt::white);
        themes["Tema Claro"] = {lightPalette, Qt::black, "#e0e0e0", ""};

        QPalette darkPalette;
        darkPalette.setColor(QPalette::Window, QColor(28, 28, 33, 255));
        darkPalette.setColor(QPalette::WindowText, Qt::white);
        darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
        darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
        darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
        darkPalette.setColor(QPalette::ToolTipText, Qt::white);
        darkPalette.setColor(QPalette::Disabled, QPalette::Text, QColor(68, 68, 68));
        darkPalette.setColor(QPalette::Active, QPalette::Text, Qt::white);
        darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
        darkPalette.setColor(QPalette::ButtonText, Qt::white);
        darkPalette.setColor(QPalette::BrightText, Qt::red);
        darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
        darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
        darkPalette.setColor(QPalette::HighlightedText, Qt::black);
        themes["Tema Oscuro"] = {darkPalette, Qt::white, "#232323", ""};

        // Tema Azul
        QPalette bluePalette;
        bluePalette.setColor(QPalette::Window, QColor(30, 45, 70));        // fondo general
        bluePalette.setColor(QPalette::WindowText, QColor(200, 220, 255)); // texto claro
        bluePalette.setColor(QPalette::Base, QColor(25, 40, 60));          // base de QLineEdit, QTextEdit
        bluePalette.setColor(QPalette::AlternateBase, QColor(35, 50, 75)); // alternado
        bluePalette.setColor(QPalette::ToolTipBase, Qt::white);
        bluePalette.setColor(QPalette::ToolTipText, Qt::black);
        bluePalette.setColor(QPalette::Disabled, QPalette::Text, QColor(100, 120, 150));
        bluePalette.setColor(QPalette::Active, QPalette::Text, QColor(200, 220, 255));
        bluePalette.setColor(QPalette::Button, QColor(45, 70, 110)); // botones
        bluePalette.setColor(QPalette::ButtonText, QColor(200, 220, 255));
        bluePalette.setColor(QPalette::BrightText, Qt::red);
        bluePalette.setColor(QPalette::Link, QColor(80, 160, 255));
        bluePalette.setColor(QPalette::Highlight, QColor(80, 160, 255));
        bluePalette.setColor(QPalette::HighlightedText, Qt::black);

        // Toolbar color y iconos
        themes["Tema Cielo"] = {bluePalette, QColor(80, 160, 255), "#2d466e", ""};

        // Tema Verde
        QPalette greenPalette;
        greenPalette.setColor(QPalette::Window, QColor(30, 55, 30));        // fondo general
        greenPalette.setColor(QPalette::WindowText, QColor(180, 255, 180)); // texto claro
        greenPalette.setColor(QPalette::Base, QColor(25, 45, 25));          // base de QLineEdit
        greenPalette.setColor(QPalette::AlternateBase, QColor(35, 65, 35)); // alternado
        greenPalette.setColor(QPalette::ToolTipBase, Qt::white);
        greenPalette.setColor(QPalette::ToolTipText, Qt::black);
        greenPalette.setColor(QPalette::Disabled, QPalette::Text, QColor(100, 150, 100));
        greenPalette.setColor(QPalette::Active, QPalette::Text, QColor(180, 255, 180));
        greenPalette.setColor(QPalette::Button, QColor(40, 100, 40)); // botones
        greenPalette.setColor(QPalette::ButtonText, QColor(180, 255, 180));
        greenPalette.setColor(QPalette::BrightText, Qt::red);
        greenPalette.setColor(QPalette::Link, QColor(80, 220, 80));
        greenPalette.setColor(QPalette::Highlight, QColor(80, 220, 80));
        greenPalette.setColor(QPalette::HighlightedText, Qt::black);

        // Toolbar color y iconos
        themes["Tema Pantano"] = {greenPalette, QColor(0, 180, 0), "#264d26", ""};
    }

    QString m_theme = "Tema Oscuro";
    QMap<QString, Theme> themes;
};
