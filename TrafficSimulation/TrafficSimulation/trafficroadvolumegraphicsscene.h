#ifndef TRAFFICVOLUMEGRAPHICSSCENE_H
#define TRAFFICVOLUMEGRAPHICSSCENE_H

#include "roadgraphicsscene.h"

class GraphicsSideLineItem;

class TrafficRoadVolumeGraphicsScene : public RoadGraphicsScene
{
	Q_OBJECT

public:
	TrafficRoadVolumeGraphicsScene(QObject *parent=0);
	~TrafficRoadVolumeGraphicsScene();

	enum VolumeType
	{
		MotorVolume, NonMotorVolume, CarVolume, BusVolume, MotorbikeVolume,
		TaxiVolume, TruckVolume
	};
	TrafficRoadVolumeGraphicsScene& setVolumeType(VolumeType);
	void addItems();

protected:
	void init();
	void addLegend();
	void updateItemsAttr();

private:
	/// type
	VolumeType mVolumeType;
};

#endif // TRAFFICVOLUMEGRAPHICSSCENE_H
