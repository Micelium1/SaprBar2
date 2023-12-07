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
    void MatrixACalculator();
    void VectorBCalculator();
    void VectorDeltaCalculator();

private:
    Ui::Processor *ui;
    const std::vector<RodsTableDataStructure>* RodsTable;
    const std::vector<NodesTableDataStructure>* NodesTable;
    bool* Sealings;
};

#endif // PROCESSOR_H
