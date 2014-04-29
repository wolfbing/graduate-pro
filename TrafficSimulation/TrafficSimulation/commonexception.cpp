#include "commonexception.h"

CommonException::CommonException(QString info)
	: mErrInfo(info)
{

}

CommonException::~CommonException()
{

}

QString CommonException::info() const
{
	return mErrInfo;
}
