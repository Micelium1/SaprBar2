#include "sealing.h"
#include "qpainter.h"

Sealing::Sealing(bool _left, QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
    left = _left;
    setRect(rect().x(),rect().y(),50,rect().height());
    if (left) moveBy(-50,0);
    setZValue(-1);
    setPen(QPen(Qt::white));
}


void Sealing::paint(QPainter * painter,   const QStyleOptionGraphicsItem * option,   QWidget * widget)
{
    if (left)
    {
        const static QPixmap sealing_left(":resourse/Sealings/SealingLeft.png");
        painter->drawPixmap(QRectF(rect().x(),rect().y(),rect().width(),rect().height()-3),sealing_left,QRectF(sealing_left.rect()));
    }
    else
    {
        const static QPixmap sealing_right(":resourse/Sealings/SealingRight.png");
        painter->drawPixmap(QRectF(rect().x(),rect().y(),rect().width(),rect().height()-3),sealing_right,QRectF(sealing_right.rect()));
    }

    QGraphicsRectItem::paint(painter, option, widget);
}
