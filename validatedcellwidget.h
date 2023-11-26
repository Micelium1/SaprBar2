#ifndef VALIDATEDCELLWIDGET_H
#define VALIDATEDCELLWIDGET_H

#include <QStyledItemDelegate>

class ValidatedCellWidget : public QStyledItemDelegate
{
public:
    bool NegRestriction;
    ValidatedCellWidget(QObject *parent,bool _NegRestriction = false);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
private:
};

#endif // VALIDATEDCELLWIDGET_H
