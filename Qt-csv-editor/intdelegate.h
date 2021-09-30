#ifndef INTDELEGATE_H
#define INTDELEGATE_H

#include <QStyledItemDelegate>

class IntDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit IntDelegate(QObject *parent = nullptr);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
};

#endif // INTDELEGATE_H
