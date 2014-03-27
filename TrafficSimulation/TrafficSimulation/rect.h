#ifndef RECT_H
#define RECT_H

#include <QObject>

// 这个rect是正常坐标系下的, QRectF是屏幕坐标系下的, 有些地方不适合用
class Rect
{

public:
	Rect(){};
	Rect(qreal left, qreal top, qreal width, qreal height);
	Rect(const Rect & );
	Rect & operator=(const Rect &);
	bool operator==(const Rect &) const;
	~Rect();

	QPointF center() const;
	qreal width() const;
	qreal height() const;
	qreal left() const;
	qreal top() const;
	qreal right() const;
	qreal bottom() const;

private:
	qreal mLeft;
	qreal mTop;
	qreal mWidth;
	qreal mHeight;
	
};

#endif // RECT_H
