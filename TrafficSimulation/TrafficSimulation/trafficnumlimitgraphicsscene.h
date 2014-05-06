#ifndef TRAFFICNUMLIMITGRAPHICSSCENE_H
#define TRAFFICNUMLIMITGRAPHICSSCENE_H

#include "roadgraphicsscene.h"


class GraphicsSideLineItem;

class TrafficNumLimitGraphicsScene : public RoadGraphicsScene
{
	Q_OBJECT

public:
	TrafficNumLimitGraphicsScene(QObject *parent=0);
	~TrafficNumLimitGraphicsScene();

	enum LimitType
	{
		CarLimit, MotorLimit, TruckLimit, TaxiLimit
	};

	TrafficNumLimitGraphicsScene& setLimitType(LimitType);

	void addItems();

protected:
	void init();
	void addLegend();
	void updateItemsAttr();

private:
	// 现行车种
	LimitType mLimitType;
	
};

#endif // TRAFFICNUMLIMITGRAPHICSSCENE_H
