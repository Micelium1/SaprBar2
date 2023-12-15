#ifndef POSTPROCESSOR_H
#define POSTPROCESSOR_H

#include "myfunc.h"
#include "tablestructures.h"
#include <QWidget>
#include <QDialog>

namespace Ui {
class Postprocessor;
}

class Postprocessor : public QDialog
{
    Q_OBJECT

public:
    explicit Postprocessor(const std::vector<RodsTableDataStructure> *RodsTable, const std::vector<NodesTableDataStructure> *NodesTable, bool *Sealings,std::vector<MyFunc>* vectorNx,std::vector<MyFunc>* vectorUx,std::vector<QString> rods_header,std::vector<QString> nodes_header, QDialog *parent = nullptr);

    ~Postprocessor();

    void SaveButtonClicked();

    void ExitButton_clicked();

    void InputChanged(QString Input);

    void RodSetted(int rod);
private:
    Ui::Postprocessor *ui;

    const std::vector<RodsTableDataStructure>* RodsTable;

    const std::vector<NodesTableDataStructure>* NodesTable;

    bool* Sealings;

    std::vector<MyFunc>* vectorNx;

    std::vector<MyFunc>* vectorUx;

    std::vector<QString> rods_header;

    std::vector<QString> nodes_header;

    int actual_rod;

    MyFunc* actual_func_Nx;

    MyFunc* actual_func_Ux;
};

#endif // POSTPROCESSOR_H
