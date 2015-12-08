#include "helpdialog.h"
#include "ui_helpdialog.h"

helpDialog::helpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::helpDialog)
{
    ui->setupUi(this);
	QString appDir = QApplication::applicationDirPath();
	QPalette pal;
	pal.setBrush(ui->textBrowser->viewport()->backgroundRole(), QBrush(QImage(appDir + "/resources/helpdialog.png")));
	ui->textBrowser->viewport()->setPalette(pal);
}

helpDialog::~helpDialog()
{
    delete ui;
}
