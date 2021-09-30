#include "booldelegate.h"

#include <QCheckBox>
#include <QStandardItemModel>

BoolDelegate::BoolDelegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

QWidget *BoolDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QCheckBox* box = new QCheckBox(parent);
    const QStandardItemModel* model = qobject_cast<const QStandardItemModel*>(index.model());
    if(model)
    {
        box->setChecked(index.data().toBool());
    }

    return box;
}

void BoolDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QCheckBox* box = qobject_cast<QCheckBox*>(editor);
    if(box)
    {
        box->setChecked(index.data().toBool());
    }
}

void BoolDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

void BoolDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QCheckBox* box = qobject_cast<QCheckBox*>(editor);
    QStandardItemModel* stdModel = qobject_cast<QStandardItemModel*>(model);
    if(box && stdModel)
    {
        stdModel->setItem(index.row(),index.column(),new QStandardItem(box->isChecked()? QString("true") : QString("false")));
    }
}
