#ifndef PREPROCCESSOR_H
#define PREPROCCESSOR_H

#include <QDialog>

namespace Ui {
class Preproccessor;
}
class RodsTableDataStructure;
class NodesTableDataStructure;
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

    std::vector<RodsTableDataStructure> RodsTableGet();

    std::vector<NodesTableDataStructure> NodesTableGet();
private:
    Ui::Preproccessor *ui;
};
class RodsTableDataStructure
{
private:
    double lenght,area,E_const,forse,allowed_tension;
public:
    RodsTableDataStructure(double _lenght, double _area,double _E_const, double _forse, double _allowed_tension);
    double lenghtGet();
    double areaGet();
    double E_constGet();
    double forseGet();
    double allowedTensionGet();
};
class NodesTableDataStructure
{
private:
    double node_forse;
public:
    NodesTableDataStructure(double _node_forse);
    double nodeForseGet();
};

#endif // PREPROCCESSOR_H
