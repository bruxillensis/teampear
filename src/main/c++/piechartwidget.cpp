#include "piechartwidget.h"
#include <QPainter>
#include <vector>
#include <QColor>
#include <iostream>
#include "node.h"

#define HUE_MAX		359			//maximum HSV value
#define PIE_MULT	16			//Pie slice multiplier
#define C_SAT		175			//Pie slice saturation
#define C_VAL		240			//Pie slice lightness
#define DEGREES		360			//multiplier to convert pie slices to degrees
#define EDGE		10			//white space between pie chart and edge of window
#define MAX_NODES	20			//Max amount of pie chart nodes on screen

using namespace std;

PieChartWidget::PieChartWidget(QWidget *parent): QWidget(parent)
{
}

void PieChartWidget::paintEvent(QPaintEvent *)
{
    int i, j, c_inc;
	float current, total, other = 0;
    QPainter painter(this);
    QRectF size = QRectF(EDGE, EDGE, this->width()-EDGE, this->width()-EDGE);
	int hue = 0, last_slice = 0;
	double current_slice;

	//check if csv data is of grants and clinical funding type
	bool money = false;

	if (data->getFourth() != 0)
		money = true;

	QColor color;

	vector<node*> *children = data->getChildren();
	vector<node*> *top_nodes = new vector<node*>();

    //get total for pie chart
	if (money)
		total = data->getFourth();
	else
		total = data->getSecond();

	for (i = 0; i < children->size(); i++){
		if (top_nodes->size() >= MAX_NODES)
		{
			for (j = 0; j < top_nodes->size(); j++)
			{
				if ((children->at(i)->getSecond()>top_nodes->at(j)->getSecond() && !money) 
					|| (children->at(i)->getFourth()>top_nodes->at(j)->getFourth() && money))
				{
					if (money)
						other += top_nodes->at(j)->getFourth();
					else
						other += top_nodes->at(j)->getSecond();

					top_nodes->at(j) = children->at(i);
					break;

				}
			}
		}
		else
		{
			if (((children->at(i)->getSecond()/ total)*360 < 4 && !money)
				||((children->at(i)->getFourth() / total) * 360 < 4 && money)){
				if (money)
					other += children->at(i)->getFourth();
				else
					other += children->at(i)->getSecond();
			} else
				top_nodes->push_back(children->at(i));
		}
	}


	//color increment
	if (top_nodes->size() < 20)
		c_inc = HUE_MAX / top_nodes->size();
	else
		c_inc = HUE_MAX / MAX_NODES + 1;
	

    //for loop to gen pie slices
    for(i=0; i < top_nodes->size(); i++){
		//get current pie slice size
		if (money)
			current = top_nodes->at(i)->getFourth();
		else
			current = top_nodes->at(i)->getSecond();

		cout << current << endl;

        if(current > 0){
	
            color.setHsv(hue,C_SAT,C_VAL);						//gen new color
            painter.setBrush(color);							//set brush as new color
            current_slice =(current/total)*DEGREES;				//generate slice

			if (i == top_nodes->size()-1 && (current_slice + last_slice) < DEGREES && top_nodes->size() <= 20){
				current_slice += DEGREES - (current_slice + last_slice);
			}

			painter.drawPie(size, last_slice*PIE_MULT, (int)current_slice*PIE_MULT);	//draw slice
            last_slice += current_slice;	//increment tracker of last slice place

            hue += c_inc;					//increment hue
        }
    }

	if (other > 0){
		color.setHsv(hue, C_SAT, C_VAL);
		painter.setBrush(color);
		current_slice = (other / total)*DEGREES;
		current_slice += DEGREES - (current_slice + last_slice);

		painter.drawPie(size, last_slice*PIE_MULT, (int)current_slice*PIE_MULT);
	}

}

//method sends the data to the piechart and redraws chart
//@Param root: root node to draw pie chart from
void PieChartWidget::setData(node* root)
{
	//sets the private variable data to root
    data = root;

	//repaints the pie chart
    repaint();

	//updates the visual of the new pie chart
    update();

}

