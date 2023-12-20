#ifndef MYFUNC_H
#define MYFUNC_H
#include "QString"

class MyFunc
{
public:
    MyFunc(double _A,double _B, double _C);

    MyFunc(double _B,double _C);

    double value(double x) const;

    double criticalValue() const;

    double criticalPoint() const;

    QString print() const;


private:
    double A = 0,B,C;
};

#endif // MYFUNC_H
