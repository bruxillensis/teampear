#ifndef BARDIALOG_H
#define BARDIALOG_H

#include <QDialog>
#include "qcustomplot.h"
#include "statisticsTree.h"
#include "node.h"

using namespace std;
	
namespace Ui {
class BarDialog;
}


class BarDialog : public QDialog
{
    Q_OBJECT

public:
	explicit BarDialog(QWidget *parent, node* rootNode);
    ~BarDialog();

private:
    Ui::BarDialog *ui;
	node* treeData;
	string dataType;
};

#endif // BARDIALOG_H
