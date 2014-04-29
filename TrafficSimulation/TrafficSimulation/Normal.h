#pragma once

#include "rect.h"

class Normal
{
public:
	Normal(void);
	~Normal(void);

	virtual Rect border() const = 0; // boundingRect, 这里的Rect是自定义类型(正常坐标系), 不是qt的那个QRect
	virtual void norm(qreal maxL, QPointF center)=0; // 参数分别是最长边框和中心点

};

