#include "legendproxy.h"
#include <QGraphicsScene>
#include <QPainter>
#include "legend.h"
#include "legendelement.h"

LegendProxy::LegendProxy(QWidget *widget)
	: QGraphicsProxyWidget(0, Qt::Window)
	, mPosInitialized(false)
	, mLegendWidget((Legend*)widget)
{
	setWidget(widget);
	setZValue(1E10);
	//setCacheMode(QGraphicsItem::ItemCoordinateCache);
	setCacheMode(QGraphicsItem::NoCache);
	//mElements = mLegendWidget->elements();
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


void LegendProxy::updateAttr(QList<QColor> colorList, QList<qreal> widthList)
{
	mLegendWidget->updateAttr(colorList, widthList);
}

void LegendProxy::updateAttr(QList<QColor> colorList1, QList<QColor> colorList2, QList<qreal> sizeList)
{
	mLegendWidget->updateAttr(colorList1, colorList2, sizeList);
}

void LegendProxy::setElements(QList<LegendElement> li)
{
	mElements = li;
}

void LegendProxy::updateLegend()
{
	//delete mLegendWidget;
	mLegendWidget = new Legend(mElements);
	setWidget(mLegendWidget);
}

void LegendProxy::newUpdateAttr(QList<QColor> colors, QList<qreal> widths)
{
	for (int i=0; i<mElements.size(); ++i)
	{
		mElements[i].setElementColor1(colors[i]);
		mElements[i].setElementSize(widths[i]);
	}
	updateLegend();
}

void LegendProxy::newUpdateAttr(QList<QColor> colorList1, QList<QColor> colorList2, QList<qreal> sizeList)
{
	for (int i=0; i<mElements.size(); ++i)
	{
		mElements[i].setElementColor1(colorList1[i]);
		mElements[i].setElementColor2(colorList2[i]);
		mElements[i].setElementSize(sizeList[i]);
	}
	updateLegend();
}


