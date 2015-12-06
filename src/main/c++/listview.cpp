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

	//Publication & Grants
	vector<node*>* children = root->getChildren();
	
		if (strcmp(root->getFirst().c_str(), "Publications") == 0)
	{
		this->setColumnCount(2);
		this->setHeaderLabels(QStringList() << "Name" << "Total");

	}
	else if (strcmp(root->getFirst().c_str(), "Grants and Clinical Funding") == 0)
	{
		this->setColumnCount(3);
		this->setHeaderLabels(QStringList() << "Name" << "# Total " << "$ Total");
	}
	else if (strcmp(root->getFirst().c_str(), "Programs") == 0)
	{
		this->setColumnCount(3);
		this->setHeaderLabels(QStringList() << "Name" << "Hour" << "Student");
	}
	else
	{
		this->setColumnCount(2);
		this->setHeaderLabels(QStringList() << "Name" << "Total");
	}

		QTreeWidgetItem *itm = new QTreeWidgetItem(this);
		
		populateList(root, itm);
}




void ListView::populateList(node* root, QTreeWidgetItem* parent)
{
	QTreeWidgetItem* itm = new QTreeWidgetItem();
	itm->setText(0, QString::fromStdString(root->getFirst()));
	itm->setText(1, QString::number(root->getSecond()));
	if (root->getThird() != NULL)
	{
		itm->setText(2, QString::number(root->getSecond()));
	}
	if (root->getFourth() != NULL)
	{
		itm->setText(2, QString::number(root->getFourth()));
	}

	parent->addChild(itm);

	vector<node*>* children = root->getChildren();

	for (int i = 0; i < children->size(); i++)
	{
		populateList(children->at(i), itm);
	}
}