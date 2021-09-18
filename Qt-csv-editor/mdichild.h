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

private:
    Ui::MdiChild *ui;
};

#endif // MDICHILD_H
