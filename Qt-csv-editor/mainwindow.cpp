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

void MainWindow::onMdiChildClosing(QString filename)
{
    qDebug() << "On close: " << filename;
    for(QAction* action : ui->windowMenu->actions())
    {
        qDebug() << action->text();
        if(action->text() == filename)
        {
            ui->windowMenu->removeAction(action);
        }
    }
}

MdiChild *MainWindow::createChild(QString &fileName)
{
    MdiChild* newChild = new MdiChild(ui->mdiArea);
    newChild->setAttribute(Qt::WA_DeleteOnClose,true);
    ui->mdiArea->addSubWindow(newChild);
    newChild->openFile(fileName);
    newChild->show();
    connect(newChild,&MdiChild::onClose,this,&MainWindow::onMdiChildClosing);

    QAction* newAction = new QAction(fileName,this);
    windowActions.push_back(newAction);
    ui->windowMenu->addAction(newAction);

    connect(newAction,&QAction::triggered,this,&MainWindow::onChooseWindowAction);

    return newChild;
}

void MainWindow::onExitAction()
{
    this->close();
}

