#ifndef GRAPHICSWIDGET_H
#define GRAPHICSWIDGET_H

#include <QWidget>
#include "legend.h"
#include <QPainter>

/*
- 地图的移动和放缩
- 光标的形状定义
- 归一化的坐标转换成屏幕坐标（及进行平移、放缩等变换）
- 绘制完成后再显示图例（否则图例的位置控制不了）
*/
class GraphicsWidget : public QWidget
{
	Q_OBJECT

public:
	GraphicsWidget(QWidget *parent = 0);
	~GraphicsWidget();

signals:
	void paintCompleted();

public slots:
	void showLegend();
	void printGraphics();


protected:
	QPointF normCoorToScreenCoor( QPointF coor );
	virtual void createLegend() = 0; //包括了创建和show
	virtual void paintGraphics(QPainter& p, QPaintEvent* event) = 0;
	// 事件
	void mousePressEvent(QMouseEvent *);
	void mouseReleaseEvent(QMouseEvent *);
	void mouseMoveEvent(QMouseEvent *);
	void wheelEvent(QWheelEvent *);
	// 子类重载paintEvent时仍然需要调用此函数
	// 这里实现共有的功能: - 背景色填充  - 版权声明  - 发射绘制完成信号
	void paintEvent(QPaintEvent *);
	// 获取缩放比例
	qreal getRatio();


protected:
	Legend* mLegend;
	QColor mBackColor;

private:
	// 负责拖动的变量
	bool mPressed; // 是否是鼠标左键按下状态
	QPointF mOffset; // 图的位移
	QPoint mPressCoor; // 鼠标点击的位置
	// 负责放缩的变量
	qreal mRatio;
	// 图例对话框
	bool mLegendShown;

	

};

#endif // GRAPHICSWIDGET_H
