#include "busnumgraphicswidget.h"
#include <QPainter>
#include <QPaintEvent>

BusNumGraphicsWidget::BusNumGraphicsWidget(QWidget *parent)
	: GraphicsWidget(parent)
	, mConn(0)
{
	mConn = mDbAdapter.loadNormConnWithBusNum();
	init();
}

BusNumGraphicsWidget::~BusNumGraphicsWidget()
{
	if(mConn)
		delete mConn;
}

void BusNumGraphicsWidget::paintGraphics(QPainter& p, QPaintEvent * event )
{
	QHashIterator<ConnWithCoorPair,int> ite(*mConn);
	QPainterPath path0, path1, path2, path3, path4, path5, path6;

	QPen pen0(QBrush(mColor0), mWidth0, Qt::SolidLine, Qt::SquareCap, Qt::RoundJoin);
	QPen pen1(QBrush(mColor1), mWidth1, Qt::SolidLine, Qt::SquareCap, Qt::RoundJoin);
	QPen pen2(QBrush(mColor2), mWidth2, Qt::SolidLine, Qt::SquareCap, Qt::RoundJoin);
	QPen pen3(QBrush(mColor3), mWidth3, Qt::SolidLine, Qt::SquareCap, Qt::RoundJoin);
	QPen pen4(QBrush(mColor4), mWidth4, Qt::SolidLine, Qt::SquareCap, Qt::RoundJoin);
	QPen pen5(QBrush(mColor5), mWidth5, Qt::SolidLine, Qt::SquareCap, Qt::RoundJoin);
	QPen pen6(QBrush(mColor6), mWidth6, Qt::SolidLine, Qt::SquareCap, Qt::RoundJoin);

	while (ite.hasNext())
	{
		ite.next();
		QPointF firstPoint = normCoorToScreenCoor(ite.key().mCoorPair.first);
		QPointF secondPoint = normCoorToScreenCoor(ite.key().mCoorPair.second);
		int value = ite.value();
		if(0 == ite.value())
		{path0.moveTo(firstPoint);path0.lineTo(secondPoint);}
		if(1 == ite.value())
		{path1.moveTo(firstPoint);path1.lineTo(secondPoint);}
		if(2 == ite.value())
		{path2.moveTo(firstPoint);path2.lineTo(secondPoint);}
		if(3 == ite.value())
		{path3.moveTo(firstPoint);path3.lineTo(secondPoint);}
		if(4 == ite.value())
		{path4.moveTo(firstPoint);path4.lineTo(secondPoint);}
		if(5 == ite.value())
		{path5.moveTo(firstPoint);path5.lineTo(secondPoint);}
		if(ite.value()>=6)
		{path6.moveTo(firstPoint);path6.lineTo(secondPoint);}
	}
	p.setPen(pen0);p.drawPath(path0);
	p.setPen(pen1);p.drawPath(path1);
	p.setPen(pen2);p.drawPath(path2);
	p.setPen(pen3);p.drawPath(path3);
	p.setPen(pen4);p.drawPath(path4);
	p.setPen(pen5);p.drawPath(path5);
	p.setPen(pen6);p.drawPath(path6);

}

void BusNumGraphicsWidget::createLegend()
{
	if(!mLegend){
		LegendElement line0(QStringLiteral("0条公交线路"),LegendElement::LINE,mWidth0,mColor0);
		LegendElement line1(QStringLiteral("1条公交线路"),LegendElement::LINE,mWidth1,mColor1);
		LegendElement line2(QStringLiteral("2条公交线路"),LegendElement::LINE,mWidth2,mColor2);
		LegendElement line3(QStringLiteral("3条公交线路"),LegendElement::LINE,mWidth3,mColor3);
		LegendElement line4(QStringLiteral("4条公交线路"),LegendElement::LINE,mWidth4,mColor4);
		LegendElement line5(QStringLiteral("5条公交线路"),LegendElement::LINE,mWidth5,mColor5);
		LegendElement line6(QStringLiteral(">=6条公交线路"),LegendElement::LINE,mWidth6,mColor6);
		QList<LegendElement> li;
		li.append(line0);li.append(line1);li.append(line2);li.append(line3);
		li.append(line4);li.append(line5);li.append(line6);
		mLegend = new Legend(li,this);
	}
	mLegend->show();
	

}

void BusNumGraphicsWidget::init()
{
	mColor0 = QColor(54,4,255); mWidth0 = 2;
	mColor1 = QColor(28,255,232); mWidth1 = 2;
	mColor2 = QColor(106,251,0); mWidth2 = 2;
	mColor3 = QColor(225,192,0); mWidth3 = 3;
	mColor4 = QColor(252,153,103); mWidth4 = 3;
	mColor5 = QColor(251,0,1); mWidth5 = 3;
	mColor6 = QColor(128,0,0); mWidth6 = 3;

}
