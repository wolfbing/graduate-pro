#pragma once

#include "db.h"
#include "node.h"
#include "conn.h"
#include "rect.h"

class Edge;
class TurnRestrict;

class DbAdapter
{
public:
	DbAdapter(void);
	~DbAdapter(void);

	QList<Node*> loadNormNodes();
	QList<Edge*> loadEdges();
	QList<BusRoute*> loadBusRoutes();
	QList<TurnRestrict*> loadTurnRestrictions();

private:
	template <class T>
	Rect boundingRect(const QList<T*> *) const;

	template <class T>
	void norm(QList<T*>*) const;

private:
	DB* mDb;



};







