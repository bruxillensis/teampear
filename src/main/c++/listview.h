#ifndef LISTVIEW_H
#define LISTVIEW_H

#include <qtreewidget.h>
#include <QWidget>
#include <pubTree.h>
#include "node.h"
using namespace std;

class ListView : public QTreeWidget
{
		Q_OBJECT
public:
	ListView(QWidget *parent);
	void makeList(node *root);
	void addChild(QTreeWidgetItem* parent, QString name, QString description);

private:
	node* nodeData;
};

#endif // LISTVIEW_H
