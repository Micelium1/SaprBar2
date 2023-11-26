#include "validatedcellwidget.h"
#include "QLineEdit"
#include "QDoubleValidator"
#include "QStyleOption"
#include "limits"
ValidatedCellWidget::ValidatedCellWidget(QObject *parent,bool _NegRestriction)
    : QStyledItemDelegate(parent)
{
    NegRestriction = _NegRestriction;
}
QWidget *ValidatedCellWidget::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QLineEdit* Editor = new QLineEdit(parent);
    if (!NegRestriction)
    {
        Editor->setValidator(new QDoubleValidator(Editor));
    }
    else
    {
        Editor->setValidator(new QDoubleValidator(0.0,DBL_MAX,-1,Editor));
    }
    return Editor;
}
