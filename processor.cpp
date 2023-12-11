#include "processor.h"
#include "ui_processor.h"
Processor::Processor(const std::vector<RodsTableDataStructure>* RodsTable,const std::vector<NodesTableDataStructure>* NodesTable, bool* Sealings,QDialog *parent) :
    QDialog(parent),
    ui(new Ui::Processor)
{
    ui->setupUi(this);
    int nodes_amount = NodesTable->size();
    double** matrixA = MatrixACalculator(RodsTable,Sealings);
    double* vectorB = VectorBCalculator(RodsTable,NodesTable,Sealings);
    vectorDelta = VectorDeltaCalculator(matrixA,vectorB,nodes_amount);
    //for (const RodsTableDataStructure& current_rod:*RodsTable)
    //    qDebug("lenght: %f\narea: %f\nE_const: %f\n",current_rod.lenghtGet(),current_rod.areaGet(),current_rod.E_constGet());
    //for (unsigned int i = 0;i < NodesTable->size();++i)
    //    qDebug("node_force: %f",(*NodesTable)[i].nodeForseGet());
    ui->matrixATable->setRowCount(nodes_amount);
    ui->matrixATable->setColumnCount(nodes_amount);
    ui->vectorBTable->setRowCount(nodes_amount);
    ui->vectorDeltaTable->setRowCount(nodes_amount);
    for (int row = 0; row < nodes_amount;++row)
    {
        for(int column = 0;column < nodes_amount;++column)
        {
            ui->matrixATable->setItem(row,column,new QTableWidgetItem(QString::number(matrixA[row][column])));
        }
        ui->vectorBTable->setItem(row,0,new QTableWidgetItem(QString::number(vectorB[row])));
        ui->vectorDeltaTable->setItem(row,0,new QTableWidgetItem(QString::number(vectorDelta[row])));
        delete[] matrixA[row];
    }
    delete[] matrixA;
    delete[] vectorB;
}
Processor::~Processor()
{
    delete ui;
}
double** Processor::MatrixACalculator(const std::vector<RodsTableDataStructure>* RodsTable,bool* Sealings)
{
    int rods_amount = RodsTable->size();
    int matrix_size = rods_amount + 1;
    double** matrixA = new double*[matrix_size]; //матрица с кол-вом строк matrix_size
    for (int row = 0;row < matrix_size;++row) //для каждой строки создаем массив столбцов
    {
        matrixA[row] = new double[matrix_size];
        for (int column = 0;column < matrix_size;++column)
        {
            matrixA[row][column] = 0;
        }
    }
    for (int bar = 0; bar < rods_amount;++bar)
    {
        if (bar == 1) qDebug("E_const: %f; area: %f; lenght: %f",(*RodsTable)[bar].E_constGet(), (*RodsTable)[bar].areaGet(), (*RodsTable)[bar].lenghtGet());
        matrixA[bar][bar] += (*RodsTable)[bar].E_constGet() * (*RodsTable)[bar].areaGet() / (*RodsTable)[bar].lenghtGet();
        matrixA[bar][bar+1] += -(*RodsTable)[bar].E_constGet() * (*RodsTable)[bar].areaGet() / (*RodsTable)[bar].lenghtGet();
        matrixA[bar+1][bar] += -(*RodsTable)[bar].E_constGet() * (*RodsTable)[bar].areaGet() / (*RodsTable)[bar].lenghtGet();
        matrixA[bar+1][bar+1] += (*RodsTable)[bar].E_constGet() * (*RodsTable)[bar].areaGet() / (*RodsTable)[bar].lenghtGet();
        if (bar == 1) qDebug("22: %f,23: %f\n32: %f,33: %f",matrixA[bar][bar],matrixA[bar][bar+1],matrixA[bar+1][bar],matrixA[bar+1][bar+1]);
    }
    if (Sealings[0])
    {
        matrixA[0][0] = 1;
        matrixA[0][1] = 0;
        matrixA[1][0] = 0;
    }
    if (Sealings[1])
    {
        matrixA[matrix_size - 1][matrix_size - 1] = 1;
        matrixA[matrix_size - 1][matrix_size - 2] = 0;
        matrixA[matrix_size - 2][matrix_size - 1] = 0;
    }
    for (int row = 0;row < matrix_size;++row) //для каждой строки создаем массив столбцов
    {
        for (int column = 0;column < matrix_size;++column)
        {
            qDebug("%f ",matrixA[row][column]);
        }
        qDebug("\n");
    }
    return matrixA;
}
double* Processor::VectorBCalculator(const std::vector<RodsTableDataStructure>* RodsTable,const std::vector<NodesTableDataStructure>* NodesTable,bool* Sealings)
{

    int vector_size = NodesTable->size();
    double* vectorB = new double[vector_size];
    vectorB[0] =Sealings[0] ? 0 : (*NodesTable)[0].nodeForseGet() + 0.5 * (*RodsTable)[0].lenghtGet() * (*RodsTable)[0].forceGet();
    vectorB[vector_size-1] =Sealings[1] ? 0 : (*NodesTable)[vector_size-1].nodeForseGet() + 0.5 * (*RodsTable)[vector_size-2].lenghtGet() * (*RodsTable)[vector_size-2].forceGet();
    for (int Bi = 1;Bi < vector_size-1;++Bi)
    {
        vectorB[Bi] = (*NodesTable)[Bi].nodeForseGet() + 0.5 * (*RodsTable)[Bi-1].lenghtGet() * (*RodsTable)[Bi-1].forceGet() + 0.5 * (*RodsTable)[Bi].lenghtGet() * (*RodsTable)[Bi].forceGet();
    }
    return vectorB;
}

double* Processor::VectorDeltaCalculator(double** matrixA, double* vectorB, int n)
{

    double** matrix = new double*[n];
    for (int i = 0;i < n;++i)
    {
        matrix[i] = new double[n];
        memcpy(matrix[i],matrixA[i],sizeof(double) * n);
    }
    double* b = new double[n];
    memcpy(b,vectorB,sizeof(double) * n);

    // Прямой ход метода Гаусса
    for (int i = 0; i < n; i++) {
        // Поиск максимального элемента в столбце
        int maxRow = i;
        for (int j = i + 1; j < n; j++) {
            if (std::abs(matrix[j][i]) > std::abs(matrix[maxRow][i])) {
                maxRow = j;
            }
        }

        // Обмен строк
        std::swap(matrix[i], matrix[maxRow]);
        std::swap(b[i], b[maxRow]);

        // Приведение к треугольному виду
        for (int j = i + 1; j < n; j++) {
            double ratio = matrix[j][i] / matrix[i][i];
            for (int k = i; k < n; k++) {
                matrix[j][k] -= ratio * matrix[i][k];
            }
            b[j] -= ratio * b[i];
        }
    }

    // Обратный ход метода Гаусса
    double* x = new double[n];
    for (int i = n - 1; i >= 0; i--) {
        double sum = 0.0;
        for (int j = i + 1; j < n; j++) {
            sum += matrix[i][j] * x[j];
        }
        x[i] = (b[i] - sum) / matrix[i][i];
    }
    for (int i = 0;i < n;++i)
    {
        delete[] matrix[i];

    }
    delete[] matrix;
    delete[] b;
    return x;
}

