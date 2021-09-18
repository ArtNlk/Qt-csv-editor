#include "mdichild.h"
#include "ui_mdichild.h"

MdiChild::MdiChild(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MdiChild)
{
    ui->setupUi(this);
}

MdiChild::~MdiChild()
{
    delete ui;
}
