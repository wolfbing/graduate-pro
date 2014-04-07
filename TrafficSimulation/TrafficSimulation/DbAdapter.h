#pragma once

#include "db.h"
#include "node.h"
#include "conn.h"
#include "rect.h"

class Edge;

class DbAdapter
{
public:
	DbAdapter(void);
	~DbAdapter(void);

	//QList<QPair<Node,Node> >* loadNormConns();
	QList<ConnWithCoorLevel>* loadNormConnWithLevel();
	QHash<ConnWithCoorPair,int>* loadNormConnWithBusNum();
	QList<Node*> loadNormNodesWithNo();
	QList<ConnWithCoorPair>* loadNormConns();
	QList<ConnWithNoPair>* loadConnsWithNoPair();
	QList<Edge>* loadEdgeWithCoorLevel();

private:
	template <class T>
	Rect boundingRect(const QList<T> *) const;
	template <class T>
	Rect boundingRect(const QList<T*> *) const;

	void normConns(QList<QPair<Node,Node> > *);
	void normConns(QList<ConnWithCoorLevel>* );
	void normConns(QHash<ConnWithCoorPair,int>*);

	template <class T>
	void norm(QList<T>*) const;
	template <class T>
	void norm(QList<T*>*) const;

private:
	DB* mDb;



};







