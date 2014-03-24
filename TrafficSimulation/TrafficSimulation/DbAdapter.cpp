#include "DbAdapter.h"
#include <QtMath>

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

// 载入归一化的连接
QList<QPair<Node,Node> >* DbAdapter::loadNormConns()
{
	QList<QPair<Node,Node> >* connList = mDb->loadConn();
	normConns(connList);
	return connList;
}

void DbAdapter::normConns( QList<QPair<Node,Node> > *connList )
{
	if (connList->size() > 0)
	{
		QPointF tmpPoint = connList->at(0).first.mCoor;
		qreal left = tmpPoint.rx();
		qreal right = tmpPoint.rx();
		qreal top = tmpPoint.ry();
		qreal bottom = tmpPoint.ry();
		QMutableListIterator<QPair<Node,Node> > ite(*connList);
		while (ite.hasNext())
		{
			QPair<Node,Node> conn = ite.next();
			QPointF firstPoint = conn.first.mCoor;
			QPointF secondPoint = conn.second.mCoor;
			if (firstPoint.rx() < left)
				left = firstPoint.rx();
			if(firstPoint.rx() > right)
				right = firstPoint.rx();
			if(firstPoint.ry() > top )
				top = firstPoint.ry();
			if(firstPoint.ry() < bottom)
				bottom = firstPoint.ry();
			if(secondPoint.rx() < left)
				left = secondPoint.rx();
			if(secondPoint.rx() > right)
				right = secondPoint.rx();
			if(secondPoint.ry() < bottom)
				bottom =secondPoint.ry();
			if(secondPoint.ry() > top)
				top = secondPoint.ry();
		}
		QPointF center = QPointF( (left+right)/2, (top+bottom)/2);
		qreal width = qAbs(right - left);
		qreal height = qAbs(top - bottom);
		qreal maxL = (width > height ? width : height)*1.1;
		ite.toFront();
		while (ite.hasNext())
		{
			QPair<Node,Node>& conn = ite.next(); // conn是引用类型的
			QPointF firstPoint = conn.first.mCoor;
			QPointF secondPoint = conn.second.mCoor;
			conn.first.mCoor = (firstPoint-center)/maxL;
			conn.second.mCoor = (secondPoint-center)/maxL;
		}
	}
}

void DbAdapter::normConns( QList<ConnWithCoorLevel>* connList )
{
	if (connList->size() > 0)
	{
		QPointF tmpPoint = connList->at(0).mCoorPair.first;
		qreal left = tmpPoint.rx();
		qreal right = tmpPoint.rx();
		qreal top = tmpPoint.ry();
		qreal bottom = tmpPoint.ry();
		QMutableListIterator<ConnWithCoorLevel> ite(*connList);
		while (ite.hasNext())
		{
			ConnWithCoorLevel conn = ite.next();
			QPointF firstPoint = conn.mCoorPair.first;
			QPointF secondPoint = conn.mCoorPair.second;
			if (firstPoint.rx() < left)
				left = firstPoint.rx();
			if(firstPoint.rx() > right)
				right = firstPoint.rx();
			if(firstPoint.ry() > top )
				top = firstPoint.ry();
			if(firstPoint.ry() < bottom)
				bottom = firstPoint.ry();
			if(secondPoint.rx() < left)
				left = secondPoint.rx();
			if(secondPoint.rx() > right)
				right = secondPoint.rx();
			if(secondPoint.ry() < bottom)
				bottom =secondPoint.ry();
			if(secondPoint.ry() > top)
				top = secondPoint.ry();
		} // 寻找边界循环结束
		QPointF center = QPointF( (left+right)/2, (top+bottom)/2);
		qreal width = qAbs(right - left);
		qreal height = qAbs(top - bottom);
		qreal maxL = (width > height ? width : height)*1.1;
		ite.toFront();
		while (ite.hasNext())
		{
			ConnWithCoorLevel& conn = ite.next(); // conn是引用类型的
			QPointF firstPoint = conn.mCoorPair.first;
			QPointF secondPoint = conn.mCoorPair.second;
			conn.mCoorPair.first = (firstPoint-center)/maxL;
			conn.mCoorPair.second = (secondPoint-center)/maxL;
		}
	}
}

void DbAdapter::normConns( QHash<ConnWithCoorPair,int>* connHash )
{
	if (connHash->size() > 0)
	{
		QMutableHashIterator<ConnWithCoorPair,int> hashIte(*connHash);
		hashIte.next();
		QPointF tmpPoint = hashIte.key().mCoorPair.first;
		qreal left = tmpPoint.rx();
		qreal right = tmpPoint.rx();
		qreal top = tmpPoint.ry();
		qreal bottom = tmpPoint.ry();
		hashIte.toFront();
		while (hashIte.hasNext())
		{
			ConnWithCoorPair conn = hashIte.next().key();
			QPointF firstPoint = conn.mCoorPair.first;
			QPointF secondPoint = conn.mCoorPair.second;
			if (firstPoint.rx() < left)
				left = firstPoint.rx();
			if(firstPoint.rx() > right)
				right = firstPoint.rx();
			if(firstPoint.ry() > top )
				top = firstPoint.ry();
			if(firstPoint.ry() < bottom)
				bottom = firstPoint.ry();
			if(secondPoint.rx() < left)
				left = secondPoint.rx();
			if(secondPoint.rx() > right)
				right = secondPoint.rx();
			if(secondPoint.ry() < bottom)
				bottom =secondPoint.ry();
			if(secondPoint.ry() > top)
				top = secondPoint.ry();
		}
		QPointF center = QPointF( (left+right)/2, (top+bottom)/2);
		qreal width = qAbs(right - left);
		qreal height = qAbs(top - bottom);
		qreal maxL = (width > height ? width : height)*1.1;
		hashIte.toFront();
		QHash<ConnWithCoorPair,int>* tmpHash = new QHash<ConnWithCoorPair,int>;
		while (hashIte.hasNext())
		{
			hashIte.next(); // conn是引用类型的
			QPointF firstPoint = hashIte.key().mCoorPair.first;
			QPointF secondPoint = hashIte.key().mCoorPair.second;
			QPointF normFirstPoint = (firstPoint-center)/maxL;
			QPointF normSecondPoint = (secondPoint-center)/maxL;
			tmpHash->insert(ConnWithCoorPair(normFirstPoint,normSecondPoint),hashIte.value());
			hashIte.remove();
		}
		QHashIterator<ConnWithCoorPair,int> tmpIte(*tmpHash);
		while (tmpIte.hasNext())
		{
			tmpIte.next();
			connHash->insert(tmpIte.key(),tmpIte.value());
		}

		delete tmpHash;

	}
}

QList<ConnWithCoorLevel>* DbAdapter::loadNormConnWithLevel()
{
	QList<ConnWithCoorLevel>* connList = new QList<ConnWithCoorLevel>;
	connList = mDb->loadConnWithLevel();
	normConns(connList);
	return connList;
}

QHash<ConnWithCoorPair,int>* DbAdapter::loadNormConnWithBusNum()
{
	QHash<ConnWithNoPair,int>* connHash = new QHash<ConnWithNoPair,int>;
	QList<QString>* routes = mDb->loadBusRoute();
	QHash<int,int>* nodeIdToId = mDb->loadNodeIdToId(); // 道路编号和数据库主键的对应
	QListIterator<QString> routeIte(*routes);
	QString route;
	QStringList sNodeList;
	int node1,node2;
	ConnWithNoPair conn;
	while (routeIte.hasNext())
	{
		route = routeIte.next();
		sNodeList = route.split(QString(","));
		if (sNodeList.size()>1)
		{
			node1 = nodeIdToId->value(sNodeList.at(0).toInt());
			for (int i=1;i<sNodeList.size();++i)
			{
				node2 = nodeIdToId->value(sNodeList.at(i).toInt());
				if(node1<node2)
					conn = ConnWithNoPair(node1,node2);
				else
					conn = ConnWithNoPair(node2,node1);

				if(connHash->contains(conn))
					connHash->insert(conn,connHash->value(conn)+1);
				else
					connHash->insert(conn,1);
				
				node1 = node2;
			}// 一条公交线路整理完成
		}
		routeIte.next(); // 跳过同一条公交路线的反向
	}// 所有线路整理完成
	QHash<int,QPointF>* points = mDb->loadNodeById(); // 主键和点坐标的对应
	QVector<ConnWithNoPair>* connList = mDb->loadConnByNo(); // 所有的路段
	QVectorIterator<ConnWithNoPair> connVecIte(*connList);
	QHash<ConnWithCoorPair,int>* result = new QHash<ConnWithCoorPair,int>;
	while (connVecIte.hasNext())
	{
		ConnWithNoPair tmpConn = connVecIte.next();
		int busNum = 0;
		if (connHash->contains(tmpConn))
			busNum = connHash->value(tmpConn);
		result->insert(ConnWithCoorPair(
			points->value(tmpConn.node1),
			points->value(tmpConn.node2) ),
			busNum);

	}
	// 把点坐标归一化
	normConns(result);
	return result;

}
