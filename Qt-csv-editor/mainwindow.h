#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "mdichild.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:


private slots:
    void onOpenAction();
    void onExitAction();
    void onCloseAllAction();
    void onAboutAction();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H