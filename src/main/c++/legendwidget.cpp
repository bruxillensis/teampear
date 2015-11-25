#include <QTableView>
#include <QStandardItemModel>
#include <QColor>
#include <vector>
#include <string.h>
#include "legendwidget.h"
#include "node.h"

#define HUE_MAX		359			//maximum HSV value
#define C_SAT		210			//Pie slice saturation
#define C_VAL		255			//Pie slice lightness

using namespace std;

LegendWidget::LegendWidget(QWidget *parent) :QTableView(parent)
{
}

void LegendWidget::drawLegend(node* root)
{
	//resize legend
	this->setMinimumWidth(175);
	//create model for holding data
	QStandardItemModel *model = new QStandardItemModel(100, 2, this);
	//set headers of table
	model->setHeaderData(1, Qt::Horizontal, tr(root->getFirst().c_str()));
	model->setHeaderData(0, Qt::Horizontal, tr(" "));

	vector<node*> *children = root->getChildren();

	//color increment
	int c_inc = HUE_MAX / children->size();

	int i, rows = 0, current, hue = 0;

	QColor color;

	for (i = 0; i < children->size(); i++){

		current = children->at(i)->getSecond();
		if (current > 0){
			color.setHsv(hue, C_SAT, C_VAL);
			model->setItem(rows, 1, new QStandardItem(QString::fromStdString(children->at(i)->getFirst())));
			model->setItem(rows, 0, new QStandardItem(QString::fromStdString("")));
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