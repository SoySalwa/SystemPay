#ifndef DONUTWIDGET_H
#define DONUTWIDGET_H

#include <QWidget>
#include <QPainter>

class DonutWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DonutWidget(QWidget *parent = nullptr);
    ~DonutWidget() override = default;

protected:
    void paintEvent(QPaintEvent *) override;
};

#endif // DONUTWIDGET_H
