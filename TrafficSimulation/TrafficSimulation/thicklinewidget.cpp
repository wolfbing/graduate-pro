#include "thicklinewidget.h"
#include <QPainter>
#include <QPaintEvent>

ThickLineWidget::ThickLineWidget(QWidget *parent)
	: QWidget(parent)
{
	setMinimumWidth(100);
}

ThickLineWidget::ThickLineWidget( 
	double width, QColor color, QColor outColor, bool have, QWidget* parent/*=0*/ )
	: QWidget(parent)
	, mWidth(width)
	, mColor(color)
	, mOutColor(outColor)
	, mHaveBorder(have)
{
	setMinimumWidth(100);
}

ThickLineWidget::~ThickLineWidget()
{

}

void ThickLineWidget::paintEvent( QPaintEvent * event )
{
	QPainter p(this);
	p.setRenderHint(QPainter::Antialiasing);
	int w = event->rect().width();
	int h = event->rect().height();
	
	QLine line(0,h/2,w,h/2);
	if(mHaveBorder){
		QPen outPen(mOutColor); outPen.setWidthF(mWidth);
		p.setPen(outPen);
		p.drawLine(line);
	}
	QPen pen(mColor); pen.setWidthF(mWidth - (mHaveBorder? 2:0));
	p.setPen(pen);
	p.drawLine(line);
}

void ThickLineWidget::changeInnerColor(QColor color)
{
	mColor = color;
	update();
}

void ThickLineWidget::changeBorderColor(QColor color)
{
	mOutColor = color;
	update();
}

void ThickLineWidget::changeSize(qreal s)
{
	mWidth = s;
	update();
}

void ThickLineWidget::changeHaveBorder(int have)
{
	if(have)
		mHaveBorder = true;
	else
		mHaveBorder = false;
	update();
}

