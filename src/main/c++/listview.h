#ifndef LISTVIEW_H
#define LISTVIEW_H

#include <qtreewidget.h>
#include <QWidget>
#include <QTreeWidget>
#include "pubTree.h"
#include "node.h"
#include <QtCore>
#include <QtGui>
#include <QtCore>
#include <QtGui>
#include <QMessageBox>
#include <QTreeWidget>
using namespace std;

class ListView : public QTreeWidget
{
		Q_OBJECT
public:
	ListView(QWidget *parent);
	void makeList(node *root);
	void populateList(node *root, QTreeWidgetItem* parent);

private:
	node* nodeData;
};

#endif // LISTVIEW_H
