#ifndef LEGENDELEMENT_H
#define LEGENDELEMENT_H

#include <QObject>
#include <QColor>

class LegendElement : public QObject
{
    Q_OBJECT
public:
    explicit LegendElement(QObject *parent = 0);
	// size： 点-半径， 线-宽度
	// color1: 内部颜色, color2：外部颜色
    LegendElement(QString name, int type, float size, QColor color1, QColor color2=QColor());
	LegendElement(const LegendElement & element);
	void operator=(const LegendElement & element);

    enum ElementType {DOT, LINE, THICK_LINE, THICK_DOT};

    LegendElement *setElementName(QString name);
    LegendElement* setElementType(int type);
    LegendElement* setElementSize(float size);
	LegendElement* setElementColor1(QColor color);
	LegendElement* setElementColor2(QColor color);

	QString name();
	int type();
	float size();
	QColor color1();
	QColor color2();

signals:

public slots:

private:
    QString mName;
    int mType;
    float mSize;
	QColor mColor1;
	QColor mColor2;

};

#endif // LEGENDELEMENT_H
