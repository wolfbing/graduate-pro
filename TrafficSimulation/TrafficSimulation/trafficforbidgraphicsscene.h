#ifndef TRAFFICFORBIDGRAPHICSSCENE_H
#define TRAFFICFORBIDGRAPHICSSCENE_H

#include "roadgraphicsscene.h"

class GraphicsSideLineItem;


class TrafficForbidGraphicsScene : public RoadGraphicsScene
{
	Q_OBJECT

public:
	TrafficForbidGraphicsScene(QObject *parent=0);
	~TrafficForbidGraphicsScene();

	enum ForbidType
	{
		BikeForbid, CarForbid, MotorForbid, TaxiForbid, TruckForbid, BusForbid
	};

	TrafficForbidGraphicsScene& setForbidType(ForbidType);

	void addItems();

protected:
	void init();
	void addLegend();
	void updateItemsAttr();

private:
	// sceneµƒ¿‡–Õ£¨bike°¢car......
	ForbidType mForbidType;
	
};

#endif // TRAFFICFORBIDGRAPHICSSCENE_H
