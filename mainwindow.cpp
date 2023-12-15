#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "preproccessor.h"
#include "processor.h"
#include "postprocessor.h"

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
    Preproccessor Window(RodsTable,NodesTable,Sealings);//RodsTable,NodesTable,Sealings
    Window.exec();
    if (RodsTable) delete RodsTable;
    if (NodesTable) delete NodesTable;
    if (Sealings) delete[] Sealings;
    RodsTable = Window.RodsTableGet();
    //for (unsigned int i = 0;i < RodsTable.size();++i)
    //    qDebug("%f",RodsTable[i].lenghtGet());
    NodesTable = Window.NodesTableGet();
    //for (unsigned int i = 0;i < NodesTable.size();++i)
    //    qDebug("%f",NodesTable[i].nodeForseGet());
    Sealings = Window.SealingsGet();
    //qDebug("%i",Sealings[0]);
    //qDebug("%i",Sealings[1]);
    nodes_header = Window.NodesHeaderGet();
    rods_header = Window.RodsHeaderGet();
    show();
}


void MainWindow::on_ProcessorButton_clicked()
{
    hide();
    Processor Window(RodsTable,NodesTable,Sealings);
    Window.exec();
    vectorNx = Window.GetvectorNx();
    vectorUx = Window.GetvectorUx();
    show();
}


void MainWindow::on_PostProcessorButton_clicked()
{
    hide();
    qDebug("Cheking header");
    qDebug() << nodes_header[0];
    qDebug() << rods_header;
    Postprocessor Window(RodsTable,NodesTable,Sealings,vectorNx,vectorUx,rods_header,nodes_header);
    Window.exec();
    show();
}

