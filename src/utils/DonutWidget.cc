#include "DonutWidget.h"
#include "ThemeManager.h"
#include <QPainter>

DonutWidget::DonutWidget(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(250, 250);

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

    painter.fillRect(rect(), QColor(QColorConstants::Transparent));

    // Tamaño del donut
    int donutSize = qMin(width(), height()) * 0.4;
    int outerRadius = donutSize;
    int innerRadius = donutSize / 2;

    // Calcular el ancho total del gráfico (dona + espacio + texto)
    const Theme &t = ThemeManager::instance()->allThemes()[ThemeManager::instance()->currentTheme()];
    QFont font = painter.font();
    font.setPointSize(12);
    painter.setFont(font);

    QString text = "Sin Estadísticas";
    QFontMetrics fm(font);
    int textWidth = fm.horizontalAdvance(text);

    int totalWidth = (outerRadius * 2) + 15 + textWidth; // Ancho total de la dona, el espacio y el texto

    // Calcular la posición central para centrar el conjunto completo
    QPoint overallCenter(width() / 2, height() / 2);

    // Calcular la posición del centro de la dona
    int donutX = overallCenter.x() - (totalWidth / 2) + outerRadius;
    QPoint donutCenter(donutX, overallCenter.y());

    // Donut
    painter.setBrush(Qt::white);
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(donutCenter, outerRadius, outerRadius);

    painter.setBrush(t.palette.color(QPalette::Window));
    painter.drawEllipse(donutCenter, innerRadius, innerRadius);

    // Texto al lado derecho del donut
    painter.setPen(t.palette.color(QPalette::Text));
    painter.setFont(font);

    int textX = donutCenter.x() + outerRadius + 15;
    int textY = donutCenter.y() + fm.ascent() / 2 - fm.descent() / 2;
    painter.drawText(textX, textY, text);
}