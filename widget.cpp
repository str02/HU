#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
   // connect(&rtTimer,SIGNAL(timeout()),this,SLOT(rtTimerOutSlot));
   // connect(this, SIGNAL(luckStartSignal()), this, SLOT(luckStartSlot()));
    //rtTimer.start(1000);

  connect(&rtTimer, SIGNAL(timeout()), this, SLOT(rtTimerOutSlot()));
  connect(this, SIGNAL(luckStartSignal()), this, SLOT(luckStartSlot()));
    //rtTimer.start(1000);
}

Widget::~Widget()
{
    delete ui;
}
//绘制事件函数
void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    int side=qMin(width(),height());

    rotationpainter.begin(this);
    rotationpainter.scale(side/450,side/450);
    rotationpainter.translate(225,225);
    rotationpainter.rotate(number);
    rotationpainter.drawPixmap(-225,-225,450,450,QPixmap(":/dial_ima/image/转盘.png"));
    rotationpainter.end();

    pointPainter.begin(this);
    pointPainter.translate(225,225);//将X，Y起点移动到这个位置
    static const QPoint point[4]={QPoint(0,18),QPoint(20,0),QPoint(0,-130),QPoint(-20,0)};//顺序是（下，右，上，左）
    pointPainter.setBrush(QColor(Qt::darkBlue));//设置笔刷
    pointPainter.drawPolygon(point,4);//画一个矩形

    static const QRect retanle(-7,-7,14,18);//设置两个点 一个中心点 一个半径
    pointPainter.setBrush(Qt::darkYellow);//设置笔刷
    pointPainter.drawEllipse(retanle);//画椭圆
    pointPainter.end();
}
//鼠标按压事件函数
void Widget::mousePressEvent(QMouseEvent *event)
{
        if(event->button()==Qt::LeftButton)
        {
            if(event->pos().x()>187&&event->pos().x()<261&&event->pos().y()>165&&event->pos().y()<275)
            {
                qDebug() << "point event";
                emit luckStartSignal();
            }
        }


}
//获取随机数函数
void Widget::luckStartSlot()
{
number=1;
qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
value=qrand()%360+180;
rtTimer.start(5);

}
//减速计算函数
void Widget::rtTimerOutSlot()
{
    number++;
    if((number-value)==90)
    {
        rtTimer.setInterval(10);
    }
    else if((number-value)==180)
    {
        rtTimer.setInterval(15);
    }
    else if((number-value)==270)
    {
        rtTimer.setInterval(20);
    }
    else if((number-value)==360)
    {
        number--;
    }
    update();

}
