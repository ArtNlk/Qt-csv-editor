#ifndef MDICHILD_H
#define MDICHILD_H

#include <QMainWindow>
#include <QStandardItemModel>
#include "csvio.h"

namespace Ui {
class MdiChild;
}

class MdiChild : public QMainWindow
{
    Q_OBJECT

public:
    explicit MdiChild(QWidget *parent = nullptr);
    ~MdiChild();

    const QString& getFilename();

signals:
    void onClose(QString filename);

public slots:
    void openFile(const QString& filename);

    void onCloseAction();
    void onSaveAction();

    void closeEvent(QCloseEvent *event);

private:
    Ui::MdiChild *ui;

    QString fileName;
    QStandardItemModel model;
    CsvIO csv;
};

#endif // MDICHILD_H
