#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <QDialog>

namespace Ui {
class Processor;
}

class Processor : public QDialog
{
    Q_OBJECT

public:
    explicit Processor(QDialog *parent = nullptr);
    ~Processor();

private:
    Ui::Processor *ui;
};

#endif // PROCESSOR_H
