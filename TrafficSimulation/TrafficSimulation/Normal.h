#pragma once

#include "rect.h"

class Normal
{
public:
	Normal(void);
	~Normal(void);

	virtual Rect border() const = 0;
	virtual void norm(qreal, QPointF)=0;

};

