#ifndef WIDGETSTYLE_H
#define WIDGETSTYLE_H

#include <QString>
#include <QColor>

namespace WidgetStyle
{
    inline QString widgetNavBarColor(const QColor &bgColor)
    {
        return QString(R"(
            QWidget {
                background-color: %1;
                border-radius: 6px;
            }
        )")
            .arg(bgColor.name());
    }
}

#endif // WIDGETSTYLE_H