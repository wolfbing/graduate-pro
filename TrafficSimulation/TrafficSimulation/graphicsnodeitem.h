#ifndef GRAPHICSNODEITEM_H
#define GRAPHICSNODEITEM_H

#include <QGraphicsItem>
#include "Communicate.h"
#include "node.h"

class GraphicsNodeItem :public Communicate, public QGraphicsItem
{
	Q_OBJECT
	Q_INTERFACES(QGraphicsItem)

public:
	GraphicsNodeItem(QGraphicsItem *parent = 0);
	~GraphicsNodeItem();

	// 节点类型
	enum NodeItemType {
		No,Junction,Restriction,
		MotorVolumeGraph, NonMotorVolumeGraph, CarVolumeGraph, BusVolumeGraph,  // 车载量图
		MotorbikeVolumeGraph, TaxiVolumeGraph, TruckVolumeGraph,     // 车载量图
		MotorCapabilityGraph, NonMotorCapabilityGraph,  // 承载量
	};

	// 重载
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */);
	QRectF boundingRect() const;
	QPainterPath shape() const;
	QVariant itemChange(GraphicsItemChange change, const QVariant &value);
	//set 
	GraphicsNodeItem & setNodeData(Node *);
	GraphicsNodeItem & setGraphType(NodeItemType);
	// 设置绘制属性
	GraphicsNodeItem & setRadius(qreal radius);
	GraphicsNodeItem & setHaveBorder(bool haveBorder);
	GraphicsNodeItem & setBorderColor(QColor borderColor);
	GraphicsNodeItem & setInnerColor(QColor innerColor);
	GraphicsNodeItem & setNodeItemType(NodeItemType);
	// 检查最近节点, 并设为邻居
	void checkNeighbour(GraphicsNodeItem*);
	// get
	qreal radius() const;
	QColor borderColor() const;
	QColor innerColor() const;
	Node * nodeData() const;

signals:


protected:
	void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
	void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
	

private:
	void init();
	

private:
	Node * mNodeData;
	// 绘制属性
	qreal mRadius; // 外围半径, 边框定死为1
	QColor mBorderColor;
	QColor mInnerColor;
	bool mHaveBorder;
	// 最邻近的节点
	GraphicsNodeItem* mNeignbour;
	qreal mNearestDistance;
	// 节点类型
	NodeItemType mType;

};

#endif // GRAPHICSNODEITEM_H
