#include "bardialog.h"
#include "ui_bardialog.h"
#include <vector>
#include <string.h>
#include <iostream>
#include <QString>
#include "statisticsTree.h"
#include "node.h"

using namespace std;

BarDialog::BarDialog(QWidget *parent)://,  node *root) :
QDialog(parent),
ui(new Ui::BarDialog)
{
	ui->setupUi(this);
	// create empty bar chart objects:
	QCPBars *regen = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
	QCPBars *nuclear = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
	QCPBars *fossil = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
	ui->customPlot->addPlottable(regen);
	ui->customPlot->addPlottable(nuclear);
	ui->customPlot->addPlottable(fossil);
	// set names and colors:
	QPen pen;
	pen.setWidthF(1.2);
	fossil->setName("Fossil fuels");
	pen.setColor(QColor(255, 131, 0));
	fossil->setPen(pen);
	fossil->setBrush(QColor(255, 131, 0, 50));
	nuclear->setName("Nuclear");
	pen.setColor(QColor(1, 92, 191));
	nuclear->setPen(pen);
	nuclear->setBrush(QColor(1, 92, 191, 50));
	regen->setName("Regenerative");
	pen.setColor(QColor(150, 222, 0));
	regen->setPen(pen);
	regen->setBrush(QColor(150, 222, 0, 70));
	// stack bars ontop of each other:
	nuclear->moveAbove(fossil);
	regen->moveAbove(nuclear);

	// prepare x axis with country labels:
	QVector<double> ticks;
	QVector<QString> labels;
	ticks << 1 << 2 << 3 << 4 << 5 << 6 << 7;
	labels << "USA" << "Japan" << "Germany" << "France" << "UK" << "Italy" << "Canada";
	ui->customPlot->xAxis->setAutoTicks(false);
	ui->customPlot->xAxis->setAutoTickLabels(false);
	ui->customPlot->xAxis->setTickVector(ticks);
	ui->customPlot->xAxis->setTickVectorLabels(labels);
	ui->customPlot->xAxis->setTickLabelRotation(60);
	ui->customPlot->xAxis->setSubTickCount(0);
	ui->customPlot->xAxis->setTickLength(0, 4);
	ui->customPlot->xAxis->grid()->setVisible(true);
	ui->customPlot->xAxis->setRange(0, 8);

	// prepare y axis:
	ui->customPlot->yAxis->setRange(0, 12.1);
	ui->customPlot->yAxis->setPadding(5); // a bit more space to the left border
	ui->customPlot->yAxis->setLabel("Power Consumption in\nKilowatts per Capita (2007)");
	ui->customPlot->yAxis->grid()->setSubGridVisible(true);
	QPen gridPen;
	gridPen.setStyle(Qt::SolidLine);
	gridPen.setColor(QColor(0, 0, 0, 25));
	ui->customPlot->yAxis->grid()->setPen(gridPen);
	gridPen.setStyle(Qt::DotLine);
	ui->customPlot->yAxis->grid()->setSubGridPen(gridPen);

	// Add data:
	QVector<double> fossilData, nuclearData, regenData;
	fossilData << 0.86*10.5 << 0.83*5.5 << 0.84*5.5 << 0.52*5.8 << 0.89*5.2 << 0.90*4.2 << 0.67*11.2;
	nuclearData << 0.08*10.5 << 0.12*5.5 << 0.12*5.5 << 0.40*5.8 << 0.09*5.2 << 0.00*4.2 << 0.07*11.2;
	regenData << 0.06*10.5 << 0.05*5.5 << 0.04*5.5 << 0.06*5.8 << 0.02*5.2 << 0.07*4.2 << 0.25*11.2;
	fossil->setData(ticks, fossilData);
	nuclear->setData(ticks, nuclearData);
	regen->setData(ticks, regenData);

	// setup legend:
	ui->customPlot->legend->setVisible(true);
	ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop | Qt::AlignHCenter);
	ui->customPlot->legend->setBrush(QColor(255, 255, 255, 200));
	QPen legendPen;
	legendPen.setColor(QColor(130, 130, 130, 200));
	ui->customPlot->legend->setBorderPen(legendPen);
	QFont legendFont = font();
	legendFont.setPointSize(10);
	ui->customPlot->legend->setFont(legendFont);
	ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
	/*
	Node = root; // Data is given in a tree with the root node being the type of .csv

	// ###
	// THIS WONT WORK FOR GRANT PROFS ... I'LL FIGURE IT OUT DW DW. (HENRY)
	// ###


	// The first element of the root node will distinguish what type of data it is
	// Ie.: "Publications","Programs","Presentations", "Grants and Clinical Funding"
	string dataType = Node->getFirst();

	// Get the types
	// Note the type is not always going to be the within the second layer of the tree
	// It will be possible to pass in a different node (say a publication type node) when implemented
	vector<node*>* types;
	if ((dataType == "Publications") || (dataType == "Programs") || (dataType=="Presentations") || (dataType== "Grants and Clinical Funding")){
		for (int i = 0; i < Node->getChildren()->size(); i++){
			types->push_back(Node->getChildren()->at(i));
		}
	}
	else {
		types->push_back(Node);
	}
	// I think the above should work???

	// Grab Data and prepare x axis with professor Name labels:
	QVector<double> ticks;
	QVector<QString> profNames;

	// Search for the leave nodes to get the profNames
	while (Node->getChildren()->at(0)->getChildren()->size() > 0){
		Node = Node->getChildren()->at(0);
	}
	// append the profNames to a QVector so that they can be displayed later
	for (int i = 1; i <= Node->getChildren()->size(); i++){
		ticks.append(i);
		profNames.append(QString::fromStdString(Node->getChildren()->at(0)->getFirst()));
	}

	// create a vector of bar plots. This way you can iteratively stack them ontop of one another
	vector<QCPBars*> bars;
	// create a new plottable area for each type of publication
	for (int i = 0; i < types->size(); i++)
	{
		QVector<double> count;
		for (int j = 0; j < types->at(i)->getChildren()->size(); j++)
		{
			count.push_back(types->at(i)->getChildren()->at(j)->getSecond());
		}
		QCPBars *temp = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
		temp->setName(QString::fromStdString(types->at(i)->getFirst()));
		temp->setData(ticks, count);
		bars.push_back(temp);
		ui->customPlot->addPlottable(temp);
	}
	// stack bars ontop of each other:
	// loop through each of the QCPBar objects in the list bars
	if (bars.size() > 1){
		
		for (int i = 0; i < (bars.size() - 1); i++)
		{
			bars[i+1]->moveAbove(bars[i]);
		}
	}
	// set the colors
	QPen pen;
	pen.setWidthF(1.2);
	int hue1 = 0;
	int hue2 = 210;
	int hue3 = 255;
	for (int i = 0; i < bars.size(); i++)
	{
		pen.setColor(QColor(hue1 % 255, hue2 % 255, hue3 % 255));
		bars[i]->setPen(pen);
		bars[i]->setBrush((QColor(hue1 % 255, hue2 % 255, hue3 % 255, 75)));
		hue1 += 17;
		//hue2 += 97;
		//hue3 += 79;
	}

	ui->customPlot->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->customPlot, QString::fromStdString(dataType)));
	// prepare x axis:
    ui->customPlot->xAxis->setAutoTicks(true);
    ui->customPlot->xAxis->setAutoTickLabels(false);
    ui->customPlot->xAxis->setTickVector(ticks);
    ui->customPlot->xAxis->setTickVectorLabels(profNames);
    ui->customPlot->xAxis->setTickLabelRotation(60);
    //ui->customPlot->xAxis->setSubTickCount(0);
    ui->customPlot->xAxis->setTickLength(0, 3);
    ui->customPlot->xAxis->grid()->setVisible(true);
    ui->customPlot->xAxis->setRange(0, 10);

    // prepare y axis:
    ui->customPlot->yAxis->setRange(0, 20);
    ui->customPlot->yAxis->setPadding(5); // a bit more space to the left border
    ui->customPlot->yAxis->setLabel("Count");
    ui->customPlot->yAxis->grid()->setSubGridVisible(true);
    QPen gridPen;
    gridPen.setStyle(Qt::SolidLine);
    gridPen.setColor(QColor(0, 0, 0, 25));
    ui->customPlot->yAxis->grid()->setPen(gridPen);
    gridPen.setStyle(Qt::DotLine);
    ui->customPlot->yAxis->grid()->setSubGridPen(gridPen);

    // setup legend:
    ui->customPlot->legend->setVisible(true);
    ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignRight);
    ui->customPlot->legend->setBrush(QColor(255, 255, 255, 200));
    QPen legendPen;
    legendPen.setColor(QColor(130, 130, 130, 200));
    ui->customPlot->legend->setBorderPen(legendPen);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    ui->customPlot->legend->setFont(legendFont);
    //ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
	*/
}

BarDialog::~BarDialog()
{
    delete ui;
}
