#ifndef TRAFFICVOLUMEGRAPHICSSCENE_H
#define TRAFFICVOLUMEGRAPHICSSCENE_H

#include "graphicsscene.h"

class GraphicsSideLineItem;

class TrafficRoadVolumeGraphicsScene : public GraphicsScene
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
	void updateItems();

private:
	QList<GraphicsSideLineItem*> mSideLineItemList;
	// ªÊ÷∆ Ù–‘
	QList<QColor> mColorList;
	QList<qreal> mWidthList;
	QList<qreal> mZValueList;
	/// type
	VolumeType mVolumeType;
};

#endif // TRAFFICVOLUMEGRAPHICSSCENE_H
