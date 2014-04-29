#ifndef TRAFFICNODECAPABILITYGRAPHICSSCENE_H
#define TRAFFICNODECAPABILITYGRAPHICSSCENE_H

#include "graphicsscene.h"

class GraphicsNodeItem;
class GraphicsEdgeNetItem;


class TrafficNodeCapabilityGraphicsScene : public GraphicsScene
{
	Q_OBJECT

public:
	TrafficNodeCapabilityGraphicsScene(QObject *parent=0);
	~TrafficNodeCapabilityGraphicsScene();

	enum CapabilityType
	{
		MotorCapability, NonMotorCapability
	};

	TrafficNodeCapabilityGraphicsScene& setCapabilityType(CapabilityType);
	void addItems();

protected:
	void init();
	void addLegend();
	void updateItems();

private:
	QList<GraphicsNodeItem*> mNodeItemList;
	GraphicsEdgeNetItem* mEdgeNetItem;
	// ªÊ÷∆ Ù–‘
	QList<QColor> mNodeInnerColorList;
	QList<QColor> mNodeBorderColorList;
	QList<qreal> mNodeRadiusList;
	QList<bool> mNodeHaveBorderList;
	QColor mEdgeNetInnerColor;
	QColor mEdgeNetBorderColor;
	qreal mEdgeNetWidth;
	bool mEdgeNetHaveBorder;

	// node type
	CapabilityType mCapabilityType;
	
};

#endif // TRAFFICNODECAPABILITYGRAPHICSSCENE_H
