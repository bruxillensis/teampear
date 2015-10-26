#ifndef PIECHARTWIDGET_H
#define PIECHARTWIDGET_H

#include <QWidget>

class PieChartWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PieChartWidget(QWidget *parent = 0);
    void setData(std::vector<std::pair<std::string,std::vector<std::pair<std::string,std::string> > > >);
protected:
    void paintEvent(QPaintEvent * );

private:
    std::vector<std::pair<std::string,std::vector<std::pair<std::string,std::string> > > > data;
};

#endif // PIECHARTWIDGET_H
