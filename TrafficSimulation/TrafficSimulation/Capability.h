#pragma once

#include <QtCore>

class Capability
{
public:
	Capability(void);
	~Capability(void);

	///// set
	Capability& setMotorCapability(qreal);
	Capability& setNonMotorCapability(qreal);
	Capability& setId(int);

	///// get
	int id() const;
	qreal motorCapability() const;
	qreal nonMotorCapability() const;

private:
	int mId;
	qreal mMotorCapability;
	qreal mNonMotorCapability;
};

