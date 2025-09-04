#include "DonutWidget.h"

DonutWidget::DonutWidget(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(100, 100);
}

void DonutWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Fondo del widget
    painter.fillRect(rect(), QColor(QColorConstants::Transparent)); // color de fondo

    // Parámetros del donut
    int size = qMin(width(), height()) * 0.4;
    QPoint center(width() / 2.5, height() / 2); // centro a la izquierda
    int outerRadius = size;
    int innerRadius = size / 2;

    // Dibujar círculo exterior
    painter.setBrush(Qt::white);
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(center, outerRadius, outerRadius);

    // Dibujar círculo interior para formar el "donut"
    painter.setBrush(QColor("#333333"));
    painter.drawEllipse(center, innerRadius, innerRadius);

    // Texto al lado
    painter.setPen(Qt::white);
    QFont font = painter.font();
    font.setPointSize(12);
    painter.setFont(font);
    painter.drawText(width() * 0.5, height() / 2 + 6, "Sin Estadísticas");
}
