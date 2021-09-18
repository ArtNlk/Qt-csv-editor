#include "mdichild.h"
#include "ui_mdichild.h"

MdiChild::MdiChild(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MdiChild)
{
    ui->setupUi(this);

    setCentralWidget(ui->tableView);

    connect(ui->actionClose,&QAction::triggered,this,&MdiChild::onCloseAction);
    connect(ui->actionSave,&QAction::triggered,this,&MdiChild::onSaveAction);
}

MdiChild::~MdiChild()
{
    delete ui;
}

const QString &MdiChild::getFilename()
{
    return fileName;
}

void MdiChild::openFile(const QString &_filename)
{
    this->fileName = _filename;
    this->setWindowTitle(_filename);
    ui->tableView->setModel(&this->model);
}

void MdiChild::onCloseAction()
{
    emit onClose(fileName);
    qobject_cast<QWidget*>(parent())->close();
    this->close();
}

void MdiChild::onSaveAction()
{

}

void MdiChild::closeEvent(QCloseEvent *event)
{
    this->onCloseAction();
}
