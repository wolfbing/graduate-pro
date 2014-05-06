#ifndef TRAFFICNODEVOLUMEGRAPHICSSCENE_H
#define TRAFFICNODEVOLUMEGRAPHICSSCENE_H

#include "commonnodegraphicsscene.h"


class GraphicsEdgeNetItem;
class GraphicsNodeItem;


class TrafficNodeVolumeGraphicsScene : public CommonNodeGraphicsScene
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
	void updateItemsAttr();

private:
	// node type
	VolumeType mVolumeType;
	
};

#endif // TRAFFICNODEVOLUMEGRAPHICSSCENE_H
