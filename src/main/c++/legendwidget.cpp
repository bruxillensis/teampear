#include <QTableView>
#include <QStandardItemModel>
#include <QColor>
#include <vector>
#include <string.h>
#include "legendwidget.h"
#include "node.h"

#define HUE_MAX		359			//maximum HSV value
#define C_SAT		175			//Pie slice saturation
#define C_VAL		240			//Pie slice lightness
#define MAX_NODES	20			//Maximum amount of nodes to graph

using namespace std;

LegendWidget::LegendWidget(QWidget *parent) :QTableView(parent)
{
}

void LegendWidget::drawLegend(node* root)
{
	//resize legend
	this->setMinimumWidth(270);
	//create model for holding data
	QStandardItemModel *model = new QStandardItemModel(100, 2, this);
	//set headers of table
	model->setHeaderData(1, Qt::Horizontal, tr(root->getFirst().c_str()));

	bool money = false;

	if (root->getFourth())
		money = true;
	if (money)
		model->setHeaderData(0, Qt::Horizontal, tr("$"));
	else
		model->setHeaderData(0, Qt::Horizontal, tr("#"));

	vector<node*> *children = root->getChildren();
	vector<node*> *top_nodes = new vector<node*>();


	int i, j, rows = 0, hue = 0, c_inc;
	float current, other;

	QColor color;

	for (i = 0; i < children->size(); i++){
		if (top_nodes->size() >= MAX_NODES)
		{
			for (j = 0; j < top_nodes->size(); j++)
			{
				if ((children->at(i)->getSecond()>top_nodes->at(j)->getSecond() && !money)
					|| (children->at(i)->getFourth()>top_nodes->at(j)->getFourth() && money))
				{
					if (money)
						other += top_nodes->at(j)->getFourth();
					else
						other += top_nodes->at(j)->getSecond();

					top_nodes->at(j) = children->at(i);

				}
			}
		}
		else
		{
			top_nodes->push_back(children->at(i));
		}
	}

	//color increment
	if (top_nodes->size() < 20)
		c_inc = HUE_MAX / top_nodes->size();
	else
		c_inc = HUE_MAX / MAX_NODES + 1;

	for (i = 0; i < top_nodes->size(); i++){
		if (money)
			current = top_nodes->at(i)->getFourth();
		else
			current = top_nodes->at(i)->getSecond();

		if (current > 0){
			color.setHsv(hue, C_SAT, C_VAL);
			model->setItem(rows, 1, new QStandardItem(QString::fromStdString(top_nodes->at(i)->getFirst())));

			if (money)
				model->setItem(rows, 0, new QStandardItem(QString::fromStdString(to_string(top_nodes->at(i)->getFourth()))));
			else
				model->setItem(rows, 0, new QStandardItem(QString::fromStdString(to_string(top_nodes->at(i)->getSecond()))));

			model->item(rows, 0)->setData(QBrush(color), Qt::BackgroundRole);
			rows++;

			hue += c_inc;
		}
	}

	model->setRowCount(rows);

	this->setModel(model);
	this->setColumnWidth(0, 30);
	this->resizeColumnToContents(1);
	this->setEditTriggers(QAbstractItemView::NoEditTriggers);

}