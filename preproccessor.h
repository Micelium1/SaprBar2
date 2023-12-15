#ifndef PREPROCCESSOR_H
#define PREPROCCESSOR_H

#include "sealing.h"
#include <QDialog>
#include "tablestructures.h"

namespace Ui {
class Preproccessor;
}
class RodsTableDataStructure;
class NodesTableDataStructure;

class QGraphicsRectItem;
class QGraphicsEllipseItem;
class QGraphicsPolygonItem;
class MyRect;
class Node;

class Preproccessor : public QDialog
{
    Q_OBJECT

public:
    explicit Preproccessor(const std::vector<RodsTableDataStructure>* _RodsTable, const std::vector<NodesTableDataStructure>* _NodesTable, bool* Sealings,QDialog *parent = nullptr);
    ~Preproccessor();


    void AddToRodsButton_clicked();

    void DeleteFromRodsButton_clicked();

    void SaveToFileButton_clicked();

    void LoadFromFileButton_clicked();

    void NonSealingDefence(bool checked);

    void ExitButton_clicked();

    void RodsDrawer();

    void RodsDeleter(int row);

    void NodesForcesDrawer(int row,int column);

    void RodsModifier(int row, int column);

    void ForceDrawer(double value, int row);

    QPolygonF ForceLine(double x,double value);

    std::vector<RodsTableDataStructure>* RodsTableGet();

    std::vector<NodesTableDataStructure>* NodesTableGet();

    std::vector<QString> RodsHeaderGet();

    std::vector<QString> NodesHeaderGet();

    bool* SealingsGet();

    std::vector<MyRect*> RodsItems;

    std::vector<Node*> NodesItems;

    Sealing* SealingItems[2];




private:

    Ui::Preproccessor *ui;
};

#endif // PREPROCCESSOR_H
