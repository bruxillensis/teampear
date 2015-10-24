#include "piechartwidget.h"
#include <QPainter>
#include <vector>
#include <QColor>

PieChartWidget::PieChartWidget(QWidget *parent): QWidget(parent)
{
}

void PieChartWidget::paintEvent(QPaintEvent *,
                                std::vector<std::pair<std::string, std::vector<std::pair<std::string, std::string> > > > q)
{
    int i, current, total = 0;
    QPainter painter(this);
    QRectF size = QRectF(10, 10, this->width()-10, this->width()-10);
    int currentHue = 0, last_slice = 0, current_slice;
    std::vector< std::pair< std::string, QColor>> legendVec;

    //get total number of pubs
    for(i = 0; i < q.size(); i++){
        total += q.at(i).second.size();
    }

    //gen pie slices
    for(i=0; i < q.size(); i++){
        QColor current_color;
        current_color.setHsv(currentHue,255,127);
        painter.setBrush(current_color);
        current = q.at(i).second.size();
        current_slice = (current/total)*360*16;
        painter.drawPie(size, last_slice, current_slice);
        last_slice = current_slice;
        currentHue += 17;
        std::pair< std::string, QColor> cur_legend;
        cur_legend.first = q.at(i).first;
        cur_legend.second = current_color;
        legendVec.push_back(cur_legend);
    }

}

