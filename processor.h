#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "tablestructures.h"
#include <QDialog>
#include "myfunc.h"

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

    std::vector<MyFunc>* VectorNxCalculator(double* vectorDelta,const std::vector<RodsTableDataStructure>* RodsTable);

    std::vector<MyFunc>* VectorUxCalculator(double* vectorDelta,const std::vector<RodsTableDataStructure>* RodsTable);

    std::vector<MyFunc>* GetvectorNx();

    std::vector<MyFunc>* GetvectorUx();

    void ExitButton_clicked();

private:
    Ui::Processor *ui;
    double* vectorDelta;
    std::vector<MyFunc>* vectorNx;
    std::vector<MyFunc>* vectorUx;

};

#endif // PROCESSOR_H
