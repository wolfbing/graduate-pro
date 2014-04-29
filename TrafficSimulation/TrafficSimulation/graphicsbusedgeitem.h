#ifndef GRAPHICSBUSEDGEITEM_H
#define GRAPHICSBUSEDGEITEM_H

#include "graphicsedgeitem.h"

class QGraphicsItem;

class GraphicsBusEdgeItem : public GraphicsEdgeItem
{
	Q_OBJECT

public:
	GraphicsBusEdgeItem(QGraphicsItem *parent=0);
	~GraphicsBusEdgeItem();

protected:
	void hoverEnterEvent(QGraphicsSceneHoverEvent *event);

private:
	
};

#endif // GRAPHICSBUSEDGEITEM_H
