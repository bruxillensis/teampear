#include "bardialog.h"
#include "ui_bardialog.h"
#include <vector>
#include <string.h>
#include <iostream>
#include <QString>
#include "statisticsTree.h"
#include "node.h"

using namespace std;

BarDialog::BarDialog(QWidget *parent,  node* rootNode) :
QDialog(parent),
ui(new Ui::BarDialog)
{
	ui->setupUi(this);
	treeData = rootNode; // Data is given in a tree with the root node being the type of .csv

	// The first element of the root node will distinguish what type of data it is
	// Either: "Publications","Programs","Presentations", OR NULL(empty) 
	// empty == granProfessor; which branches into two other nodes "Grants" and "Clinical Funding" ... and so forth
	string dataType = treeData->getFirst(); 

	// I'm just going to try and figure out publication.csv for now
	// Grab Data and prepare x axis with professor Name labels:
	QVector<double> ticks;
	QVector<QString> profNames;

	// get the child nodes of the root node to get the publication types
	vector<node*>* pubTypes = treeData->getChildren();

	// Assuming each pubType has the same amount and order of child nodes (i.e. for each existing prof)
	for (int i = 1; i <= pubTypes->at(0)->getChildren()->size(); i++)
	{
		ticks.append(i);
		profNames.append(QString::fromStdString(pubTypes->at(0)->getChildren()->at(i)->getFirst()));
	}
		
	// create a vector of bar plots. This way you can iteratively stack them ontop of one another
	vector<QCPBars*> bars;
	// create a new plottable area for each type of publication
	for (int i = 0; i < pubTypes->size(); i++)
	{
		QVector<double> pubCount;
		for (int j = 0; j < pubTypes->at(i)->getChildren()->size(); j++)
		{
			pubCount.push_back(pubTypes->at(i)->getChildren()->at(j)->getSecond());
		}
		QCPBars *temp = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
		temp->setName(QString::fromStdString(pubTypes->at(i)->getFirst()));
		temp->setData(ticks, pubCount);
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

	// prepare x axis:
    ui->customPlot->xAxis->setAutoTicks(false);
    ui->customPlot->xAxis->setAutoTickLabels(false);
    ui->customPlot->xAxis->setTickVector(ticks);
    ui->customPlot->xAxis->setTickVectorLabels(profNames);
    ui->customPlot->xAxis->setTickLabelRotation(60);
    ui->customPlot->xAxis->setSubTickCount(0);
    ui->customPlot->xAxis->setTickLength(0, 3);
    ui->customPlot->xAxis->grid()->setVisible(true);
    ui->customPlot->xAxis->setRange(0, 10);

    // prepare y axis:
    ui->customPlot->yAxis->setRange(0, 20);
    ui->customPlot->yAxis->setPadding(5); // a bit more space to the left border
    ui->customPlot->yAxis->setLabel("Publication Count");
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
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}

BarDialog::~BarDialog()
{
    delete ui;
}
