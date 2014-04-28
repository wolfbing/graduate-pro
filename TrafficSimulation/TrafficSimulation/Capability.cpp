#include "Capability.h"


Capability::Capability(void)
{
}


Capability::~Capability(void)
{
}

Capability& Capability::setMotorCapability(qreal capability)
{
	mMotorCapability = capability;
	return *this;
}

Capability& Capability::setNonMotorCapability(qreal capability)
{
	mNonMotorCapability = capability;
	return *this;
}

Capability& Capability::setId(int id)
{
	mId = id;
	return *this;
}

int Capability::id() const
{
	return mId;
}

qreal Capability::motorCapability() const
{
	return mMotorCapability;
}

qreal Capability::nonMotorCapability() const
{
	return mNonMotorCapability;
}
