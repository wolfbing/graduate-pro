#ifndef NODEGRAPHICSVIEW_H
#define NODEGRAPHICSVIEW_H

#include <QGraphicsView>
#include "nodegraphicsscene.h"

class GraphicsView : public QGraphicsView
{
	Q_OBJECT

public:
	GraphicsView(GraphicsScene* scene, QWidget* parent=0);
	~GraphicsView();

public slots:
	void print();
		

signals:
	void sizeChange(int w, int h);
	void zoom(int step, QPointF point); // ∑≈Àı
	void move(QPointF offset);

protected:
	void resizeEvent(QResizeEvent *event);
	void wheelEvent(QWheelEvent *event);

private:
	void init(GraphicsScene* scene);

private:
	bool mIsPressed;
	QPoint mPressPos;
	QPointF mPressScenePos;
	
};

#endif // NODEGRAPHICSVIEW_H
