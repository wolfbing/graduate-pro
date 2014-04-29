#include "graphicsbusedgeitem.h"
#include "Edge.h"

GraphicsBusEdgeItem::GraphicsBusEdgeItem(QGraphicsItem *parent)
	: GraphicsEdgeItem(parent)
{

}

GraphicsBusEdgeItem::~GraphicsBusEdgeItem()
{

}

void GraphicsBusEdgeItem::hoverEnterEvent( QGraphicsSceneHoverEvent *event )
{
	QString msg = QStringLiteral("路段编号: ") + QString::number(mEdgeData->sourceNode()->no())
		+ "-" + QString::number(mEdgeData->destNode()->no()) + ";  "
		+ QStringLiteral("公交线数目: ") + QString::number(mEdgeData->busNum());
	emit sendTmpInfoToStatus(msg);
}
