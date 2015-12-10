#ifndef PIECHARTWIDGET_H
#define PIECHARTWIDGET_H

#include <QWidget>
#include "node.h"

class PieChartWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PieChartWidget(QWidget *parent = 0);
    void setData(node* root);
protected:
    void paintEvent(QPaintEvent * );

private:
    node* data;
};

#endif // PIECHARTWIDGET_H
