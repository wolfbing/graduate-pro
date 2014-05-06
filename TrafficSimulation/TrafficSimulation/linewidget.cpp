#include "linewidget.h"
#include <QPaintEvent>
#include <QPainter>
#include <QColor>

LineWidget::LineWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    mWidth = 2.0;
    mColor = QColor(255,0,0);
}

LineWidget *LineWidget::setWidth(qreal width)
{
    mWidth = width;
    return this;
}

LineWidget *LineWidget::setColor(QColor color)
{
    mColor = color;
    return this;
}

void LineWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    int width = this->width();
    int height = this->height();
    QPen pen(mColor);
    pen.setWidthF(mWidth);
    painter.setBrush(mColor);
    painter.setPen(pen);
    painter.drawLine(0, height/2.0, width, height/2.0);
}

QSize LineWidget::sizeHint() const
{
    return QSize(100,20);
}

void LineWidget::changeColor(QColor color)
{
	mColor = color;
	update();
}

void LineWidget::changeWidth(qreal width)
{
	mWidth = width;
	update();
}
