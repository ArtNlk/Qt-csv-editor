#ifndef COMBODELEGATE_H
#define COMBODELEGATE_H

#include <QStyledItemDelegate>
#include <QComboBox>
#include <QStandardItemModel>
#include <QRegularExpression>

class ComboDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    ComboDelegate(QObject* parent);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

protected:
    void populateFromHeader(QComboBox* box, const QStandardItemModel* model, int columnIndex) const;
    static QRegularExpression enumRegex;
};

#endif // COMBODELEGATE_H
