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
    explicit Processor(const std::vector<RodsTableDataStructure>* _RodsTable,const std::vector<NodesTableDataStructure>* _NodesTable,bool* Sealings,QDialog *parent = nullptr);
    ~Processor();
    double** MatrixACalculator(const std::vector<RodsTableDataStructure>* RodsTable,bool* Sealings);
    double* VectorBCalculator(const std::vector<RodsTableDataStructure>* RodsTable,const std::vector<NodesTableDataStructure>* NodesTable,bool* Sealings);
    double* VectorDeltaCalculator(double** matrix, double* b, int n);

private:
    Ui::Processor *ui;
    double* vectorDelta;
};

#endif // PROCESSOR_H
