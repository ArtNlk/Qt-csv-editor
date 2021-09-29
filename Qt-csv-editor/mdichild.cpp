#include "mdichild.h"
#include "ui_mdichild.h"

#include <QStringList>
#include <QDebug>

#include "combodelegate.h"

QRegularExpression MdiChild::enumRegex = QRegularExpression("enum\\((?:.+,)*(?:.+)\\)");

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
    csv.open(fileName);
    QStringList temp;
    QStringList header;
    csv.parseNext(header);
    int row = 0;
    int col = 0;
    while(csv.parseNext(temp))
    {
        for(auto& field : temp)
        {
            model.setItem(row,col,new QStandardItem(field));
            col++;
        }
        col = 0;
        row++;
    }

    for(int i = 0; i < header.length(); i++)
    {
        model.setHeaderData(i,Qt::Horizontal,QVariant(header[i]));
        //TODO set delegates
    }

    ui->tableView->setModel(&model);

    for(int i = 0; i < model.columnCount();i++)
    {
        if(enumRegex.match(model.headerData(i,Qt::Horizontal).toString()).hasMatch())
        {
            ui->tableView->setItemDelegateForColumn(i,new ComboDelegate(&model));
        }
    }
}

void MdiChild::onCloseAction()
{
    emit onClose(fileName);
    qobject_cast<QWidget*>(parent())->close();
    this->close();
}

void MdiChild::onSaveAction()
{
    csv.saveModel(model);
}

void MdiChild::closeEvent(QCloseEvent *event)
{
    this->onCloseAction();
}
