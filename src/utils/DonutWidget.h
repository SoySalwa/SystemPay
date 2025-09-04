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
