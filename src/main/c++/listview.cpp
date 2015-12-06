#include <QtCore>
#include <QtGui>
#include <QtCore>
#include <QtGui>
#include <QMessageBox>
#include <QTreeWidget>
#include "listview.h"
#include "pubTree.h"
#include <QPainter>
#include <vector>
#include <QColor>
#include <iostream>



using namespace std;


ListView::ListView(QWidget *parent) : QTreeWidget(parent)
{

	
}

void ListView::makeList(node * root)
{

	this->setColumnCount(2);
	this->setHeaderLabels(QStringList() << "Col A" << "Col B");

	vector<node*>* children = root->getChildren();
	int size = children->size();
	for (int i = 0; i < size; i++)
	{
		QTreeWidgetItem *itm = new QTreeWidgetItem(this);
		itm->setText(0, QString::fromStdString(children->at(i)->getFirst()));
		itm->setText(1,QString::number(children->at(i)->getSecond()));
	



	}

	
		nodeData = root;
	nodeData->getFirst();

	

}

void ListView::addChild(QTreeWidgetItem* parent, QString name, QString description)
{
	QTreeWidgetItem *itm = new QTreeWidgetItem();
	itm->setText(0, name);
	itm->setText(1, description);
	parent->addChild(itm);
}
