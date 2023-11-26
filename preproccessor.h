#ifndef PREPROCCESSOR_H
#define PREPROCCESSOR_H

#include <QDialog>

namespace Ui {
class Preproccessor;
}

class Preproccessor : public QDialog
{
    Q_OBJECT

public:
    explicit Preproccessor(QWidget *parent = nullptr);
    ~Preproccessor();


    void AddToRodsButton_clicked();

    void DeleteFromRodsButton_clicked();

    void SaveToFileButton_clicked();

    void LoadFromFileButton_clicked();

    void NonSealingDefence(bool checked);
private:
    Ui::Preproccessor *ui;
};

#endif // PREPROCCESSOR_H
