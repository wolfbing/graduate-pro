#include "rect.h"
#include <QPointF>


Rect::Rect( qreal left, qreal top, qreal width, qreal height )
{
	mLeft = left;
	mTop = top;
	mWidth = width;
	mHeight = height;
}

Rect::Rect( const Rect & rect )
{
	mLeft = rect.mLeft;
	mTop = rect.mTop;
	mWidth = rect.mWidth;
	mHeight = rect.mHeight;
}

Rect::~Rect()
{

}

Rect & Rect::operator=( const Rect & rect )
{
	mLeft = rect.mLeft;
	mTop = rect.mTop;
	mWidth = rect.mWidth;
	mHeight = rect.mHeight;
	return *this;
}

bool Rect::operator==( const Rect & rect ) const
{
	return (mLeft==rect.mLeft)&&(mTop==rect.mTop)
		&&(mWidth==rect.mWidth)&&(mHeight==rect.mHeight);
}

QPointF Rect::center() const
{
	return QPointF(mLeft+mWidth/2, mTop-mHeight/2);
}

 qreal Rect::width() const
{
	return mWidth;
}

qreal Rect::height() const
 {
	 return mHeight;
 }

qreal Rect::left() const
{
	return mLeft;
}

qreal Rect::top() const
{
	return mTop;
}

qreal Rect::right() const
{
	return mLeft+mWidth;
}

qreal Rect::bottom() const
{
	return mTop-mHeight;
}
