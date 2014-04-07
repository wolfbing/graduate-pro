#ifndef LEGENDPROXY_H
#define LEGENDPROXY_H

#include <QGraphicsProxyWidget>

class LegendProxy : public QGraphicsProxyWidget
{
	Q_OBJECT

public:
	LegendProxy(QWidget *widget=0);
	~LegendProxy();

protected:
	QVariant itemChange(GraphicsItemChange change, const QVariant &value);
	void showEvent(QShowEvent *event);

private:
	
};

#endif // LEGENDPROXY_H
