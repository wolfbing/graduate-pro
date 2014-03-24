#ifndef ROADLEVELGRAPHICSWIDGET_H
#define ROADLEVELGRAPHICSWIDGET_H

#include <QWidget>
#include "conn.h"
#include "DbAdapter.h"
#include "graphicswidget.h"
#include "legend.h"

/*
- 工作流水：
  载入数据——绘制——创建图例
*/
class RoadLevelGraphicsWidget : public GraphicsWidget
{
	Q_OBJECT

public:
	RoadLevelGraphicsWidget(QWidget *parent = 0);
	~RoadLevelGraphicsWidget();

protected:
	void paintGraphics(QPainter&, QPaintEvent *);

private:
	void createLegend();
	void init();


private:
	DbAdapter mDbAdapter;
	QList<ConnWithCoorLevel>* mConnList;
	
	// 各种路的颜色和宽度
	QColor mColor0, mColor1, mColor2, mColor3, mColor4, mColor5, mColor6,
		mOutColor0, mOutColor1, mOutColor2, mOutColor3, mOutColor6;
	int mWidth0, mWidth1, mWidth2, mWidth3, mWidth4, mWidth5, mWidth6;

};

#endif // ROADLEVELGRAPHICSWIDGET_H
