#include "validatedcellwidget.h"
#include "QLineEdit"
#include "QDoubleValidator"
#include "QStyleOption"
#include "limits"
#include "float.h"
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
        Editor->setValidator(new QDoubleValidator(LDBL_MIN,LDBL_MAX,-1,Editor));
    }
    return Editor;
}
