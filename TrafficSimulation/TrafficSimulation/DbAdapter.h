#pragma once

#include "db.h"
#include "node.h"
#include "conn.h"
#include "rect.h"

class Edge;
class TurnRestrict;
class RoadPermission;
class TrafficVolume;
class Speed;
class Capability;

class DbAdapter
{
public:
	DbAdapter(void);
	~DbAdapter(void);
	// get
	QList<Node*> loadNormNodes();
	QList<Edge*> loadEdges();
	QList<BusRoute*> loadBusRoutes();
	QList<TurnRestrict*> loadTurnRestrictions();
	QList<RoadPermission*> loadTrafficForbid();
	QList<RoadPermission*> loadTrafficNumLimit();
	QList<TrafficVolume*> loadNodeTrafficVolume();
	QList<TrafficVolume*> loadRoadTrafficVolume();
	QList<Capability*> loadNodeCapability();
	QList<Capability*> loadRoadCapability();
	QList<Speed*> loadSpeed();

	// set
	void setDbPath(QString);

private:
	template <class T>
	Rect boundingRect(const QList<T*> *) const;

	template <class T>
	void norm(QList<T*>*) const;

private:
	DB* mDb;



};







