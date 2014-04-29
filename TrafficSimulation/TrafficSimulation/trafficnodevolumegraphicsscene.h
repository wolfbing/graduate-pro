#ifndef TRAFFICNODEVOLUMEGRAPHICSSCENE_H
#define TRAFFICNODEVOLUMEGRAPHICSSCENE_H

#include "graphicsscene.h"


class GraphicsEdgeNetItem;
class GraphicsNodeItem;


class TrafficNodeVolumeGraphicsScene : public GraphicsScene
{
	Q_OBJECT

public:
	TrafficNodeVolumeGraphicsScene(QObject *parent=0);
	~TrafficNodeVolumeGraphicsScene();

	enum VolumeType
	{
		MotorVolume, NonMotorVolume, CarVolume, BusVolume, MotorbikeVolume,
		TaxiVolume, TruckVolume
	};

	TrafficNodeVolumeGraphicsScene& setVolumeType(VolumeType);
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
	VolumeType mVolumeType;
	
};

#endif // TRAFFICNODEVOLUMEGRAPHICSSCENE_H
