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
    data = inData;
    // Grab Data and prepare x axis with professor Name labels:
    QVector<double> ticks;
    QVector<QString> profNames;
	QVector<double> bookChaptersData, booksData, booksEditedData, caseReportsData, clinicalCareGuidesData, commentariesData, \
		conferencesData, editorialsData, invitedArticlesData, journalArticlesData, lettersData, magazinesData, manualsData, \
		monographsData, multimediaData, newletterArticlesData, newspaperArticlesData, abstractsData, studentPubsData, \
		webVidsData, workingPapersData, othersData;
    int size = data.size();
	while (data.size()>0) 
    {
		pair<string, vector<pair<string, int>>> pair1 = data.back(); // everything within a type
        data.pop_back(); // remove that type from the data
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
			
			if (pair1.first == "Book Chapters")							{ bookChaptersData.resize(profNames.size()); bookChaptersData.insert(Ndx, pair2.second); }
			else if (pair1.first == "Books")							{ booksData.resize(profNames.size()); booksData.insert(Ndx, pair2.second); }
			else if (pair1.first == "Books Edited")						{ booksEditedData.resize(profNames.size()); booksEditedData.insert(Ndx, pair2.second); }
			else if (pair1.first == "Case Reports")						{ caseReportsData.resize(profNames.size()); caseReportsData.insert(Ndx, pair2.second); }
			else if (pair1.first == "Clinical Case Guidelines")			{ clinicalCareGuidesData.resize(profNames.size()); clinicalCareGuidesData.insert(Ndx, pair2.second); }
			else if (pair1.first == "Commentaries")						{ commentariesData.resize(profNames.size()); commentariesData.insert(Ndx, pair2.second); }
			else if (pair1.first == "Conference Proceedings")			{ conferencesData.resize(profNames.size()); conferencesData.insert(Ndx, pair2.second); }
			else if (pair1.first == "Editorials")						{ editorialsData.resize(profNames.size()); editorialsData.insert(Ndx, pair2.second); }
			else if (pair1.first == "Invited Articles")					{ invitedArticlesData.resize(profNames.size()); invitedArticlesData.insert(Ndx, pair2.second); }
			else if (pair1.first == "Journal Article")					{ journalArticlesData.resize(profNames.size()); journalArticlesData.insert(Ndx, pair2.second); }
			else if (pair1.first == "Letters to Editor")				{ lettersData.resize(profNames.size()); lettersData.insert(Ndx, pair2.second); }
			else if (pair1.first == "Magazine Entries")					{ magazinesData.resize(profNames.size()); magazinesData.insert(Ndx, pair2.second); }
			else if (pair1.first == "Manuals")							{ manualsData.resize(profNames.size()); manualsData.insert(Ndx, pair2.second); }
			else if (pair1.first == "Monographs")						{ monographsData.resize(profNames.size()); monographsData.insert(Ndx, pair2.second); }
			else if (pair1.first == "Multimedia")						{ multimediaData.resize(profNames.size()); multimediaData.insert(Ndx, pair2.second); }
			else if (pair1.first == "Newsletter Articles")				{ newletterArticlesData.resize(profNames.size()); newletterArticlesData.insert(Ndx, pair2.second); }
			else if (pair1.first == "Newspaper Articles")				{ newspaperArticlesData.resize(profNames.size()); newspaperArticlesData.insert(Ndx, pair2.second); }
			else if (pair1.first == "Published Abstracts")				{ abstractsData.resize(profNames.size()); abstractsData.insert(Ndx, pair2.second); }
			else if (pair1.first == "Supervised Student Publications")	{ studentPubsData.resize(profNames.size()); studentPubsData.insert(Ndx, pair2.second); }
			else if (pair1.first == "Websites / Videos")				{ webVidsData.resize(profNames.size()); webVidsData.insert(Ndx, pair2.second); }
			else if (pair1.first == "Working Papers")					{ workingPapersData.resize(profNames.size()); workingPapersData.insert(Ndx, pair2.second); }
			else if (pair1.first == "Others")							{ othersData.resize(profNames.size()); othersData.insert(Ndx, pair2.second); }
			vector2.pop_back(); // remove prof
            
        }
    }
    for (int i=1; i<=profNames.count(); i++)
    {
        ticks.append(i);
    }

	// create empty bar chart objects:
	// This is a mess right now... I don't know how to iterate through a variable names
	vector<QCPBars*> bars;
	if (!(bookChaptersData.empty()))		{ 
		QCPBars *bookChapters = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
		bookChapters->setName("Book Chapters");
		bookChapters->setData(ticks, bookChaptersData);
		bars.push_back(bookChapters);
		ui->customPlot->addPlottable(bookChapters);
	}
	if (!(booksData.empty()))				{ 
		QCPBars *books = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
		books->setName("Books");
		books->setData(ticks, booksData);
		bars.push_back(books);
		ui->customPlot->addPlottable(books);
	}
	if (!(booksEditedData.empty()))			{ 
		QCPBars *booksEdited = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
		booksEdited->setName("Books Edited");
		booksEdited->setData(ticks, booksEditedData);
		bars.push_back(booksEdited);
		ui->customPlot->addPlottable(booksEdited);
	}
	if (!(caseReportsData.empty()))			{ 
		QCPBars *caseReports = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
		caseReports->setName("Case Reports");
		caseReports->setData(ticks, caseReportsData);
		bars.push_back(caseReports);
		ui->customPlot->addPlottable(caseReports);
	}
	if (!(clinicalCareGuidesData.empty()))	{ 
		QCPBars *clinicalCareGuides = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
		clinicalCareGuides->setName("Clinical Case Guidelines");
		clinicalCareGuides->setData(ticks, clinicalCareGuidesData);
		bars.push_back(clinicalCareGuides);
		ui->customPlot->addPlottable(clinicalCareGuides);
	}
	if (!(commentariesData.empty()))		{ 
		QCPBars *commentaries = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
		commentaries->setName("Commentaries");
		commentaries->setData(ticks, commentariesData);
		bars.push_back(commentaries);
		ui->customPlot->addPlottable(commentaries);
	}
	if (!(conferencesData.empty()))			{ 
		QCPBars *conferences = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
		conferences->setName("Conference Proceedings");
		conferences->setData(ticks, conferencesData);
		bars.push_back(conferences);
		ui->customPlot->addPlottable(conferences);
	}
	if (!(editorialsData.empty()))			{ 
		QCPBars *editorials = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
		editorials->setName("Editorials");
		editorials->setData(ticks, editorialsData);
		bars.push_back(editorials);
		ui->customPlot->addPlottable(editorials);
	}
	if (!(invitedArticlesData.empty()))		{ 
		QCPBars *invitedArticles = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
		invitedArticles->setName("Invited Articles");
		invitedArticles->setData(ticks, invitedArticlesData);
		bars.push_back(invitedArticles);
		ui->customPlot->addPlottable(invitedArticles);
	}
	if (!(journalArticlesData.empty()))		{ 
		QCPBars *journalArticles = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
		journalArticles->setName("Journal Articles");
		journalArticles->setData(ticks, journalArticlesData);
		bars.push_back(journalArticles);
		ui->customPlot->addPlottable(journalArticles);
	}
	if (!(lettersData.empty()))				{ 
		QCPBars *letters = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
		letters->setName("Letters to Editor");
		letters->setData(ticks, lettersData);
		bars.push_back(letters);
		ui->customPlot->addPlottable(letters);
	}
	if (!(magazinesData.empty()))			{ 
		QCPBars *magazines = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
		magazines->setName("Magazine Entries");
		magazines->setData(ticks, magazinesData);
		bars.push_back(magazines);
		ui->customPlot->addPlottable(magazines);
	}
	if (!(manualsData.empty()))				{ 
		QCPBars *manuals = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
		manuals->setName("Manuals");
		manuals->setData(ticks, manualsData);
		bars.push_back(manuals);
		ui->customPlot->addPlottable(manuals);
	}
	if (!(monographsData.empty()))			{ 
		QCPBars *monographs = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
		monographs->setName("Monographs");
		monographs->setData(ticks, monographsData);
		bars.push_back(monographs);
		ui->customPlot->addPlottable(monographs);
	}
	if (!(multimediaData.empty()))			{ 
		QCPBars *multimedia = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
		multimedia->setName("Multimedia");
		multimedia->setData(ticks, multimediaData);
		bars.push_back(multimedia);
		ui->customPlot->addPlottable(multimedia);
	}
	if (!(newletterArticlesData.empty()))	{ 
		QCPBars *newletterArticles = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
		newletterArticles->setName("Newsletter Articles");
		newletterArticles->setData(ticks, newletterArticlesData);
		bars.push_back(newletterArticles);
		ui->customPlot->addPlottable(newletterArticles);
	}
	if (!(newspaperArticlesData.empty()))	{ 
		QCPBars *newspaperArticles = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
		newspaperArticles->setName("Newspaper Articles");
		newspaperArticles->setData(ticks, newspaperArticlesData);
		bars.push_back(newspaperArticles);
		ui->customPlot->addPlottable(newspaperArticles);
	}
	if (!(abstractsData.empty()))			{ 
		QCPBars *abstracts = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
		abstracts->setName("Published Abstracts");
		abstracts->setData(ticks, abstractsData);
		bars.push_back(abstracts);
		ui->customPlot->addPlottable(abstracts);
	}
	if (!(studentPubsData.empty()))			{ 
		QCPBars *studentPubs = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
		studentPubs->setName("Supervised Student Publications");
		studentPubs->setData(ticks, studentPubsData);
		bars.push_back(studentPubs);
		ui->customPlot->addPlottable(studentPubs);
	}
	if (!(webVidsData.empty()))				{ 
		QCPBars *webVids = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
		webVids->setName("Websites / Videos");
		webVids->setData(ticks, webVidsData);
		bars.push_back(webVids);
		ui->customPlot->addPlottable(webVids);
	}
	if (!(workingPapersData.empty()))		{ 
		QCPBars *workingPapers = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
		workingPapers->setName("Working Papers");
		workingPapers->setData(ticks, workingPapersData);
		bars.push_back(workingPapers);
		ui->customPlot->addPlottable(workingPapers);
	}
	if (!(othersData.empty()))				{ 
		QCPBars *others = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
		others->setName("Others");
		others->setData(ticks, othersData);
		bars.push_back(others);
		ui->customPlot->addPlottable(others);
	
	}


	// stack bars ontop of each other:
	// loop through each of the QCPBar objects in the list bars
	if (bars.size() > 1){
		for (int i = 0; i < (bars.size() - 1); i++)
		{
			(bars[i])->moveAbove(bars[i + 1]);
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
