#ifndef BARDIALOG_H
#define BARDIALOG_H

#include <QDialog>
#include "qcustomplot.h"

using namespace std;

namespace Ui {
class BarDialog;
}

class BarDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BarDialog(QWidget *parent, vector<pair<string,vector<pair<string,int> > > > );
    ~BarDialog();

private:
    Ui::BarDialog *ui;
    vector<pair<string,vector<pair<string,int> > > > data;
};

#endif // BARDIALOG_H
