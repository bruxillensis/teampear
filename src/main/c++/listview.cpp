#include <QtCore>
#include <QtGui>
#include <QtCore>
#include <QtGui>
#include <QMessageBox>
#include <QTreeWidget>
#include "listview.h"
#include <QLocale>
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
	QTreeWidgetItem *itm = new QTreeWidgetItem(this);
	
		if (strcmp(root->getFirst().c_str(), "Publications") == 0)
	{
		this->setColumnCount(2);
		this->setHeaderLabels(QStringList() << "Name" << "Total");
		
		itm->setText(0, "\t\t\t\t\t");
		itm->setExpanded(true);

	}
	else if (strcmp(root->getFirst().c_str(), "Grants and Clinical Funding") == 0)
	{
		this->setColumnCount(3);
		this->setHeaderLabels(QStringList() << "Name" << "# Total " << "$ Total");
		
		itm->setText(0, "\t\t\t\t\t");
		itm->setExpanded(true);
	}
	else if (strcmp(root->getFirst().c_str(), "Programs") == 0)
	{
		this->setColumnCount(3);
		this->setHeaderLabels(QStringList() << "Name" << "Count" << "Hours" );
		
		itm->setText(0, "\t\t\t\t\t");
		itm->setExpanded(true);
	}
	else
	{
		this->setColumnCount(2);
		this->setHeaderLabels(QStringList() << "Name" << "Total");
		
		itm->setText(0, "\t\t\t\t\t");
		itm->setExpanded(true);
	}



		populateList(root, itm);

		
}




void ListView::populateList(node* root, QTreeWidgetItem* parent)
{
	QTreeWidgetItem* itm = new QTreeWidgetItem();
	itm->setText(0, QString::fromStdString(root->getFirst()));
	if (root->getSecond()!=0)
	itm->setText(1, QString::number(root->getSecond()));

	if (root->getThird() != NULL)
	{
		itm->setText(2, QString::number((double) root->getThird()));
	}
	if (root->getFourth() != NULL)
	{
		itm->setText(2, QLocale().toCurrencyString(root->getFourth()));
	}
	
	if (root->getVisible())
		parent->addChild(itm);

	vector<node*>* children = root->getChildren();

	for (int i = 0; i < children->size(); i++)
	{
		populateList(children->at(i), itm);
	}
}
