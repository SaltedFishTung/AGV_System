#include "mypainterwidget.h"
#include <QPainter>

MyPainterWidget::MyPainterWidget(QWidget* parent) : QWidget(parent)
{
    setMinimumSize(1600,900);
    setMaximumSize(1600,900);
}

MyPainterWidget::~MyPainterWidget(){}

void MyPainterWidget::paintEvent(QPaintEvent* p) {
    QPainter painter(this);
    painter.setPen(QPen(Qt::blue,4));//设置画笔形式
    painter.drawLine(20,20,220,220);//画直线
    painter.drawLine(20,220,220,20);
    painter.drawEllipse(20,20,200,200);//画圆
    painter.drawRect(20,20,200,200);//画矩形
}
