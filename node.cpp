#include "node.h"
#include "qbrush.h"
#include "qgraphicsscene.h"


Node::Node(double x,QGraphicsItem *parent) : QGraphicsEllipseItem(-3,-3,6,6,parent)
{
    setPos(x,0);
}

void Node::SetForce(double value)
{
    if (force != nullptr)
    {
        delete force;
        force = nullptr;
    }
    if (value != 0)
    {
        force = new QGraphicsPolygonItem(ForceLine(value),this);
        force->setBrush(QBrush(value > 0 ? Qt::red : Qt::blue));
        scene()->addItem(force);
    }


}

QGraphicsPolygonItem* Node::GetForce() const
{
    return force;
}


QPolygonF Node::ForceLine(double value)
{
    QPolygonF pol;
    if (value > 0)
    {
        pol << QPoint(0, -2) << QPoint(30, -2) << QPoint(25, -7) << QPoint(40, 0) << QPoint(25, 7) << QPoint(30, 2) << QPoint(0, 2);
    }
    else if (value < 0)
    {
        pol << QPoint(0, -2) << QPoint(-30, -2) << QPoint(-25, -7) << QPoint(-40, 0) << QPoint(-25, 7) << QPoint(-30, 2) << QPoint(0, 2);
    }

    return pol;
}
Node::~Node()
{

}
