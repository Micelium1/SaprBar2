#ifndef PREPROCCESSOR_H
#define PREPROCCESSOR_H

#include <QDialog>

namespace Ui {
class Preproccessor;
}
class RodsTableDataStructure;
class NodesTableDataStructure;
class QGraphicsRectItem;
class Preproccessor : public QDialog
{
    Q_OBJECT

public:
    explicit Preproccessor(QWidget *parent = nullptr);
    ~Preproccessor();


    void AddToRodsButton_clicked();

    void DeleteFromRodsButton_clicked();

    void SaveToFileButton_clicked();

    void LoadFromFileButton_clicked();

    void NonSealingDefence(bool checked);

    void ExitButton_clicked();

    void RodsDrawer();

    void RodsModifier(int row, int column);

    void NodePowerDrawer(int row);


    std::vector<RodsTableDataStructure>* RodsTableGet();

    std::vector<NodesTableDataStructure>* NodesTableGet();

    bool* SealingsGet();

    std::vector<QGraphicsRectItem*> RodsItems;
private:

    Ui::Preproccessor *ui;
};
class RodsTableDataStructure
{
private:
    double lenght,area,E_const,forse,allowed_tension;
public:
    RodsTableDataStructure(double _lenght, double _area,double _E_const, double _forse, double _allowed_tension);
    double lenghtGet() const;
    double areaGet() const;
    double E_constGet() const;
    double forseGet() const;
    double allowedTensionGet() const;
};
class NodesTableDataStructure
{
private:
    double node_forse;
public:
    NodesTableDataStructure(double _node_forse);
    double nodeForseGet() const;
};

#endif // PREPROCCESSOR_H
