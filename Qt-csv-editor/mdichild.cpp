#include "mdichild.h"
#include "ui_mdichild.h"

MdiChild::MdiChild(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MdiChild)
{
    ui->setupUi(this);

    setCentralWidget(ui->tableView);
}

MdiChild::~MdiChild()
{
    delete ui;
}

void MdiChild::openFile(const QString &_filename)
{
    this->setWindowTitle(_filename);
}
