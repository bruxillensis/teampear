#include "bardialog.h"
#include "ui_bardialog.h"
#include <vector>
#include <string.h>
#include <iostream>
#include <QString>

using namespace std;
BarDialog::BarDialog(QWidget *parent, vector<pair<string, vector<pair<string, int> > > > inData) :
QDialog(parent),
ui(new Ui::BarDialog)
{
	ui->setupUi(this);
	data1 = inData;
	// Grab Data and prepare x axis with professor Name labels:
	QVector<double> ticks;
	QVector<QString> profNames;
	// Create vectors to hold the counts of each type
	QVector<double> bookChaptersData, booksData, booksEditedData, caseReportsData, clinicalCareGuidesData, commentariesData, \
		conferencesData, editorialsData, invitedArticlesData, journalArticlesData, lettersData, magazinesData, manualsData, \
		monographsData, multimediaData, newletterArticlesData, newspaperArticlesData, abstractsData, studentPubsData, \
		webVidsData, workingPapersData, othersData;

	// Create a vector to store the type names
	const char* args[] = { "Book Chapters", "Books", "Books Edited", "Case Reports", "Clinical Case Guidelines", \
		"Commentaries", "Conference Proceedings", "Editorials", "Invited Articles", "Journal Article", \
		"Letters to Editor", "Magazine Entries", "Manuals", "Monographs", "Multimedia", "Newsletter Articles", \
		"Newspaper Articles", "Published Abstracts", "Supervised Student Publications", "Websites / Videos", \
		"Working Papers", "Others" };
	vector<string> typeString(args, args + sizeof(args) / sizeof(args[0]));

	int size = data1.size();
	while (data1.size() > 0)
	{
		pair<string, vector<pair<string, int>>> pair1 = data1.back(); // everything within a type
		data1.pop_back(); // remove that type from the data
		vector<pair<string, int>> vector2 = pair1.second; // hold the vectors of profs for that type
		while (vector2.size() > 0) // Iterate through the profs
		{

			pair<string, int> pair2 = vector2.back(); // hold the prof name
			if (!(profNames.contains(QString::fromStdString(pair2.first))))// check if its already in profname list
			{
				profNames.append(QString::fromStdString(pair2.first));
			}
			int Ndx = profNames.indexOf(QString::fromStdString(pair2.first));
			// resize all of the vectors of data counters, respective to the number of profs
			// that way you can access it through the same index


			if (pair1.first == typeString[0])		{ bookChaptersData.resize(profNames.size()); bookChaptersData.insert(Ndx, pair2.second); }
			else if (pair1.first == typeString[1])	{ booksData.resize(profNames.size()); booksData.insert(Ndx, pair2.second); }
			else if (pair1.first == typeString[2])	{ booksEditedData.resize(profNames.size()); booksEditedData.insert(Ndx, pair2.second); }
			else if (pair1.first == typeString[3])	{ caseReportsData.resize(profNames.size()); caseReportsData.insert(Ndx, pair2.second); }
			else if (pair1.first == typeString[4])	{ clinicalCareGuidesData.resize(profNames.size()); clinicalCareGuidesData.insert(Ndx, pair2.second); }
			else if (pair1.first == typeString[5])	{ commentariesData.resize(profNames.size()); commentariesData.insert(Ndx, pair2.second); }
			else if (pair1.first == typeString[6])	{ conferencesData.resize(profNames.size()); conferencesData.insert(Ndx, pair2.second); }
			else if (pair1.first == typeString[7])	{ editorialsData.resize(profNames.size()); editorialsData.insert(Ndx, pair2.second); }
			else if (pair1.first == typeString[8])	{ invitedArticlesData.resize(profNames.size()); invitedArticlesData.insert(Ndx, pair2.second); }
			else if (pair1.first == typeString[9])	{ journalArticlesData.resize(profNames.size()); journalArticlesData.insert(Ndx, pair2.second); }
			else if (pair1.first == typeString[10])	{ lettersData.resize(profNames.size()); lettersData.insert(Ndx, pair2.second); }
			else if (pair1.first == typeString[11])	{ magazinesData.resize(profNames.size()); magazinesData.insert(Ndx, pair2.second); }
			else if (pair1.first == typeString[12])	{ manualsData.resize(profNames.size()); manualsData.insert(Ndx, pair2.second); }
			else if (pair1.first == typeString[13])	{ monographsData.resize(profNames.size()); monographsData.insert(Ndx, pair2.second); }
			else if (pair1.first == typeString[14])	{ multimediaData.resize(profNames.size()); multimediaData.insert(Ndx, pair2.second); }
			else if (pair1.first == typeString[15])	{ newletterArticlesData.resize(profNames.size()); newletterArticlesData.insert(Ndx, pair2.second); }
			else if (pair1.first == typeString[16])	{ newspaperArticlesData.resize(profNames.size()); newspaperArticlesData.insert(Ndx, pair2.second); }
			else if (pair1.first == typeString[17])	{ abstractsData.resize(profNames.size()); abstractsData.insert(Ndx, pair2.second); }
			else if (pair1.first == typeString[18])	{ studentPubsData.resize(profNames.size()); studentPubsData.insert(Ndx, pair2.second); }
			else if (pair1.first == typeString[19])	{ webVidsData.resize(profNames.size()); webVidsData.insert(Ndx, pair2.second); }
			else if (pair1.first == typeString[20])	{ workingPapersData.resize(profNames.size()); workingPapersData.insert(Ndx, pair2.second); }
			else if (pair1.first == typeString[21])	{ othersData.resize(profNames.size()); othersData.insert(Ndx, pair2.second); }
			vector2.pop_back(); // remove prof

		}
	}
	for (int i = 1; i <= profNames.count(); i++)
	{
		ticks.append(i);
	}

	// create empty bar chart objects:
	vector<QCPBars*> bars;
	// Create a vector to hold the vectors of Data
	vector<QVector<double>> typeData = { bookChaptersData, booksData, booksEditedData, caseReportsData, clinicalCareGuidesData, commentariesData, \
		conferencesData, editorialsData, invitedArticlesData, journalArticlesData, lettersData, magazinesData, manualsData, \
		monographsData, multimediaData, newletterArticlesData, newspaperArticlesData, abstractsData, studentPubsData, \
		webVidsData, workingPapersData, othersData };
	
	// loop through each of the data types
	for (int i = 0; i < typeData.size(); i++)
	{
		// if there is an instance of a count that is not 0, create a plot for it with the respective data 
		// and the respective data type string name
		if (typeData[i].count(0) != typeData[i].size())
		{
			QCPBars *temp = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
			temp->setName(QString::fromStdString(typeString[i]));
			temp->setData(ticks, typeData[i]);
			bars.push_back(temp);
			ui->customPlot->addPlottable(temp);
		}
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
	int hue2 = 100;
	int hue3 = 200;
	for (int i = 0; i < bars.size(); i++)
	{
		pen.setColor(QColor(hue1 % 255, hue2 % 255, hue3 % 255));
		bars[i]->setPen(pen);
		bars[i]->setBrush((QColor(hue1 % 255, hue2 % 255, hue3 % 255, 50)));
		hue1 += 17;
		hue2 += 97;
		hue3 += 79;
	}

    ui->customPlot->xAxis->setAutoTicks(false);
    ui->customPlot->xAxis->setAutoTickLabels(false);
    ui->customPlot->xAxis->setTickVector(ticks);
    ui->customPlot->xAxis->setTickVectorLabels(profNames);
    ui->customPlot->xAxis->setTickLabelRotation(60);
    ui->customPlot->xAxis->setSubTickCount(0);
    ui->customPlot->xAxis->setTickLength(0, 4);
    ui->customPlot->xAxis->grid()->setVisible(true);
    ui->customPlot->xAxis->setRange(0, 8);

    // prepare y axis:
    ui->customPlot->yAxis->setRange(0, 12.1);
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
