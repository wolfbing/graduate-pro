#ifndef GRAPHICSSIDELINEITEM_H
#define GRAPHICSSIDELINEITEM_H

#include <QGraphicsItem>
#include <QColor>
#include "Communicate.h"
class Edge;

/*
往一边侧的lineitem, 就像双向的道路每一侧

*/
class GraphicsSideLineItem :public Communicate, public QGraphicsItem
{
	Q_OBJECT
	Q_INTERFACES(QGraphicsItem)

public:
	GraphicsSideLineItem(QGraphicsItem *parent=0);
	~GraphicsSideLineItem();

	// graph type
	enum GraphType
	{
		RoadTypeGraph, TrafficTypeGraph,
		BikeForbidGraph, CarForbidGraph, MotorForbidGraph,  // 禁行类型图
		BusForbidGraph, TaxiForbidGraph, TruckForbidGraph,  // 禁行类型图
		CarLimitGraph, TaxiLimitGraph, TruckLimitGraph, MotorLimitGraph,  // 限号通行类型图
		MotorVolumeGraph, NonMotorVolumeGraph, CarVolumeGraph, BusVolumeGraph,  // 车载量图
		MotorbikeVolumeGraph, TaxiVolumeGraph, TruckVolumeGraph     // 车载量图
	};

	// set
	GraphicsSideLineItem & setEdgeData(Edge*);
	GraphicsSideLineItem & setWidth(qreal);
	GraphicsSideLineItem & setColor(QColor);
	GraphicsSideLineItem & setGraphType(GraphType);

	void advance();
	Edge* edgeData() const;
	void updateAttr(QColor, qreal);

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */);
	QRectF boundingRect() const;
	QPainterPath shape() const;

	void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
	void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

private:
	void init();

private:
	Edge* mEdgeData;
	//  绘制属性
	QColor mColor;
	qreal mWidth;
	// 道路类型
	GraphType mGraphType;
	
};

#endif // GRAPHICSSIDELINEITEM_H
