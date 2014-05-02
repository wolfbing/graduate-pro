#include "thickdotwidget.h"
#include <QPaintEvent>
#include <QPainter>
#include <QSize>


ThickDotWidget::ThickDotWidget(QWidget *parent)
	: QWidget(parent)
{
	this->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
}

ThickDotWidget::ThickDotWidget(qreal radius,  QColor inColor, QColor outColor, bool haveBorder, QWidget* parent )
	: QWidget(parent)
{
	this->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
	mInColor = inColor;
	mOutColor = outColor;
	mSize = radius;
	mHaveBorder = haveBorder;
}



ThickDotWidget::~ThickDotWidget()
{

}

void ThickDotWidget::paintEvent( QPaintEvent * event )
{
	QRect rect = event->rect();
	QPainter p(this);
	p.setRenderHint(QPainter::Antialiasing);
	QPoint center = rect.center();
	if(mHaveBorder)
		p.setPen(QPen(mOutColor));
	else
		p.setPen(Qt::NoPen);
	p.setBrush(QBrush(mInColor));
	p.drawEllipse(center.x()-mSize,center.y()-mSize,2*mSize,2*mSize);


}

QSize ThickDotWidget::sizeHint() const
{
	return QSize(2*mSize+4, 2*mSize+4);
}

void ThickDotWidget::changeSize(qreal s)
{
	mSize = s;
	update();
}

void ThickDotWidget::changeInnerColor(QColor color)
{
	mInColor = color;
	update();
}

void ThickDotWidget::changeBorderColor(QColor color)
{
	mOutColor = color;
	update();
}

void ThickDotWidget::changeHaveBorder(int have)
{
	if(have)
		mHaveBorder = true;
	else
		mHaveBorder = false;
	update();
}
