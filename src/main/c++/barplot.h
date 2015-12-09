#ifndef BARPLOT_H
#define BARPLOT_H

#include "qcustomplot.h"
#include "statisticsTree.h"
#include "node.h"


using namespace std;
	
namespace Ui {
class BarPlot;
}


class BarPlot : public QCustomPlot
{
    Q_OBJECT

public:
	explicit BarPlot(QWidget *parent);
	int plotBar(node* root);
	int plotOther();
	int plotGrantTeach();

private:
    Ui::BarPlot *ui;
	node* Node;
	string dataType;
};


#endif // BARPLOT_H
