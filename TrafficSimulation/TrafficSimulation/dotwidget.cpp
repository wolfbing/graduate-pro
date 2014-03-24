#include "dotwidget.h"
#include <QPainter>
#include <QBrush>
#include <QPen>

DotWidget::DotWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    mColor =QColor(255,0,0);
    mRadius = 2.0;
}

DotWidget *DotWidget::setRadius(float radius)
{
    mRadius = radius;
    return this;
}

DotWidget *DotWidget::setColor(QColor color)
{
    mColor = color;
    return this;
}

QSize DotWidget::sizeHint() const
{
    return QSize(100, 20);
}

void DotWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen(mColor);
    QBrush brush(mColor);
    painter.setPen(pen);
    painter.setBrush(brush);
    float cx = width()/2.0;
    float cy = height()/2.0;
    painter.drawEllipse(cx-mRadius, cy-mRadius, 2*mRadius, 2*mRadius);
}
