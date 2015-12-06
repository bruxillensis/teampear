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
#include "node.h"


using namespace std;


ListView::ListView(QWidget *parent) : QTreeWidget(parent)
{

	
}

void ListView::makeList(node * root)
{
	this->setColumnCount(4);
	
	//Publication & Grants
	vector<node*>* children = root->getChildren();
	
	if (strcmp(root->getFirst().c_str(), "Publications"))
	{
		this->setHeaderLabels(QStringList() << "Name" << "Total");
	}
	else if (strcmp(root->getFirst().c_str(), "Grant"))
	{
		this->setHeaderLabels(QStringList() << "Name" << "# Total " << "$ Total");
	}
	else if (strcmp(root->getFirst().c_str(), "Programs"))
	{
		this->setHeaderLabels(QStringList() << "Name" << "Hour" << "Student");
	}
	else
	{
		this->setHeaderLabels(QStringList() << "Name" << "Total");
	}

	int size = children->size();
	for (int i = 0; i < size; i++)
	{
		

		if (children->at(i)->getSecond() == 0)
			continue;

		QTreeWidgetItem *itm = new QTreeWidgetItem(this);

		itm->setText(0, QString::fromStdString(children->at(i)->getFirst()));
		itm->setText(1,QString::number(children->at(i)->getSecond()));
		vector<node*>* child = children->at(i)->getChildren();

		int sizet = child->size();
		for (int g = 0; g < sizet; g++)
		{
			

			if (child->at(g)->getSecond() == 0)
				continue;

			QTreeWidgetItem *t = new QTreeWidgetItem();
			

			t->setText(0, QString::fromStdString(child->at(g)->getFirst()));
			t->setText(1, QString::number(child->at(g)->getSecond()));
			if (child->at(g)->getThird() != NULL)
			{
				t->setText(3, QString::fromStdString(child->at(g)->getFirst()));
			}
			if (child->at(g)->getFourth() != NULL)
			{
				t->setText(3, QString::fromStdString(child->at(g)->getFirst()));
			}
			itm->addChild(t);
		}
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
