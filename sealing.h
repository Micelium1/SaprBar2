#ifndef SEALING_H
#define SEALING_H
#include <QGraphicsRectItem>
class Sealing : public QGraphicsRectItem
{
public:
    Sealing(bool _left,QGraphicsItem *parent = nullptr);
    void paint(QPainter * painter,   const QStyleOptionGraphicsItem * option,   QWidget * widget);
private:
    bool left;
};

#endif // SEALING_H
