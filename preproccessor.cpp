#include "preproccessor.h"
#include "ui_preproccessor.h"
#include "QDebug"
#include "QJsonDocument"
#include "QJsonArray"
#include "QJsonObject"
#include "QFile"
#include "QFileDialog"
#include "QMessageBox"
#include "validatedcellwidget.h"

Preproccessor::Preproccessor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Preproccessor)
{
    ui->setupUi(this);

    for (int index = 0,ColumCount = ui->RodsTable->columnCount();index < ColumCount;++index)
    {
    switch (index)
    {
    case 3:
    {
        ui->RodsTable->setItemDelegateForColumn(index,new ValidatedCellWidget(ui->RodsTable));
        break;
    }
    default:
    {
        ui->RodsTable->setItemDelegateForColumn(index,new ValidatedCellWidget(ui->RodsTable,true));
        break;
    }
    }
    }
    ui->NodesTable->setItemDelegateForColumn(0,new ValidatedCellWidget(ui->NodesTable));
    connect(ui->ExitButton,&QPushButton::clicked, this,&Preproccessor::ExitButton_clicked);
    connect(ui->AddToRodsButton,&QPushButton::clicked,this,&Preproccessor::AddToRodsButton_clicked);
    connect(ui->DeleteFromRodsButton,&QPushButton::clicked,this,&Preproccessor::DeleteFromRodsButton_clicked);
    connect(ui->SaveToFileButton,&QPushButton::clicked,this,&Preproccessor::SaveToFileButton_clicked);
    connect(ui->LoadFromFileButton,&QPushButton::clicked,this,&Preproccessor::LoadFromFileButton_clicked);
    connect(ui->SealingLeft,&QCheckBox::clicked,this,&Preproccessor::NonSealingDefence);
    connect(ui->SealingRight,&QCheckBox::clicked,this,&Preproccessor::NonSealingDefence);
}

Preproccessor::~Preproccessor()
{
    delete ui;
}

void Preproccessor::ExitButton_clicked()
{
    this->close();
}

void Preproccessor::AddToRodsButton_clicked()
{
    ui->RodsTable->insertRow(ui->RodsTable->rowCount());

    for(int i = 0,RodsRows = ui->RodsTable->columnCount(); i <= RodsRows;++i)
    {
        ui->RodsTable->setItem(ui->RodsTable->rowCount()-1,i,new QTableWidgetItem("0"));
    }
    int NodeRows = ui->NodesTable->rowCount();
    if (NodeRows == 0)
    {
        ui->NodesTable->insertRow(NodeRows);
        ui->NodesTable->setItem(NodeRows++,0,new QTableWidgetItem("0"));
    }
    ui->NodesTable->insertRow(NodeRows);
    ui->NodesTable->setItem(NodeRows,0,new QTableWidgetItem("0"));
}


void Preproccessor::DeleteFromRodsButton_clicked()
{
    int RodsCount = ui->RodsTable->rowCount();
    if (!RodsCount)
    {
        QMessageBox::warning(this,"Warning","Нечего удалять");
        return;
    }
    QList<QTableWidgetSelectionRange> DeletingObject = ui->RodsTable->selectedRanges();
    if (DeletingObject.isEmpty())
    {
        ui->RodsTable->removeRow(RodsCount-1);
        ui->NodesTable->removeRow(RodsCount);
    }
    else
    {
        for(const QTableWidgetSelectionRange &CurrentRange:DeletingObject)
        {
            for(int Iter = CurrentRange.bottomRow();Iter >= CurrentRange.topRow();--Iter)
            {
                ui->RodsTable->removeRow(Iter);
                ui->NodesTable->removeRow(Iter+1);
            }

        }
    }
    if (ui->NodesTable->rowCount() == 1)
    {
        ui->NodesTable->removeRow(0);
    }

}


void Preproccessor::SaveToFileButton_clicked()
{
    if (!ui->NodesTable->rowCount())
    {
        QMessageBox::warning(this,"Warning","Нечего сохранять");
        return;
    }
    QString fileName = QFileDialog::getSaveFileName(this, "Save File", "Construction.json", "JSON files (*.json)");
    if (fileName.isEmpty()) return;
    QJsonArray AboutToSerialize;
    for(int IterRow = 0, BotRow = ui->NodesTable->rowCount() - 1;IterRow <= BotRow;++IterRow)
    {
        QJsonObject Object;
        for (int IterColumn = ui->NodesTable->columnCount() - 1;IterColumn >= 0; --IterColumn )
        {
            Object[ui->NodesTable->horizontalHeaderItem(IterColumn)->text()] = ui->NodesTable->item(IterRow,IterColumn)->text();
        }
        AboutToSerialize.append(Object);
    }
    QJsonArray AboutToSerializeRods;
    for(int IterRow = 0, BotRow = ui->RodsTable->rowCount() - 1;IterRow <= BotRow;++IterRow)
    {
        QJsonObject Object;
        for (int IterColumn = ui->RodsTable->columnCount() - 1;IterColumn >= 0; --IterColumn )
        {
            Object[ui->RodsTable->horizontalHeaderItem(IterColumn)->text()] = ui->RodsTable->item(IterRow,IterColumn)->text();
        }
        AboutToSerializeRods.append(Object);
    }
    QJsonObject Sealings;
    Sealings["SealingLeft"] = ui->SealingLeft->isChecked();
    Sealings["SealingRight"] = ui->SealingRight->isChecked();
    QFile JsonFile(fileName);
    QJsonObject Data;
    Data.insert("Nodes",AboutToSerialize);
    Data.insert("Rods",AboutToSerializeRods);
    Data.insert("Sealings",Sealings);
    JsonFile.open(QFile::WriteOnly);
    JsonFile.write(QJsonDocument(Data).toJson(QJsonDocument::Indented));
    JsonFile.close();
}


void Preproccessor::LoadFromFileButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Save File", "Construction.json", "JSON files (*.json)");
    if (fileName.isEmpty()) return;

    QFile JsonFile(fileName);
    JsonFile.open(QFile::ReadOnly);
    QJsonObject Data = QJsonDocument::fromJson(JsonFile.readAll()).object();
    QJsonArray AboutToDeserialize = Data["Nodes"].toArray();
    QJsonArray AboutToDeserializeRods = Data["Rods"].toArray();
    QJsonObject Sealings = Data["Sealings"].toObject();

    JsonFile.close();
    ui->NodesTable->setRowCount(0);
    for(const QJsonValueRef& Iter: AboutToDeserialize)
    {
        QJsonObject Object(Iter.toObject());
        ui->NodesTable->insertRow(ui->NodesTable->rowCount());
        for (int IterColumn = ui->NodesTable->columnCount() - 1;IterColumn >= 0; --IterColumn )
        {

           QTableWidgetItem* Item = new QTableWidgetItem(Object[ui->NodesTable->horizontalHeaderItem(IterColumn)->text()].toString());
           ui->NodesTable->setItem(ui->NodesTable->rowCount()-1,IterColumn,Item);
        }
    }
    ui->RodsTable->setRowCount(0);
    for(const QJsonValueRef& Iter: AboutToDeserializeRods)
    {
        QJsonObject Object(Iter.toObject());
        ui->RodsTable->insertRow(ui->RodsTable->rowCount());
        for (int IterColumn = ui->RodsTable->columnCount() - 1;IterColumn >= 0; --IterColumn )
        {

           QTableWidgetItem* Item = new QTableWidgetItem(Object[ui->RodsTable->horizontalHeaderItem(IterColumn)->text()].toString());
           ui->RodsTable->setItem(ui->RodsTable->rowCount()-1,IterColumn,Item);
        }
    }
    ui->SealingLeft->setChecked(Sealings["SealingLeft"].toBool());
    ui->SealingRight->setChecked(Sealings["SealingRight"].toBool());
}

void Preproccessor::NonSealingDefence(bool checked)
{
    if (checked) return;
    if (sender() == ui->SealingLeft && !ui->SealingRight->isChecked())
    {
        ui->SealingRight->setChecked(true);
    }
    else if (sender() == ui->SealingRight && !ui->SealingLeft->isChecked())
    {
       ui->SealingLeft->setChecked(true);
    }
}
RodsTableDataStructure::RodsTableDataStructure(double _lenght, double _area,double _E_const, double _forse, double _allowed_tension)
{
    lenght = _lenght;
    area = _area;
    E_const = _E_const;
    forse = _forse;
    allowed_tension = _allowed_tension;
}
double RodsTableDataStructure::lenghtGet()
{
    return lenght;
}
double RodsTableDataStructure::areaGet()
{
    return area;
}
double RodsTableDataStructure::forseGet()
{
    return forse;
}
double RodsTableDataStructure::allowedTensionGet()
{
    return allowed_tension;
}
NodesTableDataStructure::NodesTableDataStructure(double _node_forse)
{
    node_forse = _node_forse;
}
double NodesTableDataStructure::nodeForseGet()
{
    return node_forse;
}
std::vector<RodsTableDataStructure> Preproccessor::RodsTableGet()
{
    std::vector<RodsTableDataStructure> RodsTable;
    for (int current_row = 0,table_end = ui->RodsTable->rowCount();current_row < table_end;++current_row)
        RodsTable.push_back(RodsTableDataStructure(ui->RodsTable->item(current_row,0)->text().toDouble(),ui->RodsTable->item(current_row,1)->text().toDouble(),ui->RodsTable->item(current_row,2)->text().toDouble(),ui->RodsTable->item(current_row,3)->text().toDouble(),ui->RodsTable->item(current_row,4)->text().toDouble()));
    return RodsTable;
}
std::vector<NodesTableDataStructure> Preproccessor::NodesTableGet()
{
    std::vector<NodesTableDataStructure> NodesTable;
    for (int current_row = 0,table_end = ui->NodesTable->rowCount();current_row < table_end;++current_row)
        NodesTable.push_back(NodesTableDataStructure(ui->NodesTable->item(current_row,0)->text().toDouble()));
    return NodesTable;
}

