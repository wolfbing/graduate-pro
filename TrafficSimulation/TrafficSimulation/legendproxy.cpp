#include "legendproxy.h"
#include <QGraphicsScene>
#include <QPainter>

LegendProxy::LegendProxy(QWidget *widget)
	: QGraphicsProxyWidget(0, Qt::Window)
	, mPosInitialized(false)
{
	setWidget(widget);
	setZValue(1E10);
	//setCacheMode(QGraphicsItem::ItemCoordinateCache);
}

LegendProxy::~LegendProxy()
{

}

QVariant LegendProxy::itemChange( GraphicsItemChange change, const QVariant &value )
{
	//if(!mPosInitialized)
	//	return QGraphicsProxyWidget::itemChange(change, value);
	//if (change == ItemPositionChange && scene()) {
	//	QRectF rect = boundingRect();
	//	QPointF pos = value.toPointF();
	//	QRectF sceneRect = scene()->sceneRect();
	//	if (pos.x() + rect.left() < sceneRect.left())
	//		pos.setX(sceneRect.left() - rect.left());
	//	else if (pos.x() + rect.right() >= sceneRect.right())
	//		pos.setX(sceneRect.right() - rect.right());
	//	if (pos.y() + rect.top() < sceneRect.top())
	//		pos.setY(sceneRect.top() - rect.top());
	//	else if (pos.y() + rect.bottom() >= sceneRect.bottom())
	//		pos.setY(sceneRect.bottom() - rect.bottom());
	//	return pos;
	//}
	return QGraphicsProxyWidget::itemChange(change, value);
}

void LegendProxy::showEvent( QShowEvent *event )
{
	if (scene())
	{
		mPosInitialized = true;
		QRectF srect = scene()->sceneRect();
		QRectF rect = boundingRect();
		setPos(srect.right()-rect.width()-100, srect.bottom()-rect.height()-100 );
	}
	QGraphicsProxyWidget::showEvent(event);
	
}


