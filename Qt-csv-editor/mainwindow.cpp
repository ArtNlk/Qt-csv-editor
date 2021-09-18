#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QMessageBox>
#include <QFileDialog>

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

MdiChild *MainWindow::createChild(QString &fileName)
{
    MdiChild* newChild = new MdiChild(ui->mdiArea);
    ui->mdiArea->addSubWindow(newChild);
    newChild->openFile(fileName);
    newChild->show();

    return newChild;
}

void MainWindow::onExitAction()
{
    this->close();
}

