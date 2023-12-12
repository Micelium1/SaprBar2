#ifndef TABLESTRUCTURES_H
#define TABLESTRUCTURES_H

class RodsTableDataStructure
{
private:
    double lenght,area,E_const,forse,allowed_tension;
public:
    RodsTableDataStructure(double _lenght, double _area,double _E_const, double _forse, double _allowed_tension);
    double lenghtGet() const;
    double areaGet() const;
    double E_constGet() const;
    double forceGet() const;
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

#endif // TABESTRUCTURES_H
