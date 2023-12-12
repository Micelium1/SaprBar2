#include "myfunc.h"

MyFunc::MyFunc(double _A, double _B, double _C)
{
    A = _A;
    B = _B;
    C = _C;
}

MyFunc::MyFunc(double _B,double _C)
{
    B = _B;
    C = _C;
}

double MyFunc::value(double x) const
{
    double val = A * (x * x) + B * x + C;

    return qAbs(val) < qAbs((A+B+C)/3/1e10) ? 0 : val;
}

double MyFunc::critical() const
{
    if (A) return value(-B/(2*A));
    else return 0;
}

QString MyFunc::print() const
{
    QString printer;
    if (A)
    {
        printer +=QString("%1x^2 ").arg(A);
        if (B) printer +=QString(B >= 0 ? "+ %1x ":"- %1x ").arg(std::abs(B));
    }
    else
    {
        if (B)
        {
            printer +=QString("%1x ").arg(B);
            if (C) printer +=QString(C >= 0 ? "+ %1":"- %1").arg(std::abs(C));
        }
        else
        {
            if (C) printer +=QString("%1").arg(C);
        }
    }

    return printer;
}
