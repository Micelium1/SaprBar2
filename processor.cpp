#include "processor.h"
#include "ui_processor.h"

Processor::Processor(const std::vector<RodsTableDataStructure>* _RodsTable,const std::vector<NodesTableDataStructure>* _NodesTable, bool* _Sealings,QDialog *parent) :
    QDialog(parent),
    ui(new Ui::Processor)
{
    RodsTable = _RodsTable;
    NodesTable = _NodesTable;
    Sealings = _Sealings;
    ui->setupUi(this);
    //for (const RodsTableDataStructure& current_rod:*RodsTable)
    //    qDebug("%f",current_rod.lenghtGet());
    //for (unsigned int i = 0;i < NodesTable.size();++i)
    //    qDebug("%f",NodesTable[i].nodeForseGet());
}
Processor::~Processor()
{
    delete ui;
}
