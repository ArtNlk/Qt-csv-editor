#ifndef MDICHILD_H
#define MDICHILD_H

#include <QMainWindow>

namespace Ui {
class MdiChild;
}

class MdiChild : public QMainWindow
{
    Q_OBJECT

public:
    explicit MdiChild(QWidget *parent = nullptr);
    ~MdiChild();

public slots:
    void openFile(const QString& filename);

private:
    Ui::MdiChild *ui;

    QString fileName;
};

#endif // MDICHILD_H
