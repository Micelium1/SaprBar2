#ifndef MYRECT_H
#define MYRECT_H

#include <QGraphicsRectItem>

class MyRect : public QGraphicsRectItem
{
public:
    MyRect(double x,QGraphicsItem *parent = nullptr);
    void paint(QPainter * painter,   const QStyleOptionGraphicsItem * option,   QWidget * widget);
    void ForceSignSet(double force);
private:
    int force_sign = 0;
};

#endif // MYRECT_H
