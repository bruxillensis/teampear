#include <vector>
#include <string.h>
#include <iostream>
#include <QString>
#include <algorithm> 
#include <limits>
#include "barplot.h"
#include "statisticsTree.h"
#include "node.h"


#define BAR_SAT		210		// colour saturation
#define BAR_VAL		230		// colour lightness
#define BAR_ALPHA	110 	// colour transparency
#define HUE_MAX		359
#define COUNT_MAX	20		// number of stacked layers

using namespace std;
BarPlot::BarPlot(QWidget *parent) : QCustomPlot(parent)
{
}

int BarPlot::plotBar(node *root)
{	
	Node = root; // Data is passed through as a node

	string dataType = Node->getFirst();

	bool grantType = false;
	if (Node->getFourth() > 0.0)
		grantType = true;

	// Get the types
	// Note the type is not always going to be the within the children of the node (depending on what node is passed)
	// It will be possible to pass in a different node (say a publication type node) when implemented
	vector<node*> types;
	if (Node->getParent() == NULL){
		vector<node*>* temptypes = Node->getChildren();
		for (int i = 0; i < temptypes->size(); i++){
			if (temptypes->at(i)->getSecond() > 0)
				types.push_back(temptypes->at(i));
		}
	}
	else{	types.push_back(Node);	}

	// Grab Data and prepare x axis with (professor Name) labels:
	QVector<QString> labels;
	// Search for the prof names if not grant type
	if (!(grantType)){
		for (int i = 0; i < types.size(); i++){
			for (int j = 0; j < types.at(i)->getChildren()->size(); j++){
				QString name = QString::fromStdString(types.at(i)->getChildren()->at(j)->getFirst());
				if (!(labels.contains(name)))
					labels.push_back(name);
			}
		}
	}
	// if grant type, display the types only
	else{
		for (int i = 0; i < Node->getChildren()->size(); i++)
			labels.push_back(QString::fromStdString(Node->getChildren()->at(i)->getFirst()));
	}

	// stacked bar chart can get cluttered, ensure no more than 30 different types
	// determine which types to push into an "Others" group
	vector<int> othersNdx;
	if (types.size() > COUNT_MAX){
		vector<double> typeSumCounts;
		for (int i = 0; i < types.size(); i++){
			if (grantType)
				typeSumCounts.push_back(types.at(i)->getFourth());
			else
				typeSumCounts.push_back(types.at(i)->getSecond());
		}
		while (types.size() - othersNdx.size() > COUNT_MAX){
			othersNdx.push_back(min_element(typeSumCounts.begin(), typeSumCounts.end()) - typeSumCounts.begin());
			typeSumCounts.at(min_element(typeSumCounts.begin(), typeSumCounts.end()) - typeSumCounts.begin()) = std::numeric_limits<double>::infinity();
		}
	}

	QVector<double> ticks;
	for (int i = 1; i <= labels.size(); i++)
		ticks.push_back(i);

	vector<QCPBars*> bars;
	QVector<double> othersCount(labels.size());
	double *othersData = othersCount.data();
	// create a new plottable area for each type, group everything within the "Others" group together
	for (int i = 0; i < types.size(); i++)
	{
		QVector<double> count(labels.size());
		double *data = count.data();
		// Note: not all types have same number of children (profs)
		// this would affect the labels (prof names)
		for (int j = 0; j < types.at(i)->getChildren()->size(); j++){
			int pos = labels.indexOf(QString::fromStdString(types.at(i)->getChildren()->at(j)->getFirst()));
			if (grantType)
				data[pos] = types.at(i)->getChildren()->at(j)->getFourth();
			else
				data[pos]= types.at(i)->getChildren()->at(j)->getSecond();
		}
		QCPBars *temp = new QCPBars(this->xAxis, this->yAxis);

		if (std::find(othersNdx.begin(), othersNdx.end(), i) != othersNdx.end()){
			for (int j = 0; j < labels.size(); j++)
				othersData[j] += count[j];
		}
		else{
			temp->setName(QString::fromStdString(types.at(i)->getFirst()));
			temp->setData(ticks, count);
			bars.push_back(temp);
			this->addPlottable(temp);
		}
	}
	// Graph "Others" only if there's something in it
	if (std::find(othersCount.begin(), othersCount.end(), (!0)) != othersCount.end()){
		QCPBars *temp = new QCPBars(this->xAxis, this->yAxis);
		temp->setName("Others");
		temp->setData(ticks, othersCount);
		bars.push_back(temp);
		this->addPlottable(temp);
	}
	// stack bars ontop of each other:
	// loop through each of the QCPBar objects in the list bars
	if (bars.size() > 1){
		for (int i = 0; i < (bars.size() - 1); i++)
			bars[i+1]->moveAbove(bars[i]);
	}
	// set the colors
	QPen pen;
	pen.setWidthF(1.2);
	int C_HUE = 0;
	for (int i = 0; i < bars.size(); i++)
	{
		QColor color_brush, color_pen;
		color_brush.setHsv(C_HUE, BAR_SAT, BAR_VAL);
		color_brush.setAlpha(BAR_ALPHA);
		color_pen.setHsv(C_HUE, BAR_SAT+30, BAR_VAL+10);
		color_pen.setAlpha(255);
		pen.setColor(color_pen);
		bars[i]->setPen(pen);
		bars[i]->setBrush(color_brush);
		C_HUE += HUE_MAX/bars.size();
	}

	//this->plotLayout()->addElement(0, 0, new QCPPlotTitle(this, QString::fromStdString(dataType)));
	// prepare x axis:
    this->xAxis->setAutoTicks(false);
    this->xAxis->setAutoTickLabels(false);
    this->xAxis->setTickVector(ticks);
    this->xAxis->setTickVectorLabels(labels);
    this->xAxis->setTickLabelRotation(60);
    this->xAxis->setSubTickCount(0);
    this->xAxis->setTickLength(0, 3);
    this->xAxis->grid()->setVisible(true);
	

    // prepare y axis:
	this->yAxis->setTickStep(5);
    this->yAxis->setPadding(5); // a bit more space to the left border
	if (grantType)
		this->yAxis->setLabel("Amount");
	else
		this->yAxis->setLabel("Count");
    this->yAxis->grid()->setSubGridVisible(true);
    QPen gridPen;
    gridPen.setStyle(Qt::SolidLine);
    gridPen.setColor(QColor(0, 0, 0, 25));
    this->yAxis->grid()->setPen(gridPen);
    gridPen.setStyle(Qt::DotLine);
    this->yAxis->grid()->setSubGridPen(gridPen);
	this->yAxis->scaleRange(1.3, this->yAxis->range().center());

	this->rescaleAxes(true);
	this->xAxis->setRange(0.5, 10.5);

    // setup legend:
	QCPLayoutGrid *subLayout = new QCPLayoutGrid;
	QCPLayoutElement *dummyElement = new QCPLayoutElement;

	this->plotLayout()->addElement(0, 1, subLayout); // add sub-layout in the cell to the right of the main axis rect
	subLayout->addElement(0, 0, this->legend); // add legend
	subLayout->addElement(1, 0, dummyElement); // add dummy element below legend
	subLayout->setRowStretchFactor(0, 0.01); // make legend cell (in row 0) take up as little vertical space as possible
	this->plotLayout()->setColumnStretchFactor(1, 0.01); // make the legend cell and dummy element column as small as possible

    this->legend->setVisible(true);
    this->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignRight);
    this->legend->setBrush(QColor(255, 255, 255, 200));
    QPen legendPen;
    legendPen.setColor(QColor(130, 130, 130, 200));
    this->legend->setBorderPen(legendPen);
    QFont legendFont = font();
    legendFont.setPointSize(8);
    this->legend->setFont(legendFont);
	this->legend->setSelectableParts(QCPLegend::spItems); // legend box shall not be selectable, only legend items
	
	this->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables | QCP::iSelectLegend);

	if (std::find(othersCount.begin(), othersCount.end(), (!0)) != othersCount.end()){
		return 1;
	}
	else
		return 0;
}
