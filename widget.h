#ifndef WIDGET_H
#define WIDGET_H
#include <QPainter>
#include <QWidget>
#include <QDebug>
#include<QTimer>
#include<QTime>
#include<QEvent>
#include <QMouseEvent>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

signals:
    void luckStartSignal();
public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
protected :
    virtual void paintEvent(QPaintEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);

public slots:
    void luckStartSlot();
    void rtTimerOutSlot();
private:
    Ui::Widget *ui;
    QPainter rotationpainter;
    QPainter pointPainter;
    int value;
    qreal number;
    QTimer rtTimer;

};

#endif // WIDGET_H
