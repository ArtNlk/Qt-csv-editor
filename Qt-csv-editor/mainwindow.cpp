#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QMdiSubWindow>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setCentralWidget(ui->mdiArea);

    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::onOpenAction);
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::onExitAction);
    connect(ui->actionCloseAll, &QAction::triggered, this, &MainWindow::onCloseAllAction);
    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::onAboutAction);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onOpenAction()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Открыть CSV"),
                                                    "",
                                                    tr("Файлы CSV")+"(*.csv)");
    if(!fileName.isEmpty())
    {
        createChild(fileName);
    }
}

void MainWindow::onCloseAllAction()
{
    ui->mdiArea->closeAllSubWindows();
}

void MainWindow::onAboutAction()
{
    QMessageBox::information(
            this,
            tr("О программе"),
            tr("Приложение создано ArtNlk" ) );
}

void MainWindow::onSaveAllAction()
{

}

void MainWindow::onChooseWindowAction()
{
    QAction* sender = qobject_cast<QAction*>(QObject::sender());
    QList<QMdiSubWindow*> windows= ui->mdiArea->subWindowList();

    for(QMdiSubWindow* window : windows)
    {
        if(qobject_cast<MdiChild*>(window->widget())->getFilename() == sender->text())
        {
            ui->mdiArea->setActiveSubWindow(window);
            break;
        }
    }
}

void MainWindow::onOpenRecentAction()
{
    QAction* sender = qobject_cast<QAction*>(QObject::sender());
    QString temp = sender->text();
    createChild(temp);
}

void MainWindow::onMdiChildClosing(QString filename)
{
    qDebug() << "On close: " << filename;
    for(QAction* action : ui->windowMenu->actions())
    {
        qDebug() << action->text();
        if(action->text() == filename)
        {
            ui->windowMenu->removeAction(action);
            action->deleteLater();
        }
    }
}

MdiChild *MainWindow::createChild(QString &fileName)
{
    QList<QMdiSubWindow*> windows= ui->mdiArea->subWindowList();
    for(QMdiSubWindow* window : windows)
    {
        qDebug() << qobject_cast<MdiChild*>(window->widget())->getFilename() << " vs " << fileName;
        if(qobject_cast<MdiChild*>(window->widget())->getFilename() == fileName)
        {
            ui->mdiArea->setActiveSubWindow(window);
            return qobject_cast<MdiChild*>(window->widget());
        }
    }
    MdiChild* newChild = new MdiChild(ui->mdiArea);
    newChild->setAttribute(Qt::WA_DeleteOnClose,true);
    ui->mdiArea->addSubWindow(newChild);
    newChild->openFile(fileName);
    newChild->show();
    connect(newChild,&MdiChild::onClose,this,&MainWindow::onMdiChildClosing);

    QAction* newAction = new QAction(fileName,this);
    ui->windowMenu->addAction(newAction);

    connect(newAction,&QAction::triggered,this,&MainWindow::onChooseWindowAction);

    updateRecents(fileName);

    return newChild;
}

void MainWindow::updateRecents(const QString &fileName)
{
    for(int i =0; i < recentsActions.size(); i++)
    {
        if(recentsActions.at(i)->text() == fileName)
        {
            return;
        }
    }

    if(ui->fileMenu->actions().size() > maxRecents)
    {
        ui->fileMenu->removeAction(recentsActions.at(0));
        recentsActions.at(0)->deleteLater();
        recentsActions.removeAt(0);
    }

    QAction* newAction = new QAction(fileName,this);
    recentsActions.push_back(newAction);
    ui->fileMenu->insertAction(ui->actionExit,newAction);

    connect(newAction,&QAction::triggered,this,&MainWindow::onOpenRecentAction);
}

void MainWindow::onExitAction()
{
    this->close();
}

