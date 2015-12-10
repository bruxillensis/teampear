#ifndef LEGENDWIDGET_H
#define LEGENDWIDGET_H

#include <QTableView>
#include "node.h"

class LegendWidget : public QTableView
{
	Q_OBJECT
public:
	explicit LegendWidget(QWidget *parent = 0);
	void drawLegend(node* root);

};
#endif
