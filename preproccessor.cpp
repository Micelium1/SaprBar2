#include "preproccessor.h"
#include "node.h"
#include "ui_preproccessor.h"
#include "QDebug"
#include "QJsonDocument"
#include "QJsonArray"
#include "QJsonObject"
#include "QFile"
#include "QFileDialog"
#include "QMessageBox"
#include "validatedcellwidget.h"
#include "QGraphicsRectItem"
#include "myrect.h"
#include <math.h>
Preproccessor::Preproccessor(const std::vector<RodsTableDataStructure>* _RodsTable, const std::vector<NodesTableDataStructure>* _NodesTable, bool* Sealings,QDialog *parent) :
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
    QGraphicsScene* scene = new QGraphicsScene(ui->RodsVewier);
    ui->RodsVewier->setScene(scene);
    ui->NodesTable->setItemDelegateForColumn(0,new ValidatedCellWidget(ui->NodesTable));
    SealingItems[0] = new Sealing(true);
    SealingItems[1] = new Sealing(false);
    scene->addItem(SealingItems[0]);
    scene->addItem(SealingItems[1]);
    if (_RodsTable)
    {
        for(const RodsTableDataStructure& Iter:*_RodsTable)
        {
            RodsDrawer();
            int row = ui->RodsTable->rowCount();
            ui->RodsTable->insertRow(row);

            ui->RodsTable->setItem(row,0,new QTableWidgetItem(QString::number(Iter.lenghtGet())));
            RodsModifier(row,0);
            ui->RodsTable->setItem(row,1,new QTableWidgetItem(QString::number(Iter.areaGet())));
            RodsModifier(row,1);
            ui->RodsTable->setItem(row,2,new QTableWidgetItem(QString::number(Iter.E_constGet())));
            RodsModifier(row,2);
            ui->RodsTable->setItem(row,3,new QTableWidgetItem(QString::number(Iter.forceGet())));
            RodsModifier(row,3);
            ui->RodsTable->setItem(row,4,new QTableWidgetItem(QString::number(Iter.allowedTensionGet())));
            RodsModifier(row,4);
        }
    }
    if (_NodesTable)
    {
    for(const NodesTableDataStructure& Iter:*_NodesTable)
    {
        int row = ui->NodesTable->rowCount();
        ui->NodesTable->insertRow(row);

        ui->NodesTable->setItem(row,0,new QTableWidgetItem(QString::number(Iter.nodeForseGet())));
        NodesForcesDrawer(row,0);
    }
    }
    if (Sealings)
    {
    ui->SealingLeft->setChecked(Sealings[0]);
    ui->SealingRight->setChecked(Sealings[1]);
    }
    if (!RodsItems.empty())
    {

    }
    connect(ui->ExitButton,&QPushButton::clicked, this,&Preproccessor::ExitButton_clicked);
    connect(ui->AddToRodsButton,&QPushButton::clicked,this,&Preproccessor::AddToRodsButton_clicked);
    connect(ui->DeleteFromRodsButton,&QPushButton::clicked,this,&Preproccessor::DeleteFromRodsButton_clicked);
    connect(ui->SaveToFileButton,&QPushButton::clicked,this,&Preproccessor::SaveToFileButton_clicked);
    connect(ui->LoadFromFileButton,&QPushButton::clicked,this,&Preproccessor::LoadFromFileButton_clicked);
    connect(ui->SealingLeft,&QCheckBox::clicked,this,&Preproccessor::NonSealingDefence);
    connect(ui->SealingRight,&QCheckBox::clicked,this,&Preproccessor::NonSealingDefence);
    connect(ui->RodsTable,&QTableWidget::cellChanged,this,&Preproccessor::RodsModifier);
    connect(ui->NodesTable,&QTableWidget::cellChanged,this,&Preproccessor::NodesForcesDrawer);
}
void Preproccessor::RodsDrawer()
{
    QGraphicsScene* scene = ui->RodsVewier->scene();
    double x = 0;

    for(QGraphicsRectItem* current_rod:RodsItems)
    {
        x+= current_rod->rect().width();
    }
    RodsItems.emplace_back(new MyRect(x));
    scene->addItem(RodsItems.back());
    if (NodesItems.empty())
    {
        NodesItems.emplace_back(new Node(x));
        scene->addItem(NodesItems.back());
    }
    NodesItems.emplace_back(new Node(x));
    scene->addItem(NodesItems.back());

}
void Preproccessor::ForceDrawer(double value, int row)
{

    RodsItems[row]->ForceSignSet(value);
}
void Preproccessor::NodesForcesDrawer(int row,int column)
{
    NodesItems[row]->SetForce(ui->NodesTable->item(row,column)->text().replace(",",".").toDouble());
}
void Preproccessor::RodsModifier(int row,int column)
{
    if(column == 0)
    {
        double lenght = ui->RodsTable->item(row,column)->text().replace(",",".").toDouble();
        if (lenght < 1) lenght = 1;
        lenght = 140 * log(10*lenght)/log(20);
        double dx = lenght - RodsItems[row]->rect().width();
        RodsItems[row]->setRect(RodsItems[row]->rect().left(),RodsItems[row]->rect().y(),lenght,RodsItems[row]->rect().height());
        SealingItems[1]->moveBy(dx,0);
        for(int rod_number = RodsItems.size();row < rod_number;++row)
        {
            NodesItems[row+1]->moveBy(dx,0);

            if (row + 1 == rod_number)
            {
                break;
            }
            RodsItems[row+1]->moveBy(dx,0);
        }
    }
    else if(column == 1)
    {
        double area =ui->RodsTable->item(row,column)->text().replace(",",".").toDouble();
        if (area < 1) area = 1;
        area = 280 * log(10*area)/log(1000);
        double max_h = area;
        for(MyRect* current_rod:RodsItems)
        {
            max_h = qMax(max_h,current_rod->rect().height());
        }

        RodsItems[row]->setRect(RodsItems[row]->rect().left(),-area/2,RodsItems[row]->rect().width(),area);

        SealingItems[0]->setRect(SealingItems[0]->rect().x(),-max_h/2,SealingItems[0]->rect().width(),max_h);
        SealingItems[1]->setRect(SealingItems[1]->rect().x(),-max_h/2,SealingItems[1]->rect().width(),max_h);

    }
    else if(column == 2)
        ;
    else if (column == 3)
    {
        ForceDrawer(ui->RodsTable->item(row,column)->text().replace(",",".").toDouble(),row);
    }


}

void Preproccessor::RodsDeleter(int row)
{
    double dx = -RodsItems[row]->rect().width();
    for(int rod_number = RodsItems.size(),current_row = row;current_row < rod_number;++current_row)
    {
        NodesItems[current_row+1]->moveBy(dx,0);

        if (current_row + 1 == rod_number)
        {
            break;
        }
        RodsItems[current_row+1]->moveBy(dx,0);
    }
    delete RodsItems[row];
    delete NodesItems[row+1];
    RodsItems.erase(RodsItems.begin()+row);
    NodesItems.erase(NodesItems.begin()+row + 1);

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
    RodsDrawer();
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
        RodsDeleter(RodsCount-1);
        ui->RodsTable->removeRow(RodsCount-1);
        ui->NodesTable->removeRow(RodsCount);
    }
    else
    {
        for(const QTableWidgetSelectionRange &CurrentRange:DeletingObject)
        {
            for(int Iter = CurrentRange.bottomRow();Iter >= CurrentRange.topRow();--Iter)
            {
                RodsDeleter(Iter);
                ui->RodsTable->removeRow(Iter);
                ui->NodesTable->removeRow(Iter+1);
            }

        }
    }
    if (ui->NodesTable->rowCount() == 1)
    {
        ui->NodesTable->removeRow(0);
        delete NodesItems[0];
        NodesItems.erase(NodesItems.begin());
    }
    //qDebug("Nodes: %i",NodesItems.size());

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

    ui->RodsTable->setRowCount(0);
    for(const QJsonValueRef& Iter: AboutToDeserializeRods)
    {
        RodsDrawer();
        QJsonObject Object(Iter.toObject());
        ui->RodsTable->insertRow(ui->RodsTable->rowCount());

        for (int IterColumn = ui->RodsTable->columnCount() - 1;IterColumn >= 0; --IterColumn )
        {

           QTableWidgetItem* Item = new QTableWidgetItem(Object[ui->RodsTable->horizontalHeaderItem(IterColumn)->text()].toString());
           ui->RodsTable->setItem(ui->RodsTable->rowCount()-1,IterColumn,Item);
        }
    }
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

std::vector<RodsTableDataStructure>* Preproccessor::RodsTableGet()
{
    std::vector<RodsTableDataStructure>* RodsTable = new std::vector<RodsTableDataStructure>;
    RodsTable->reserve(ui->RodsTable->rowCount());
    for (int current_row = 0,table_end = ui->RodsTable->rowCount();current_row < table_end;++current_row)
        RodsTable->emplace_back(RodsTableDataStructure(ui->RodsTable->item(current_row,0)->text().replace(",",".").toDouble(),ui->RodsTable->item(current_row,1)->text().replace(",",".").toDouble(),ui->RodsTable->item(current_row,2)->text().replace(",",".").toDouble(),ui->RodsTable->item(current_row,3)->text().replace(",",".").toDouble(),ui->RodsTable->item(current_row,4)->text().replace(",",".").toDouble()));
    return RodsTable;
}
std::vector<NodesTableDataStructure>* Preproccessor::NodesTableGet()
{
    std::vector<NodesTableDataStructure>* NodesTable = new std::vector<NodesTableDataStructure>;
    NodesTable->reserve(ui->NodesTable->rowCount());
    for (int current_row = 0,table_end = ui->NodesTable->rowCount();current_row < table_end;++current_row)
        NodesTable->emplace_back(NodesTableDataStructure(ui->NodesTable->item(current_row,0)->text().replace(",",".").toDouble()));
    return NodesTable;
}

std::vector<QString> Preproccessor::RodsHeaderGet()
{
    std::vector<QString> header;
    int column_count = ui->RodsTable->columnCount();
    for (int i = 0;i < column_count; ++i)
    {
        header.emplace_back(ui->RodsTable->horizontalHeaderItem(i)->text());
    }

    return header;
}
std::vector<QString> Preproccessor::NodesHeaderGet()
{
    std::vector<QString> header;
    int column_count = ui->NodesTable->columnCount();
    for (int i = 0;i < column_count; ++i)
    {
        header.emplace_back(ui->NodesTable->horizontalHeaderItem(i)->text());
    }
    return header;
}
bool* Preproccessor::SealingsGet()
{
    bool* Sealings = new bool[2];
    Sealings[0] = ui->SealingLeft->isChecked();
    Sealings[1] = ui->SealingRight->isChecked();
    return Sealings;
}

