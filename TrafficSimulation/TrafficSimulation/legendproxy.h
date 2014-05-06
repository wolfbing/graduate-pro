#ifndef LEGENDPROXY_H
#define LEGENDPROXY_H

#include <QGraphicsProxyWidget>

class Legend;
class LegendElement;

class LegendProxy : public QGraphicsProxyWidget
{
	Q_OBJECT

public:
	LegendProxy(QWidget *widget=0);
	~LegendProxy();

	void updateAttr(QList<QColor>, QList<qreal>);
	void updateAttr(QList<QColor> colorList1, QList<QColor> colorList2, QList<qreal> sizeList);
	void setElements(QList<LegendElement>);
	void updateLegend();
	void newUpdateAttr(QList<QColor>, QList<qreal>);
	void newUpdateAttr(QList<QColor> colorList1, QList<QColor> colorList2, QList<qreal> sizeList);

protected:
	QVariant itemChange(GraphicsItemChange change, const QVariant &value);
	void showEvent(QShowEvent *event);

private:
	bool mPosInitialized;
	Legend* mLegendWidget;
	QList<LegendElement> mElements;
	
};

#endif // LEGENDPROXY_H
