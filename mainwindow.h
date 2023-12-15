#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "myfunc.h"
#include <QMainWindow>
#include "tablestructures.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_PreprocessorButton_clicked();

    void on_ProcessorButton_clicked();

    void on_PostProcessorButton_clicked();

private:
    Ui::MainWindow *ui;
    std::vector<RodsTableDataStructure>* RodsTable = nullptr;
    std::vector<NodesTableDataStructure>* NodesTable = nullptr;
    std::vector<QString> rods_header;
    std::vector<QString> nodes_header;
    bool* Sealings = nullptr;
    std::vector<MyFunc>* vectorNx;
    std::vector<MyFunc>* vectorUx;
};
#endif // MAINWINDOW_H
