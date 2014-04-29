#ifndef TRAFFICROADCAPABILITYGRAPHICSSCENE_H
#define TRAFFICROADCAPABILITYGRAPHICSSCENE_H

#include "graphicsscene.h"

class GraphicsSideLineItem;


class TrafficRoadCapabilityGraphicsScene : public GraphicsScene
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
	CapabilityType mCapabilityType;

	
};

#endif // TRAFFICROADCAPABILITYGRAPHICSSCENE_H
