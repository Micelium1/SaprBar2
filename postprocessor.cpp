#include "postprocessor.h"
#include "ui_postprocessor.h"
#include "QMessageBox"

Postprocessor::Postprocessor(const std::vector<RodsTableDataStructure>* _RodsTable, const std::vector<NodesTableDataStructure>* _NodesTable, bool* _Sealings, std::vector<MyFunc>* _vectorNx, std::vector<MyFunc>* _vectorUx, QDialog* parent)
    : QDialog(parent)
    , ui(new Ui::Postprocessor)
{
    ui->setupUi(this);
    RodsTable = _RodsTable;
    NodesTable = _NodesTable;
    Sealings = _Sealings;
    vectorNx = _vectorNx;
    vectorUx = _vectorUx;
    actual_rod = 0;
    actual_func_Nx = &(*vectorNx)[0];
    actual_func_Ux = &(*vectorUx)[0];
    int rods_number = RodsTable->size();
    ui->NxTable->setRowCount(rods_number);
    ui->UxTable->setRowCount(rods_number);
    ui->StressTable->setRowCount(rods_number);
    for (int current_rod = 0;current_rod < rods_number; ++current_rod)
    {
        double Nx0 = (*vectorNx)[current_rod].value(0);
        double NxL = (*vectorNx)[current_rod].value((*RodsTable)[current_rod].lenghtGet());
        double Ux0 = (*vectorUx)[current_rod].value(0);
        double UxL = (*vectorUx)[current_rod].value((*RodsTable)[current_rod].lenghtGet());
        double area = (*RodsTable)[current_rod].areaGet();
        double maxStress = qMax(qAbs(Nx0/area),qAbs(NxL/area));
        double maxStressAllowed = (*RodsTable)[current_rod].allowedTensionGet();
        ui->NxTable->setItem(current_rod,0,new QTableWidgetItem(QString::number(Nx0)));
        ui->NxTable->setItem(current_rod,1,new QTableWidgetItem(QString::number(NxL)));
        ui->NxTable->setItem(current_rod,2,new QTableWidgetItem(QString::number(qMax(qAbs(Nx0),qAbs(NxL)))));
        ui->UxTable->setItem(current_rod,0,new QTableWidgetItem(QString::number(Ux0)));
        ui->UxTable->setItem(current_rod,1,new QTableWidgetItem(QString::number(UxL)));
        ui->UxTable->setItem(current_rod,2,new QTableWidgetItem(QString::number((*vectorUx)[current_rod].critical())));
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
    ui->NxOut->setReadOnly(true);
    ui->UxOut->setReadOnly(true);
    ui->StressOut->setReadOnly(true);
    ui->Input->setValidator(new QDoubleValidator(0.0,(*RodsTable)[0].lenghtGet(),-1,ui->Input));
    connect(ui->ExitButton,&QPushButton::clicked, this,&Postprocessor::ExitButton_clicked);
    connect(ui->SaveButton,&QPushButton::clicked,this,&Postprocessor::SaveButtonClicked);
    connect(ui->SelectedRod,&QComboBox::editTextChanged,this,&Postprocessor::RodSetted);
    connect(ui->Input,&QLineEdit::textEdited,this,&Postprocessor::InputChanged);
}


void Postprocessor::SaveButtonClicked()
{

}

void Postprocessor::ExitButton_clicked()
{
    this->close();
}

void Postprocessor::RodSetted(QString rod_st)
{
    actual_rod = rod_st.toInt()-1;
    ui->Input->setValidator(new QDoubleValidator(0.0,(*RodsTable)[actual_rod].lenghtGet(),-1,ui->Input));
    actual_func_Nx = &(*vectorNx)[actual_rod];
    actual_func_Ux = &(*vectorUx)[actual_rod];
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
