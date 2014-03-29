#ifndef QGRAPHICSEDGETNETITEM_H
#define QGRAPHICSEDGETNETITEM_H

#include <QGraphicsItem>
#include "Edge.h"

class GraphicsEdgetNetItem : public QGraphicsItem
{

public:
	GraphicsEdgetNetItem(QGraphicsItem *parent = 0);
	~GraphicsEdgetNetItem();

	void addEdge(const Edge &);

	void advance();

	// жидиащКЏЪ§
	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */);
	QPainterPath shape() const;


private:
	QList<Edge> mEdges;
	
};

#endif // QGRAPHICSEDGETNETITEM_H
