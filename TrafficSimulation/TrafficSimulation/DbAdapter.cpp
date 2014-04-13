#include "DbAdapter.h"
#include <QtMath>
#include "Edge.h"

DbAdapter::DbAdapter(void)
	: mDb(0)
{
	mDb = new DB;
}


DbAdapter::~DbAdapter(void)
{
	if(mDb)
		delete mDb;

}


QList<Node*> DbAdapter::loadNormNodes()
{
	QList<Node*> pointList = mDb->loadNodes();
	norm(&pointList);
	return pointList;
}



template <class T>
void DbAdapter::norm( QList<T*>* tList ) const
{
	Rect rect = boundingRect(tList);
	QPointF center = rect.center();
	qreal width = rect.width();
	qreal height = rect.height();
	qreal maxLen = width>height ? width : height;
	QMutableListIterator<T*> mIte(*tList);
	while (mIte.hasNext())
	{
		T* tmpT = mIte.next();
		tmpT->norm(maxLen, center);
		//mIte.setValue(tmpT);
	}
}


template <class T>
Rect DbAdapter::boundingRect( const QList<T*> * tList) const
{
	QListIterator<T*> ite(*tList);
	if(!ite.hasNext())
		return Rect(0,0,0,0);
	T* tmpT;
	Rect rect;
	tmpT = ite.next();
	rect = tmpT->border();
	qreal left=rect.left(), right = rect.right(),
		top = rect.top(), bottom = rect.bottom();
	while (ite.hasNext())
	{
		tmpT = ite.next();
		rect = tmpT->border();
		if(rect.left()<left)
			left = rect.left();
		if(rect.right()>right)
			right = rect.right();
		if(rect.bottom()<bottom)
			bottom = rect.bottom();
		if(rect.top()>top)
			top = rect.top();
	}
	// 这里又要进行坐标系的转换
	return Rect(left,top, qAbs(right-left), qAbs(top-bottom));
}


QList<Edge*> DbAdapter::loadEdges()
{
	QList<Edge*> edgeList = mDb->loadEdges();
	return edgeList;
}

QList<BusRoute*> DbAdapter::loadBusRoutes()
{
	return mDb->loadBusRoutes();
}

QList<TurnRestrict*> DbAdapter::loadTurnRestrictions()
{
	return mDb->loadTurnRestrictions();
}
