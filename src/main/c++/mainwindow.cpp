#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <utility>
#include <string>
#include <vector>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

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
