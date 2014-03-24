#include "thicklinewidget.h"
#include <QPainter>
#include <QPaintEvent>

ThickLineWidget::ThickLineWidget(QWidget *parent)
	: QWidget(parent)
{
	
}

ThickLineWidget::ThickLineWidget( 
	double width, QColor color, QColor outColor, QWidget* parent/*=0*/ )
	: QWidget(parent)
	, mWidth(width)
	, mColor(color)
	, mOutColor(outColor)
{

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
	QPen pen(mColor); pen.setWidthF(mWidth-2); 
	QPen outPen(mOutColor); outPen.setWidthF(mWidth);
	QLine line(0,h/2,w,h/2);
	p.setPen(outPen);
	p.drawLine(line);
	p.setPen(pen);
	p.drawLine(line);
}

