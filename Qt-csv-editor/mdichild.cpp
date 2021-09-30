#include "mdichild.h"
#include "ui_mdichild.h"

#include <QStringList>
#include <QDebug>
#include <QMessageBox>
#include <algorithm>

#include "combodelegate.h"
#include "intdelegate.h"
#include "booldelegate.h"

QRegularExpression MdiChild::enumRegex = QRegularExpression("enum\\((?:.+,)*(?:.+)\\)");

MdiChild::MdiChild(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MdiChild),
    loaded(false)
{
    ui->setupUi(this);

    setCentralWidget(ui->tableView);

    connect(ui->actionClose,&QAction::triggered,this,&MdiChild::onCloseAction);
    connect(ui->actionSave,&QAction::triggered,this,&MdiChild::onSaveAction);
    connect(ui->actionRemoveRecord,&QAction::triggered,this,&MdiChild::onRemoveRecordAction);
    connect(ui->actionAddRecord,&QAction::triggered,this,&MdiChild::onAddRecordAction);
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
    try {
        csv.open(fileName);
    }  catch (std::runtime_error e) {
        QMessageBox::information(this,
                                 tr("Ошибка открытия файла"),
                                 tr("Ошибка открытия \n%1").arg(_filename));
    }
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
    QString currentHeader;
    for(int i = 0; i < model.columnCount();i++)
    {
        currentHeader = model.headerData(i,Qt::Horizontal).toString();
        if(enumRegex.match(currentHeader).hasMatch())
        {
            ui->tableView->setItemDelegateForColumn(i,new ComboDelegate(&model));
        }
        else if(currentHeader == "int")
        {
            ui->tableView->setItemDelegateForColumn(i,new IntDelegate(&model));
        } else if(currentHeader == "bool")
        {
            ui->tableView->setItemDelegateForColumn(i,new BoolDelegate(&model));
        }
    }
    loaded = true;
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

void MdiChild::onAddRecordAction()
{
    if(!loaded) return;
    QList<QStandardItem*> newRow = QList<QStandardItem*>(model.columnCount());
    model.appendRow(newRow);
}

void MdiChild::onRemoveRecordAction()
{
    if(!loaded) return;
    QItemSelectionModel* selection = ui->tableView->selectionModel();
    QModelIndexList selections = selection->selection().indexes();
    std::sort(selections.begin(),selections.end(),[](QModelIndex a, QModelIndex b){return a.row() > b.row();});
    for(auto& selection : selections)
    {
        model.removeRow(selection.row());
    }
}

void MdiChild::closeEvent(QCloseEvent *event)
{
    this->onCloseAction();
}
