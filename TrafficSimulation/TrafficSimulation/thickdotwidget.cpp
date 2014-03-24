#include "thickdotwidget.h"
#include <QPaintEvent>
#include <QPainter>

ThickDotWidget::ThickDotWidget(QWidget *parent)
	: QWidget(parent)
{
	
}

ThickDotWidget::ThickDotWidget(qreal size,  QColor inColor, QColor outColor, QWidget* parent )
	: QWidget(parent)
{
	mInColor = inColor;
	mOutColor = outColor;
	mSize = size;
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

	p.setPen(QPen(mOutColor));
	p.setBrush(QBrush(mInColor));
	p.drawEllipse(center.x()-mSize,center.y()-mSize,2*mSize,2*mSize);


}
