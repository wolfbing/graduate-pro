#ifndef GRAPHICSNODENOTEXTITEM_H
#define GRAPHICSNODENOTEXTITEM_H

#include <QGraphicsTextItem>
#include "graphicsnodeitem.h"


class GraphicsNodeNoTextItem : public QGraphicsTextItem
{

public:
	GraphicsNodeNoTextItem(GraphicsNodeItem *parent );
	~GraphicsNodeNoTextItem();

	// жиди
	//void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */);
	//void boundingRect();
	//void shape();

private:
	//QGraphicsItem* mParentNodeItem;
};

#endif // GRAPHICSNODENOTEXTITEM_H
