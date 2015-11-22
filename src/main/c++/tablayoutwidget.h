#ifndef TABLAYOUTWIDGET_H
#define TABLAYOUTWIDGET_H

#include <QWidget>
#include "filterdialog.h"

namespace Ui {
class tabLayoutWidget;
}

class tabLayoutWidget : public QWidget
{
    Q_OBJECT

public:
    explicit tabLayoutWidget(QWidget *parent = 0);
    ~tabLayoutWidget();

private slots:


    void on_filterDataButton_clicked();

private:
    Ui::tabLayoutWidget *ui;
};

#endif // TABLAYOUTWIDGET_H
