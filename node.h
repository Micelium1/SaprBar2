#ifndef NODE_H
#define NODE_H
#include "qgraphicsitem.h"

class Node : public QGraphicsEllipseItem
{
public:
    Node(double x,QGraphicsItem *parent = nullptr);

    void SetForce(double value);

    QGraphicsPolygonItem* GetForce() const;

    ~Node();
private:
    QPolygonF ForceLine(double value);

    QGraphicsPolygonItem* force = nullptr;

};

#endif // NODE_H
