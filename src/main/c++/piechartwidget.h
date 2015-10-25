#ifndef PIECHARTWIDGET_H
#define PIECHARTWIDGET_H

#include <QWidget>

class PieChartWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PieChartWidget(QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent *);
    /*,
                std::vector<std::pair<std::string,std::vector<std::pair<std::string,std::string> > > > );*/
};

#endif // PIECHARTWIDGET_H
