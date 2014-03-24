#include "sqlqueryexception.h"

SqlQueryException::SqlQueryException()
{
}

SqlQueryException::SqlQueryException(QString err)
{
    this->mErr = err;
}

SqlQueryException::~SqlQueryException() throw()
{

}

void SqlQueryException::raise() const
{
    throw *this;
}

SqlQueryException *SqlQueryException::clone() const
{
    return new SqlQueryException(*this);
}

QString SqlQueryException::text()
{
    return mErr;
}
