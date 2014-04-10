#include "graphicsedgeitem.h"
#include "Edge.h"
#include <QPainter>
#include <QtMath>

GraphicsEdgeItem::GraphicsEdgeItem(QGraphicsItem *parent)
	: QGraphicsItem(parent), Communicate()
	, mHaveBorder(true)
{
	setFlag(ItemSendsGeometryChanges);
	setCacheMode(NoCache);
	setAcceptHoverEvents(true);

}

GraphicsEdgeItem::~GraphicsEdgeItem()
{

}

GraphicsEdgeItem& GraphicsEdgeItem::setWidth( qreal width )
{
	mWidth = width;
	return *this;
}

GraphicsEdgeItem& GraphicsEdgeItem::setBorderColor( QColor color )
{
	mBorderColor = color;
	return *this;
}

GraphicsEdgeItem& GraphicsEdgeItem::setInnerColor( QColor color )
{
	mInnerColor = color;
	return *this;
}

GraphicsEdgeItem& GraphicsEdgeItem::setEdgeData( Edge* edge )
{
	mEdgeData = edge;
	return *this;
}

void GraphicsEdgeItem::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */ )
{
	painter->setRenderHint(QPainter::Antialiasing);
	QPen innerPen, outerPen;	
	if (mHaveBorder)
	{
		outerPen.setColor(mBorderColor);
		outerPen.setWidthF(mWidth);
		painter->setPen(outerPen);
		painter->drawLine(mEdgeData->sourceNode()->sceneCoor(), mEdgeData->destNode()->sceneCoor() );
	}

	innerPen.setColor(mInnerColor);
	innerPen.setWidthF(mWidth-(mHaveBorder ? 2 : 0) );
	painter->setPen(innerPen);
	painter->drawLine(mEdgeData->sourceNode()->sceneCoor(), mEdgeData->destNode()->sceneCoor() );

}

QRectF GraphicsEdgeItem::boundingRect() const
{
	QRectF rect(mEdgeData->sourceNode()->sceneCoor(), mEdgeData->destNode()->sceneCoor() );
	rect = rect.normalized();
	return rect;
}

QPainterPath GraphicsEdgeItem::shape() const
{
	QPainterPath path;
	QPointF source = mEdgeData->sourceNode()->sceneCoor();
	QPointF dest = mEdgeData->destNode()->sceneCoor();
	QLineF line(source, dest);
	qreal angle = line.angle();
	if(angle>=180)
		angle -= 180;
	qreal dx = mWidth/2.0*qSin(angle);
	qreal dy = mWidth/2.0*qCos(angle);
	QPointF p1(source.x()-dx,source.y()+dy);
	QPointF p2(source.x()+dx,source.y()-dy);
	QPointF p3(dest.x()+dx,dest.y()-dy);
	QPointF p4(dest.x()-dx,dest.y()+dy);
	path.moveTo(p1);
	path.lineTo(p2);
	path.lineTo(p3);
	path.lineTo(p4);
	path.lineTo(p1);
	return path;	
	
}

Edge* GraphicsEdgeItem::edgeData() const
{
	return mEdgeData;
}

void GraphicsEdgeItem::advance()
{
	prepareGeometryChange();
}

void GraphicsEdgeItem::hoverEnterEvent( QGraphicsSceneHoverEvent *event )
{
	QString msg = QStringLiteral("路段编号: ") + QString::number(mEdgeData->sourceNode()->no() )+ 
		+ "-" + QString::number(mEdgeData->destNode()->no()) + ";  " +
		QStringLiteral("道路等级: ")+QString::number(mEdgeData->roadLevel());
	emit sendTmpInfoToStatus(msg);
}

void GraphicsEdgeItem::hoverLeaveEvent( QGraphicsSceneHoverEvent *event )
{
	emit clearTmpInfoFromStatus();
}

GraphicsEdgeItem& GraphicsEdgeItem::setHaveBorder( bool haveBorder )
{
	mHaveBorder = haveBorder;
	return *this;
}


