#include "myrect.h"
#include "qpainter.h"




MyRect::MyRect(double x,QGraphicsItem *parent) :QGraphicsRectItem(x,0,0,0,parent)
{
}

void MyRect::paint(QPainter * painter,   const QStyleOptionGraphicsItem * option,   QWidget * widget)
{
    if (force_sign == 1)
    {
        const static QPixmap red_arrows_pix(":resourse/Forces/RedArrows.png");
        painter->drawPixmap(rect(),red_arrows_pix,QRectF(red_arrows_pix.rect()));
    }
    else if (force_sign == -1)
    {
        const static QPixmap blue_arrows_pix(":resourse/Forces/BlueArrows.png");
        painter->drawPixmap(rect(),blue_arrows_pix,QRectF(blue_arrows_pix.rect()));
    }
    QGraphicsRectItem::paint(painter, option, widget);
}
void MyRect::ForceSignSet(double force)
{
    //qDebug("Отработала смена знака");
    if (force > 0) force_sign = 1;
    else if (force == 0) force_sign = 0;
    else force_sign = -1;
    //force_sign = force > 0 ? force < 0 ? -1:0:1;
    //qDebug("Значение %i,", force_sign);
    //qDebug("Значение force %f", force);
    update();
}
