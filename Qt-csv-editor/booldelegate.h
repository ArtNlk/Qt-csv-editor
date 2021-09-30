#ifndef BOOLDELEGATE_H
#define BOOLDELEGATE_H

#include <QStyledItemDelegate>

class BoolDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit BoolDelegate(QObject *parent = nullptr);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
};

#endif // BOOLDELEGATE_H
