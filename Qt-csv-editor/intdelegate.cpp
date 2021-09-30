#include "intdelegate.h"

#include <QSpinBox>
#include <QStandardItemModel>

IntDelegate::IntDelegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

QWidget *IntDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSpinBox* box = new QSpinBox(parent);
    box->setRange(INT_MIN,INT_MAX);
    const QStandardItemModel* model = qobject_cast<const QStandardItemModel*>(index.model());
    if(model)
    {
        box->setValue(index.data().toInt());
    }

    return box;
}

void IntDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QSpinBox* box = qobject_cast<QSpinBox*>(editor);
    if(box)
    {
        box->setValue(index.data().toInt());
    }
}

void IntDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

void IntDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QSpinBox* box = qobject_cast<QSpinBox*>(editor);
    QStandardItemModel* stdModel = qobject_cast<QStandardItemModel*>(model);
    if(box && stdModel)
    {
        stdModel->setItem(index.row(),index.column(),new QStandardItem(QString::number(box->value())));
    }
}
