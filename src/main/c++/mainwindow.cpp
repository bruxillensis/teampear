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
#include "piedialog.h"

using namespace std;

static std::vector<std::pair<std::string,std::vector<std::pair<std::string,std::string> > > > q;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTreeWidgetItem *t = new QTreeWidgetItem(0);
    //std::pair<String,Vector<pair<String,int>>> pair;


    std::vector<std::pair<std::string,std::vector<std::pair<std::string,std::string> > > > q;
    std::pair<std::string,std::vector<std::pair<std::string,std::string> > > p;
    std::pair<std::string,std::string> s;

    s.first = std::string("Nazim the idiot");
    s.second = std::string("12");

    std::vector<std::pair<std::string,std::string> > p2;

    p2.push_back(s);
    p.first = std::string("Multimedia");
    p.second = p2;

    q.push_back(p);

    for(int i=0; i<q.size(); i++){
        std::pair<std::string,std::vector<std::pair<std::string,std::string> > > a;
        std::vector<std::pair<std::string,std::string> > a2;
        std::pair<std::string,std::string> b;

        a =  q.back();
        q.pop_back();
        a2 = a.second;
        b = a2.back();
        a2.pop_back();





   // pair.first="Max Ingram";
   // pair.second = "17";
QString qw = qw.fromStdString(b.first + " " + b.second);

    QTreeWidget * tree = ui->treeWidget;
    std::string pubType = a.first;


    t->setText(0,qw);

//ui->treeWidget->itemAt(0,0)->addChild(t);

  // FIX
    if(!pubType.compare("Book Chapters"))
        ui->treeWidget->itemAt(0,0)->addChild(t);
    else if(!pubType.compare("Books"))
        ui->treeWidget->itemAt(0,20)->addChild(t);
    else if(!pubType.compare("Books Edited"))
        ui->treeWidget->itemAt(0,40)->addChild(t);
    else if(!pubType.compare("Case Reports"))
        ui->treeWidget->itemAt(0,60)->addChild(t);
    else if(!pubType.compare("Clinical Care Guidelines"))
        ui->treeWidget->itemAt(0,80)->addChild(t);
    else if(!pubType.compare("Commentaries"))
        ui->treeWidget->itemAt(0,100)->addChild(t);
    else if(!pubType.compare("Conference Precedings"))
        ui->treeWidget->itemAt(0,120)->addChild(t);
    else if(!pubType.compare("Editorials"))
        ui->treeWidget->itemAt(0,140)->addChild(t);
    else if(!pubType.compare("Invited Articles"))
        ui->treeWidget->itemAt(0,160)->addChild(t);
    else if(!pubType.compare("Journal Article"))
        ui->treeWidget->itemAt(0,180)->addChild(t);
    else if(!pubType.compare("Letters to Editor"))
        ui->treeWidget->itemAt(0,200)->addChild(t);
    else if(!pubType.compare("Magazine Entries"))
        ui->treeWidget->itemAt(0,220)->addChild(t);
    else if(!pubType.compare("Manuals"))
        ui->treeWidget->itemAt(0,240)->addChild(t);
    else if(!pubType.compare("Monographs"))
        ui->treeWidget->itemAt(0,260)->addChild(t);
    else if(!pubType.compare("Multimedia"))
        ui->treeWidget->itemAt(0,280)->addChild(t);
    else if(!pubType.compare("Newsletter Articles"))
        ui->treeWidget->itemAt(0,300)->addChild(t);
    else if(!pubType.compare("Newspaper Articles"))
        ui->treeWidget->itemAt(0,320)->addChild(t);
    else if(!pubType.compare("Published Abstract"))
        ui->treeWidget->itemAt(0,340)->addChild(t);
    else if(!pubType.compare("Supervised Student Publications"))
        ui->treeWidget->itemAt(0,360)->addChild(t);
    else if(!pubType.compare("Websites / Videos"))
        ui->treeWidget->itemAt(0,380)->addChild(t);
    else if(!pubType.compare("Working Papers"))
        ui->treeWidget->itemAt(0,400)->addChild(t);
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
    PieDialog d(this);
    d.exec();
}

void MainWindow::setVector(std::vector<std::pair<std::string,std::vector<std::pair<std::string,std::string> > > > p)
{
    q = p;
}

std::vector<std::pair<std::string,std::vector<std::pair<std::string,std::string> > > > MainWindow::getVector()
{
    return q;
}
