#ifndef BUSNUMGRAPHICSWIDGET_H
#define BUSNUMGRAPHICSWIDGET_H

#include <QWidget>
#include "DbAdapter.h"
#include "conn.h"
#include "graphicswidget.h"

class BusNumGraphicsWidget : public GraphicsWidget
{
	Q_OBJECT

public:
	BusNumGraphicsWidget(QWidget *parent = 0);
	~BusNumGraphicsWidget();

protected:
	void paintGraphics(QPainter& p, QPaintEvent * event);

private:
	void createLegend();
	void init();

private:
	DbAdapter mDbAdapter;
	QHash<ConnWithCoorPair,int>* mConn;
	QColor mColor0, mColor1, mColor2, mColor3, mColor4, mColor5, mColor6;
	qreal mWidth0, mWidth1, mWidth2, mWidth3, mWidth4, mWidth5, mWidth6;

};

#endif // BUSNUMGRAPHICSWIDGET_H
