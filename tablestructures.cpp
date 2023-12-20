#include "tablestructures.h"

RodsTableDataStructure::RodsTableDataStructure(double _lenght, double _area,double _E_const, double _forse, double _allowed_tension)
{
    lenght = _lenght;
    area = _area;
    E_const = _E_const;
    forse = _forse;
    allowed_tension = _allowed_tension;
}
double RodsTableDataStructure::lenghtGet() const
{
    return lenght;
}
double RodsTableDataStructure::areaGet() const
{
    return area;
}
double RodsTableDataStructure::forceGet() const
{
    return forse;
}
double RodsTableDataStructure::allowedTensionGet() const
{
    return allowed_tension;
}
double RodsTableDataStructure::E_constGet() const
{
    return E_const;
}

// bool RodsTableDataStructure::operator==(RodsTableDataStructure right)
// {
//     return (this->lenght == right.lenght && this->area == right.area && this->E_const == right.E_const && this->forse == right.forse && this->allowed_tension == right.allowedTensionGet());
// }
NodesTableDataStructure::NodesTableDataStructure(double _node_forse)
{
    node_forse = _node_forse;
}
double NodesTableDataStructure::nodeForseGet() const
{
    return node_forse;
}

// bool NodesTableDataStructure::operator==(NodesTableDataStructure right)
// {
//     return this->node_forse == right.node_forse;
// }

