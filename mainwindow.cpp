#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "preproccessor.h"
#include "processor.h"

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
    Preproccessor Window;
    Window.exec();
    RodsTable = Window.RodsTableGet();
    //for (unsigned int i = 0;i < RodsTable.size();++i)
    //    qDebug("%f",RodsTable[i].lenghtGet());
    NodesTable = Window.NodesTableGet();
    //for (unsigned int i = 0;i < NodesTable.size();++i)
    //    qDebug("%f",NodesTable[i].nodeForseGet());

    show();
}


void MainWindow::on_ProcessorButton_clicked()
{
    hide();
    Processor Window(RodsTable,NodesTable);
    Window.exec();

    show();
}

