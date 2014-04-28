#ifndef TRAFFICFORBIDGRAPHICSSCENE_H
#define TRAFFICFORBIDGRAPHICSSCENE_H

#include "graphicsscene.h"

class GraphicsSideLineItem;


class TrafficForbidGraphicsScene : public GraphicsScene
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
	void updateItems();
	void doSomething();

private:
	QList<GraphicsSideLineItem*> mSideLineItemList;
	// 绘制属性
	QList<QColor> mColorList;
	QList<qreal> mWidthList;
	QList<qreal> mZValueList;
	// scene的类型，bike、car......
	ForbidType mForbidType;
	
};

#endif // TRAFFICFORBIDGRAPHICSSCENE_H
