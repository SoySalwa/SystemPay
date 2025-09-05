#include "DonutWidget.h"
#include "ThemeManager.h"
#include <QApplication>
#include <QPainter>

DonutWidget::DonutWidget(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(100, 100);

    // Conectar al cambio de tema para repintar automáticamente
    connect(ThemeManager::instance(), &ThemeManager::themeChanged, this, [=](const QString &)
            {
                update(); // repinta el widget cuando cambia el tema
            });
}

void DonutWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Fondo del widget
    painter.fillRect(rect(), QColor(QColorConstants::Transparent));

    // Parámetros del donut
    int size = qMin(width(), height()) * 0.4;
    QPoint center(width() / 2.5, height() / 2);
    int outerRadius = size;
    int innerRadius = size / 2;

    // Dibujar círculo exterior (puedes dejar blanco o usar un color de tema)
    painter.setBrush(Qt::white);
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(center, outerRadius, outerRadius);

    // Obtener color del círculo interior según el tema activo
    const Theme &t = ThemeManager::instance()->allThemes()[ThemeManager::instance()->currentTheme()];
    QColor innerColor = t.palette.color(QPalette::Window); // o QPalette::Window según prefieras

    painter.setBrush(innerColor);
    painter.drawEllipse(center, innerRadius, innerRadius);

    // Texto al lado
    painter.setPen(t.palette.color(QPalette::Text)); // texto según tema
    QFont font = painter.font();
    font.setPointSize(12);
    painter.setFont(font);
    painter.drawText(width() * 0.5, height() / 2 + 6, "Sin Estadísticas");
}
