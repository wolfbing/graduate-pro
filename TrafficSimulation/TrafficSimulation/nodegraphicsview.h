#ifndef NODEGRAPHICSVIEW_H
#define NODEGRAPHICSVIEW_H

#include <QGraphicsView>
#include "nodegraphicsscene.h"

class NodeGraphicsView : public QGraphicsView
{
	Q_OBJECT

public:
	NodeGraphicsView(NodeGraphicsScene* scene, QWidget* parent=0);
	~NodeGraphicsView();

signals:
	void sizeChange(int w, int h);
	void zoom(int step, QPointF point); // ∑≈Àı
	void move(QPointF offset);

protected:
	void resizeEvent(QResizeEvent *event);
	void wheelEvent(QWheelEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

private:
	void init(NodeGraphicsScene* scene);

private:
	bool mIsPressed;
	QPoint mPressPos;
	QPointF mPressScenePos;
	
};

#endif // NODEGRAPHICSVIEW_H
