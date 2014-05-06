#ifndef TRAFFICNODECAPABILITYGRAPHICSSCENE_H
#define TRAFFICNODECAPABILITYGRAPHICSSCENE_H

#include "commonnodegraphicsscene.h"

class GraphicsNodeItem;
class GraphicsEdgeNetItem;
class Legend;

class TrafficNodeCapabilityGraphicsScene : public CommonNodeGraphicsScene
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
	void updateItemsAttr();

private:
	// node type
	CapabilityType mCapabilityType;
	
};

#endif // TRAFFICNODECAPABILITYGRAPHICSSCENE_H
