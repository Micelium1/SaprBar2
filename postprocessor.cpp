#include "postprocessor.h"
#include "QJsonDocument"
#include "QJsonArray"
#include "QJsonObject"
#include "QFile"
#include "QFileDialog"
#include "ui_postprocessor.h"
#include "QMessageBox"
#include <limits.h>

Postprocessor::Postprocessor(const std::vector<RodsTableDataStructure>* _RodsTable, const std::vector<NodesTableDataStructure>* _NodesTable, bool* _Sealings, std::vector<MyFunc>* _vectorNx, std::vector<MyFunc>* _vectorUx,std::vector<QString> _rods_header,std::vector<QString> _nodes_header, QDialog* parent)
    : QDialog(parent)
    , ui(new Ui::Postprocessor)
{
    ui->setupUi(this);
    RodsTable = _RodsTable;
    NodesTable = _NodesTable;
    Sealings = _Sealings;
    vectorNx = _vectorNx;
    vectorUx = _vectorUx;
    nodes_header = _nodes_header;
    rods_header = _rods_header;
    actual_rod = 0;
    actual_func_Nx = &(*vectorNx)[0];
    actual_func_Ux = &(*vectorUx)[0];
    int rods_number = RodsTable->size();
    ui->NxTable->setRowCount(rods_number);
    ui->UxTable->setRowCount(rods_number);
    ui->StressTable->setRowCount(rods_number);
    double minStress = INFINITY;
    double minUx = INFINITY;
    double maxNx = 0;
    double maxUx = 0;
    for (int current_rod = 0;current_rod < rods_number; ++current_rod)
    {
        double Nx0 = (*vectorNx)[current_rod].value(0);
        double NxL = (*vectorNx)[current_rod].value((*RodsTable)[current_rod].lenghtGet());
        double Ux0 = (*vectorUx)[current_rod].value(0);
        double UxL = (*vectorUx)[current_rod].value((*RodsTable)[current_rod].lenghtGet());
        double Ux_crit = (*vectorUx)[current_rod].criticalValue();
        double area = (*RodsTable)[current_rod].areaGet();
        double maxStress = qMax(qAbs(Nx0/area),qAbs(NxL/area));
        double maxStressAllowed = (*RodsTable)[current_rod].allowedTensionGet();
        minStress = Nx0 != 0 ? qMin(minStress,qAbs(Nx0/area)) : minStress;
        minStress = NxL != 0 ? qMin(minStress,qAbs(NxL/area)) : minStress;
        minUx = Ux0 != 0 ? qMin(minUx,qAbs(Ux0)) : minUx;
        minUx = UxL != 0 ? qMin(minUx,qAbs(UxL)): minUx;
        minUx = Ux_crit != 0 ? qMin(minUx,qAbs(Ux_crit)): minUx;
        maxNx = qMax(maxNx,qAbs(Nx0));
        maxNx = qMax(maxNx,qAbs(NxL));
        maxUx = qMax(maxUx,qAbs(Ux0));
        maxUx = qMax(maxUx,qAbs(UxL));
        maxUx = qMax(maxUx,qAbs(Ux_crit));
        ui->NxTable->setItem(current_rod,0,new QTableWidgetItem(QString::number(Nx0)));
        ui->NxTable->setItem(current_rod,1,new QTableWidgetItem(QString::number(NxL)));
        ui->NxTable->setItem(current_rod,2,new QTableWidgetItem(QString::number(qMax(qAbs(Nx0),qAbs(NxL)))));
        ui->UxTable->setItem(current_rod,0,new QTableWidgetItem(QString::number(Ux0)));
        ui->UxTable->setItem(current_rod,1,new QTableWidgetItem(QString::number(UxL)));
        ui->UxTable->setItem(current_rod,2,new QTableWidgetItem(QString::number(Ux_crit)));
        ui->UxTable->setItem(current_rod,3,new QTableWidgetItem(QString::number((*vectorUx)[current_rod].criticalPoint())));
        ui->StressTable->setItem(current_rod,0,new QTableWidgetItem(QString::number(Nx0/area)));
        ui->StressTable->setItem(current_rod,1,new QTableWidgetItem(QString::number(NxL/area)));
        ui->StressTable->setItem(current_rod,2,new QTableWidgetItem(QString::number(maxStress)));
        ui->StressTable->setItem(current_rod,3,new QTableWidgetItem(QString::number(maxStressAllowed)));
        if (maxStress > maxStressAllowed)
        {
            ui->StressTable->item(current_rod,2)->setForeground(QBrush(Qt::red));
        }
        ui->SelectedRod->addItem(QString::number(current_rod+1));
    }
    QGraphicsScene* sceneNx = new QGraphicsScene(ui->NxVeiw);
    QGraphicsScene* sceneUx = new QGraphicsScene(ui->UxVeiw);
    QGraphicsScene* sceneStress = new QGraphicsScene(ui->StressVeiw);
    ui->NxVeiw->setScene(sceneNx);
    ui->UxVeiw->setScene(sceneUx);
    ui->StressVeiw->setScene(sceneStress);
    QPolygonF Nx, Ux, Stress;
    double x = 0;
    double draw_x = 0;
    double stress_coef = 10 / (minStress > 0 ? minStress : 1);
    double Ux_coef = 30 / (minUx > 0 ? minUx : 1);
    Nx << QPoint(0,0);
    Ux << QPoint(0,0);
    Stress << QPoint(0,0);
    for (int current_rod = 0;current_rod < RodsTable->size(); ++current_rod)
    {
        double area = (*RodsTable)[current_rod].areaGet();
        double lenght = (*RodsTable)[current_rod].lenghtGet();
        double draw_lenght = lenght >= 1 ? 140 * log(10*lenght)/log(20) : 140 * log(10)/log(20);
        double Nx0 = (*vectorNx)[current_rod].value(0);
        double NxL = (*vectorNx)[current_rod].value(lenght);
        Nx << QPointF(draw_x,-stress_coef * Nx0) << QPointF(draw_x+draw_lenght,-stress_coef * NxL);
        Stress << QPointF(draw_x,-stress_coef * Nx0/area) << QPointF(draw_x+draw_lenght,-stress_coef * NxL/area);
        MyFunc currentUx = (*vectorUx)[current_rod];
        for (int i = 0; i <= 100; ++i)
        {
            Ux << QPointF(draw_x + 0.01 * i * draw_lenght,-Ux_coef * currentUx.value(0.01*i*lenght));
        }
        sceneUx->addLine(draw_x,-Ux_coef * maxUx - 10,draw_x,Ux_coef * maxUx + 10);
        sceneNx->addLine(draw_x, -stress_coef * maxNx - 10,draw_x,stress_coef * maxNx + 10);
        sceneStress->addLine(draw_x,-stress_coef * maxNx - 10,draw_x,stress_coef * maxNx + 10);
        x += lenght;
        draw_x += draw_lenght;
    }
    Nx << QPoint(draw_x,0);
    Ux << QPoint(draw_x,0);
    Stress << QPoint(draw_x,0);
    sceneUx->addLine(draw_x,-Ux_coef * maxUx - 10,draw_x,Ux_coef * maxUx + 10);
    sceneNx->addLine(draw_x, -stress_coef * maxNx - 10,draw_x,stress_coef * maxNx + 10);
    sceneStress->addLine(draw_x,-stress_coef * maxNx - 10,draw_x,stress_coef * maxNx + 10);
    sceneNx->addPolygon(Nx);
    sceneUx->addPolygon(Ux);
    sceneStress->addPolygon(Stress);
    ui->NxOut->setReadOnly(true);
    ui->UxOut->setReadOnly(true);
    ui->StressOut->setReadOnly(true);
    ui->Input->setValidator(new QDoubleValidator(0.0,(*RodsTable)[0].lenghtGet(),-1,ui->Input));
    connect(ui->ExitButton,&QPushButton::clicked, this,&Postprocessor::ExitButton_clicked);
    connect(ui->SaveButton,&QPushButton::clicked,this,&Postprocessor::SaveButtonClicked);
    connect(ui->SelectedRod,&QComboBox::currentIndexChanged,this,&Postprocessor::RodSetted);
    connect(ui->Input,&QLineEdit::textEdited,this,&Postprocessor::InputChanged);
}


void Postprocessor::SaveButtonClicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save File", "Construction.json", "JSON files (*.json)");
    if (fileName.isEmpty()) return;
    QJsonArray AboutToSerialize;
    for(int IterRow = 0, BotRow = NodesTable->size() - 1;IterRow <= BotRow;++IterRow)
    {

        QJsonObject Object;

        Object[nodes_header[0]] = QString::number((*NodesTable)[IterRow].nodeForseGet());


        AboutToSerialize.append(Object);
    }
    QJsonArray AboutToSerializeRods;
    for(int IterRow = 0, BotRow = RodsTable->size() - 1;IterRow <= BotRow;++IterRow)
    {
        QJsonObject Object;

        Object[rods_header[0]] = QString::number((*RodsTable)[IterRow].lenghtGet());
        Object[rods_header[1]] = QString::number((*RodsTable)[IterRow].areaGet());
        Object[rods_header[2]] = QString::number((*RodsTable)[IterRow].E_constGet());
        Object[rods_header[3]] = QString::number((*RodsTable)[IterRow].forceGet());
        Object[rods_header[4]] = QString::number((*RodsTable)[IterRow].allowedTensionGet());

        AboutToSerializeRods.append(Object);
    }
    QJsonObject Sealings;
    Sealings["SealingLeft"] = Postprocessor::Sealings[0];
    Sealings["SealingRight"] = Postprocessor::Sealings[0];

    QJsonArray RodsCalculations;
    for(int IterRow = 0, BotRow = RodsTable->size() - 1;IterRow <= BotRow;++IterRow)
    {
        QJsonArray Rods;
        QJsonObject Object;
        QJsonObject Nx;
        QJsonObject Ux;
        QJsonObject Stress;
        double Lenght = (*RodsTable)[IterRow].lenghtGet();
        double Area = (*RodsTable)[IterRow].areaGet();
        double Nx0 = (*vectorNx)[IterRow].value(0);
        double NxL = (*vectorNx)[IterRow].value(Lenght);
        double Ux0 = (*vectorUx)[IterRow].value(0);
        double UxL = (*vectorUx)[IterRow].value(Lenght);
        double Stress0 = Nx0 / Area;
        double StressL = NxL / Area;
        Object["Nx(x)"] = (*vectorNx)[IterRow].print();
        Object["Ux(x)"] = (*vectorUx)[IterRow].print();
        Nx["Nx0"] = Nx0;
        Nx["NxL"] = NxL;
        Nx["NxMax"] = qMax(qAbs(Nx0),qAbs(NxL));
        Ux["Ux0"] = Ux0;
        Ux["UxL"] = UxL;
        Ux["UxCrit"] = (*vectorUx)[IterRow].criticalValue();
        Stress["Stress0"] = Stress0;
        Stress["StressL"] = StressL;
        Stress["StressMax"] = qMax(qAbs(Stress0),qAbs(StressL));
        Object["Nx"] = Nx;
        Object["Ux"] = Ux;
        Object[rods_header[4]] = QString::number((*RodsTable)[IterRow].allowedTensionGet());

        RodsCalculations.append(Object);
    }
    QFile JsonFile(fileName);
    QJsonObject Data;
    Data.insert("Calculations",RodsCalculations);
    Data.insert("Nodes",AboutToSerialize);
    Data.insert("Rods",AboutToSerializeRods);
    Data.insert("Sealings",Sealings);
    JsonFile.open(QFile::WriteOnly);
    JsonFile.write(QJsonDocument(Data).toJson(QJsonDocument::Indented));
    JsonFile.close();
}

void Postprocessor::ExitButton_clicked()
{
    this->close();
}

void Postprocessor::RodSetted(int rod)
{
    actual_rod = rod;
    ui->Input->setValidator(new QDoubleValidator(0.0,(*RodsTable)[actual_rod].lenghtGet(),-1,ui->Input));
    actual_func_Nx = &(*vectorNx)[actual_rod];
    actual_func_Ux = &(*vectorUx)[actual_rod];
    if (ui->Input->text().replace(",",".").toDouble() < (*RodsTable)[actual_rod].lenghtGet())
    {
        ui->Input->setText(QString::number((*RodsTable)[actual_rod].lenghtGet()));

    }
}

void Postprocessor::InputChanged(QString Input)
{
    Input.replace(",",".");
    double x = Input.toDouble();
    if (x > (*RodsTable)[actual_rod].lenghtGet())
    {
        QMessageBox::warning(this,"Warning","Выход за пределы стержня");
        x = (*RodsTable)[actual_rod].lenghtGet();
        ui->Input->setText(QString::number(x));
    }
    double Nx = actual_func_Nx->value(x);
    ui->NxOut->setText(QString::number(Nx));
    ui->UxOut->setText(QString::number(actual_func_Ux->value(x)));
    ui->StressOut->setText(QString::number(Nx/(*RodsTable)[actual_rod].areaGet()));
}

Postprocessor::~Postprocessor()
{
    delete ui;
}
