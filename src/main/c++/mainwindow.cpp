#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <utility>
#include <string>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <QTCore>
#include <QtGui>
#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include "piedialog.h"
#include "qdebug.h"
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent=0) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::MainWindow(QWidget *parent, std::vector<std::pair<std::string,std::vector<std::pair<std::string,int> > > > q) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    vector = q;
    ui->setupUi(this);

    //std::pair<String,Vector<pair<String,int>>> pair;
    int g = q.size();
    for(int i=0; i<g; i++){
        std::pair<std::string,std::vector<std::pair<std::string,int> > > a;

        std::vector<std::pair<std::string,int> > a2;
        std::pair<std::string,int> b;
        std::cout << q.size() <<" "<< i <<std::endl;
        if(q.size() > 0)
        {
        a =  q.back();
        q.pop_back();
        a2 = a.second;
        if(a2.size() > 0)
        {
            b = a2.back();
            a2.pop_back();
        }
        }
   // pair.first="Max Ingram";
   // pair.second = "17";
    QString qw = QString::fromStdString(b.first + "  " + std::to_string(b.second));
    std::cout << a.first << " " << b.first << " " << b.second << std::endl;
    //QTreeWidget * tree = ui->treeWidget;
    std::string pubType = a.first;
std::cout << pubType << std::endl;
    //std::cout << qw;
QTreeWidgetItem *t = new QTreeWidgetItem();

       t->setText(0,qw);



//ui->treeWidget->itemAt(0,0)->addChild(t);

    // FIX
    if(!pubType.compare("Book Chapters"))
        ui->treeWidget->itemAt(0,0)->addChild(t);

    else if(!pubType.compare("Book"))
        ui->treeWidget->itemAt(0,15)->addChild(t);
    else if(!pubType.compare("Books Edited"))
        ui->treeWidget->itemAt(0,30)->addChild(t);
    else if(!pubType.compare("Case Reports"))
        ui->treeWidget->itemAt(0,45)->addChild(t);
    else if(!pubType.compare("Clinical Care Guidelines"))
        ui->treeWidget->itemAt(0,60)->addChild(t);
    else if(!pubType.compare("Commentaries"))
        ui->treeWidget->itemAt(0,75)->addChild(t);
    else if(!pubType.compare("Conference Precedings"))
        ui->treeWidget->itemAt(0,90)->addChild(t);
    else if(!pubType.compare("Editorials"))
        ui->treeWidget->itemAt(0,105)->addChild(t);
    else if(!pubType.compare("Invited Articles"))
        ui->treeWidget->itemAt(0,120)->addChild(t);
    else if(!pubType.compare("Journal Article"))
        ui->treeWidget->itemAt(0,135)->addChild(t);
    else if(!pubType.compare("Letters to Editor"))
        ui->treeWidget->itemAt(0,150)->addChild(t);
    else if(!pubType.compare("Magazine Entries"))
        ui->treeWidget->itemAt(0,165)->addChild(t);
    else if(!pubType.compare("Manuals"))
        ui->treeWidget->itemAt(0,180)->addChild(t);
    else if(!pubType.compare("Monographs"))
        ui->treeWidget->itemAt(0,195)->addChild(t);
    else if(!pubType.compare("Multimedia"))
        ui->treeWidget->itemAt(0,210)->addChild(t);
    else if(!pubType.compare("Newsletter Articles"))
        ui->treeWidget->itemAt(0,225)->addChild(t);
    else if(!pubType.compare("Newspaper Articles"))
        ui->treeWidget->itemAt(0,240)->addChild(t);
    else if(!pubType.compare("Published Abstract"))
        ui->treeWidget->itemAt(0,255)->addChild(t);
    else if(!pubType.compare("Supervised Student Publications"))
        ui->treeWidget->itemAt(0,270)->addChild(t);
    else if(!pubType.compare("Websites / Videos"))
        ui->treeWidget->itemAt(0,285)->addChild(t);
    else if(!pubType.compare("Working Papers"))
        ui->treeWidget->itemAt(0,300)->addChild(t);

  }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    //ui->treeWidget->


    //qDebug()<<"Item clicked "+item;
}

void MainWindow::on_pushButton_clicked()
{
    pair<string, string> output;
    output.first = ui->startDate->text().toLocal8Bit().constData();
    output.second = ui->endDate->text().toLocal8Bit().constData();
}

void MainWindow::on_actionPie_Chart_triggered()
{
    PieDialog d(this, vector);
    d.exec();
}

void MainWindow::on_actionImport_CSV_triggered()
{
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "C://",
                "CSV files (*.csv)"
                );

    QMessageBox::information(this, tr("File Name"), filename);
    file_name = filename.toStdString();
}

string getFileName()
{
    string h;
    return h;
}
