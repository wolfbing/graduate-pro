#ifndef DOTWIDGET_H
#define DOTWIDGET_H

#include <QWidget>

class DotWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DotWidget(QWidget *parent = 0);
    DotWidget* setRadius(float radius);
    DotWidget* setColor(QColor color);

signals:

public slots:

public:
	QSize sizeHint() const;
    

protected:
    void paintEvent(QPaintEvent*);
	
	

private:
    QColor mColor;
    float mRadius;

};

#endif // DOTWIDGET_H
