#pragma once

#include "node.h"
#include "graphicsnodeitem.h"
#include <QGraphicsItem>
#include <QRect>

class Edge
{
public:
	Edge(){};
	Edge(GraphicsNodeItem* sourceNode, GraphicsNodeItem* destNode);
	Edge(const Edge &);
	Edge & operator=(const Edge &);
	bool operator==(const Edge &) const;
	~Edge(void);

	GraphicsNodeItem* sourceNode() const;
	GraphicsNodeItem* destNode() const;

	QRectF border(const QGraphicsItem*) const;

private:
	GraphicsNodeItem* mSourceNode;
	GraphicsNodeItem* mDestNode;


};

