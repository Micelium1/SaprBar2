#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "preproccessor.h"
#include <QDialog>

namespace Ui {
class Processor;
}

class Processor : public QDialog
{
    Q_OBJECT

public:
    explicit Processor(std::vector<RodsTableDataStructure> _RodsTable,std::vector<NodesTableDataStructure> _NodesTable,QDialog *parent = nullptr);
    ~Processor();
    void MatrixACalculator();
    void VectorBCalculator();
    void VectorDeltaCalculator();

private:
    Ui::Processor *ui;
    std::vector<RodsTableDataStructure> RodsTable;
    std::vector<NodesTableDataStructure> NodesTable;
};

#endif // PROCESSOR_H
