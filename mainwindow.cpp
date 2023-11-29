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
    show();
}


void MainWindow::on_ProcessorButton_clicked()
{
    hide();
    Processor Window;
    Window.exec();
    show();
}

