#ifndef PATHNOTEXISTSEXCEPTION_H
#define PATHNOTEXISTSEXCEPTION_H

#include <QException>
#include <QString>

class PathNotExistsException : public QException
{
public:
    PathNotExistsException(QString err="");
    ~PathNotExistsException()throw();

    void raise() const;
    PathNotExistsException* clone() const;

    QString text();

private:
    QString mErr;

};

#endif // PATHNOTEXISTSEXCEPTION_H
