#include "pathnotexistsexception.h"

PathNotExistsException::PathNotExistsException(QString err)
{
    mErr = err;
}

PathNotExistsException::~PathNotExistsException()throw()
{

}

void PathNotExistsException::raise() const
{
    throw *this;
}

PathNotExistsException *PathNotExistsException::clone() const
{
    return new PathNotExistsException(*this);
}

QString PathNotExistsException::text()
{
    return mErr;
}
