#include "mainwindow.h"
#include "resourcemanager.h"
#include "filemanager.h"
#include "node.h"
#include <QInputDialog>
#include <QDialog>
#include <iostream>
#include <QLabel>
#include <QMessageBox>
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->ui->pushButton->setVisible(false);
    this->rm = new resourceManager();
    this->refreshTree();
}

MainWindow::~MainWindow()
{
    delete rm;
    delete ui;
}

void MainWindow::refreshTree(){
    QTreeWidget* tree = ui->treeWidget;
    tree->clear();
    QList<QTreeWidgetItem *> rootList;
    for(int i=0;i<this->rm->getResources().size();i++){
        if(this->rm->getResources()[i]->isUsable){
            QTreeWidgetItem *root = new QTreeWidgetItem(tree, QStringList(QString::fromStdString(this->rm->getResources()[i]->nodeName)));
            for(int j=0;j<this->rm->getResources()[i]->dependencies.size();j++){
                QTreeWidgetItem *leaf = new QTreeWidgetItem(root, QStringList(QString::fromStdString(this->rm->getResources()[i]->dependencies[j]->nodeName)));
                root->addChild(leaf);
            }
            rootList << root;
        }
    }
    tree->insertTopLevelItems(0, rootList);
}

void MainWindow::on_actionAdd_triggered()
{
    bool ok;
    std::string input = QInputDialog::getText(this,"Add New Link","Please Input a Resource and a Dependency",QLineEdit::Normal,
                                         "",&ok).toStdString();

    if (ok && !input.length()<3&&input.find(' ')!= std::string::npos){
        std::string resource = input.substr(0,input.find(' '));
        std::string dependency = input.substr(input.find(' ')+1,input.length()-1);
        if(resource != dependency){
            this->rm->addLink(resource,dependency);
            this->refreshTree();
        }
    }
}

void MainWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    int index = 0;
    for(int i=0;i<this->rm->getResources().size();i++){
        if(this->rm->getResources()[i]->nodeName==item->text(column).toStdString()){
            index = i;
            break;
        }
    }
    this->ui->pushButton->setVisible(true);
    this->currResource = index;
    node* curr = this->rm->getResources()[index];
    std::string text = "Node Name:\n  " + curr->nodeName + "\nDependencies:\n  ";
    for(int i=0;i<curr->dependencies.size();i++){
        text += curr->dependencies[i]->nodeName+" ";
    }
    text+="\nParents:\n  ";
    for(int i=0;i<curr->parents.size();i++){
        text += curr->parents[i]->nodeName+" ";
    }
    text+="\nResource Status:\n  ";
    if(curr->isUsable){
        text+="This resource is usable!\n";
    }else{
        text+="This resource is unusable!\n";
    }
    ui->textEdit->setText(QString::fromStdString(text));
}

void MainWindow::on_actionAbout_Me_triggered()
{
//    QDialog newD;
//    newD.setWindowTitle("About");
    QMessageBox qb;
    qb.setWindowTitle(QString("About This Project"));
    qb.setText(QString("Author: Shenxiao Mei\nThank you for your time reviewing this program!"));
    qb.exec();
}

void MainWindow::on_pushButton_clicked()
{
    this->rm->deleteResource(this->rm->getResources()[this->currResource]->nodeName);
    refreshTree();

    this->ui->listWidget_2->clear();
    for(int i=0;i<this->rm->getResources().size();i++){
        if(!this->rm->getResources()[i]->isUsable){
            this->ui->listWidget_2->addItem(QString::fromStdString(this->rm->getResources()[i]->nodeName));
        }
    }
}

void MainWindow::on_listWidget_2_itemClicked(QListWidgetItem *item)
{
    int index = 0;
    for(int i=0;i<this->rm->getResources().size();i++){
        if(this->rm->getResources()[i]->nodeName==item->text().toStdString()){
            index = i;
            break;
        }
    }
    this->ui->pushButton->setVisible(false);
    this->currResource = index;
    node* curr = this->rm->getResources()[index];
    std::string text = "Node Name:(Unusable)\n  " + curr->nodeName + "\nDependencies:\n  ";
    for(int i=0;i<curr->dependencies.size();i++){
        text += curr->dependencies[i]->nodeName+" ";
    }
    text+="\nParents:\n  ";
    for(int i=0;i<curr->parents.size();i++){
        text += curr->parents[i]->nodeName+" ";
    }
    text+="\nResource Status:\n  ";
    if(curr->isUsable){
        text+="This resource is usable!\n";
    }else{
        text+="This resource is unusable!\n";
    }
    ui->textEdit->setText(QString::fromStdString(text));

}

void MainWindow::on_action_Open_triggered()
{

    QString filename = QFileDialog::getOpenFileName(
           this,
           tr("Open Document"),
           QDir::currentPath(),
           tr("Text files (*.txt *.rtf)") );
    std::string newFile = filename.toStdString();
    if(newFile.size()>0){
        rm->loadNewFile(newFile);
        refreshTree();
        ui->textEdit->clear();
        ui->listWidget_2->clear();
        ui->pushButton->setVisible(false);
    }
}
