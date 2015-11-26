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
	void plotBar(node* root);

private:
    Ui::BarPlot *ui;
	node* Node;
	string dataType;
};


#endif // BARPLOT_H
