#ifndef TRAFFICROADCAPABILITYGRAPHICSSCENE_H
#define TRAFFICROADCAPABILITYGRAPHICSSCENE_H

#include "roadgraphicsscene.h"

class GraphicsSideLineItem;


class TrafficRoadCapabilityGraphicsScene : public RoadGraphicsScene
{
	Q_OBJECT

public:
	TrafficRoadCapabilityGraphicsScene(QObject *parent=0);
	~TrafficRoadCapabilityGraphicsScene();

	enum CapabilityType
	{
		MotorCapability, NonMotorCapability
	};
	TrafficRoadCapabilityGraphicsScene& setCapabilityType(CapabilityType);
	void addItems();
	void updateItemsAttr();

protected:
	void init();
	void addLegend();

private:
	/// type
	CapabilityType mCapabilityType;

	
};

#endif // TRAFFICROADCAPABILITYGRAPHICSSCENE_H
