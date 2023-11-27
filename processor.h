#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <QWidget>

namespace Ui {
class Processor;
}

class Processor : public QWidget
{
    Q_OBJECT

public:
    explicit Processor(QWidget *parent = nullptr);
    ~Processor();

private:
    Ui::Processor *ui;
};

#endif // PROCESSOR_H
