#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "preproccessor.h"
#include <QMainWindow>

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

private:
    Ui::MainWindow *ui;
    std::vector<RodsTableDataStructure>* RodsTable = nullptr;
    std::vector<NodesTableDataStructure>* NodesTable = nullptr;
    bool* Sealings = nullptr;
    double** vectorDelta;
};
#endif // MAINWINDOW_H
