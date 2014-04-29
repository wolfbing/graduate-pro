#ifndef TRAFFICNUMLIMITGRAPHICSSCENE_H
#define TRAFFICNUMLIMITGRAPHICSSCENE_H

#include "graphicsscene.h"


class GraphicsSideLineItem;

class TrafficNumLimitGraphicsScene : public GraphicsScene
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
	void updateItems();

private:
	QList<GraphicsSideLineItem*> mSideLineItemList;
	// 绘制属性
	QList<QColor> mColorList;
	QList<qreal> mWidthList;
	QList<qreal> mZValueList;
	// 现行车种
	LimitType mLimitType;
	
};

#endif // TRAFFICNUMLIMITGRAPHICSSCENE_H
