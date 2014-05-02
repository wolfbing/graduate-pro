#ifndef QGRAPHICSEDGETNETITEM_H
#define QGRAPHICSEDGETNETITEM_H

#include <QGraphicsItem>
#include "Edge.h"

class GraphicsEdgeNetItem : public QGraphicsItem
{

public:
	GraphicsEdgeNetItem(QGraphicsItem *parent = 0);
	~GraphicsEdgeNetItem();

	void addEdgeData(Edge*);

	void advance();

	// ÷ÿ‘ÿ–È∫Ø ˝
	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */);
	QPainterPath shape() const;
	 
	// …Ë÷√ªÊÕº Ù–‘
	GraphicsEdgeNetItem & setWidth(qreal width);
	GraphicsEdgeNetItem & setBorderColor(QColor borderColor);
	GraphicsEdgeNetItem & setInnerColor(QColor innerColor);
	GraphicsEdgeNetItem & setHaveBorder(bool haveBorder);

	qreal edgeWidth() const ;
	QColor innerColor() const;
	QColor borderColor() const;

	void updateAttr(QColor innerColor, QColor borderColor, qreal width, bool haveBorder);

private:
	void init();

private:
	QList<Edge*> mEdgeDataList;
	// ªÊÕº Ù–‘
	qreal mEdgeWidth;
	QColor mBorderColor;
	QColor mInnerColor;
	bool mHaveBorder;
	
};

#endif // QGRAPHICSEDGETNETITEM_H
