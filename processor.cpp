#include "processor.h"
#include "ui_processor.h"

Processor::Processor(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::Processor)
{
    ui->setupUi(this);
}

Processor::~Processor()
{
    delete ui;
}
