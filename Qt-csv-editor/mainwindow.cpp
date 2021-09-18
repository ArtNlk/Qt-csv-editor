#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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

}

void MainWindow::onCloseAllAction()
{

}

void MainWindow::onAboutAction()
{
    QMessageBox::information(
            this,
            tr("Abou CSV editor"),
            tr("This app was created by ArtNlk") );
}

void MainWindow::onExitAction()
{
    this->close();
}

