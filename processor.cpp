#include "processor.h"
#include "ui_processor.h"

Processor::Processor(std::vector<RodsTableDataStructure> _RodsTable,std::vector<NodesTableDataStructure> _NodesTable,QDialog *parent) :
    QDialog(parent),
    ui(new Ui::Processor)
{
    RodsTable = _RodsTable;
    NodesTable = _NodesTable;
    ui->setupUi(this);
    //for (unsigned int i = 0;i < RodsTable.size();++i)
    //    qDebug("%f",RodsTable[i].lenghtGet());
    //for (unsigned int i = 0;i < NodesTable.size();++i)
    //    qDebug("%f",NodesTable[i].nodeForseGet());
}
Processor::~Processor()
{
    delete ui;
}
