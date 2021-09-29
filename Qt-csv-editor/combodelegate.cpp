#include "combodelegate.h"

QRegularExpression ComboDelegate::enumRegex = QRegularExpression("enum\\((.*)\\)");

ComboDelegate::ComboDelegate(QObject* parent) : QStyledItemDelegate(parent)
{

}

QWidget *ComboDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QComboBox* box = new QComboBox(parent);
    const QStandardItemModel* model = qobject_cast<const QStandardItemModel*>(index.model());
    if(model)
    {
        populateFromHeader(box,model,index.column());
    }

    return box;
}

void ComboDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString value = index.data().toString();
    QComboBox* box = qobject_cast<QComboBox*>(editor);
    if(box)
    {
        box->setCurrentText(value);
    }
}

void ComboDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

void ComboDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox* box = qobject_cast<QComboBox*>(editor);
    QStandardItemModel* stdModel = qobject_cast<QStandardItemModel*>(model);
    if(box && stdModel)
    {
        stdModel->setItem(index.row(),index.column(),new QStandardItem(box->currentText()));
    }
}

void ComboDelegate::populateFromHeader(QComboBox* box, const QStandardItemModel* model, int columnIndex) const
{
    QRegularExpressionMatch match = enumRegex.match(model->headerData(columnIndex,Qt::Horizontal).toString());
    if(match.captured(1).isEmpty())
    {
        return;
    }
    QStringList enums = match.captured(1).split(',',Qt::SkipEmptyParts);
    box->insertItems(0,enums);
}
