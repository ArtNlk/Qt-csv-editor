#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>

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

private slots:
    void onOpenAction();
    void onExitAction();
    void onCloseAllAction();
    void onAboutAction();
    void onSaveAllAction();
    void onChooseWindowAction();
    void onOpenRecentAction();
    void onMdiChildClosing(QString filename);

protected:
    Ui::MainWindow *ui;
    static const int maxRecents = 5;
    static const QString recentFilesKey;
    QSettings settings;
    QVector<QAction*> recentsActions;

    MdiChild* createChild(QString& fileName);
    void updateRecents(const QString& fileName);
    void saveRecents();
};
#endif // MAINWINDOW_H
