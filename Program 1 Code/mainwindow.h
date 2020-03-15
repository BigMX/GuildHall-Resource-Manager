#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class resourceManager;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionAdd_triggered();
    void refreshTree();
    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

    void on_actionAbout_Me_triggered();

    void on_pushButton_clicked();

    void on_listWidget_2_itemClicked(QListWidgetItem *item);

    void on_action_Open_triggered();

private:
    Ui::MainWindow *ui;
    resourceManager* rm;
    int currResource;
};
#endif // MAINWINDOW_H
