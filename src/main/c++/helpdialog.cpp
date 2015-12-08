#include "helpdialog.h"
#include "ui_helpdialog.h"

helpDialog::helpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::helpDialog)
{
    ui->setupUi(this);
	ui->textBrowser->viewport()->setAutoFillBackground(false);
	QPalette pal;
	QString appDir = QApplication::applicationDirPath();
	pal.setBrush(this->backgroundRole(), QBrush(QImage(appDir + "/resources/helpdialog.png")));
	this->setPalette(pal);
}

helpDialog::~helpDialog()
{
    delete ui;
}
