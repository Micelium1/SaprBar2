#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "preproccessor.h"
#include "processor.h"
#include "postprocessor.h"
#include "QMessageBox"

//bool processor_check = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_PreprocessorButton_clicked()
{
    hide();
    Preproccessor Window(RodsTable,NodesTable,Sealings);
    Window.exec();
    // if (*RodsTable != *Window.RodsTableGet() && *NodesTable != *Window.NodesTableGet() && Sealings != Window.SealingsGet())
    // {
    //     processor_check = false;
    // }

    if (RodsTable) delete RodsTable;
    if (NodesTable) delete NodesTable;
    if (Sealings) delete[] Sealings;
    RodsTable = Window.RodsTableGet();
    NodesTable = Window.NodesTableGet();
    Sealings = Window.SealingsGet();
    nodes_header = Window.NodesHeaderGet();
    rods_header = Window.RodsHeaderGet();
    show();
    //processor_check = false;
}


void MainWindow::on_ProcessorButton_clicked()
{

    if (RodsTable == nullptr)
    {
        QMessageBox::warning(this,"Warning","Нет стержней для расчёта");
        return;
    }
    if (RodsTable->empty())
    {
        QMessageBox::warning(this,"Warning","Нет стержней для расчёта");
        return;
    }

    for(const RodsTableDataStructure& Iter : *RodsTable)
    {
        if (Iter.lenghtGet() == 0 || Iter.areaGet() == 0 || Iter.E_constGet() == 0)
        {
            QMessageBox::warning(this,"Warning","обнаружен 0 в длинне, ширине или E стержня");
            show();
            return;
        }
    }
    hide();
    Processor Window(RodsTable,NodesTable,Sealings);
    Window.exec();
    vectorNx = Window.GetvectorNx();
    vectorUx = Window.GetvectorUx();
    show();
    //processor_check = true;
}


void MainWindow::on_PostProcessorButton_clicked()
{
    if (vectorNx == nullptr || vectorUx == nullptr)
    {
        QMessageBox::warning(this,"Warning","Нет результатов работы процессора");
        return;
    }
    // if (!processor_check)
    // {
    //     QMessageBox::warning(this,"Warning","Вы изменили данные в препроцессоре но не обработали их процессором");
    // }
    hide();
    Postprocessor Window(RodsTable,NodesTable,Sealings,vectorNx,vectorUx,rods_header,nodes_header);
    Window.exec();
    show();
}

