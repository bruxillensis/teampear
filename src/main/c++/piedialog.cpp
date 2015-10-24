#include "piedialog.h"
#include "ui_piedialog.h"

PieDialog::PieDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PieDialog)
{
    ui->setupUi(this);
}

PieDialog::~PieDialog()
{
    delete ui;
}
