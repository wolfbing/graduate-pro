#pragma once

#include "node.h"
#include "graphicsnodeitem.h"
#include <QGraphicsItem>
#include <QRect>

class EdgeItem
{
public:
	EdgeItem(){};
	EdgeItem(GraphicsNodeItem* sourceNode, GraphicsNodeItem* destNode);
	EdgeItem(const EdgeItem &);
	EdgeItem & operator=(const EdgeItem &);
	bool operator==(const EdgeItem &) const;
	~EdgeItem(void);

	GraphicsNodeItem* sourceNode() const;
	GraphicsNodeItem* destNode() const;

	QRectF border(const QGraphicsItem*) const;

private:
	GraphicsNodeItem* mSourceNode;
	GraphicsNodeItem* mDestNode;


};

