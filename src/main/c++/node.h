#pragma once
#include <string>
#include <vector>

using namespace std;

/* This class is intended to instantiate a tree
	I am not positive if the number of storage variables (first second third and fourth)
	are enough to cover our needs in the list and different graphs. If values need to be
	added they can be.
*/

class node {
private:
	string first;
	int	second;
	int third;
	float fourth;
	vector<node*>* children;
	bool visible;
public:
	//Constructor
	node(){
		first = "";
		second = 0;
		third = 0;
		fourth = 0;
		children = new vector<node*>();
		visible = false;
	}
	
	//Constructor for all known values
	node(string first, int second, int third, float fourth){
		this->first = first;
		this->second = second;
		this->third = third;
		this->fourth = fourth;
		children = new vector<node*>();
		visible = false;
	}
	
	//Constructor with another tree as argument
	node(node& orig){
		this->first = orig.getFirst();
		this->second = orig.getSecond();
		this->third = orig.getThird();
		this->fourth = orig.getFourth();
		this->visible = orig.getVisible();
	}

	//Should delete node and all of this children recursively
	~node(){
		delete &first;
		delete &second;
		delete &third;
		delete &fourth;
		delete children;
		delete &visible;
	}

	//Return the location of children vector
	vector<node*>* getChildren(){ return children; }
	
	//return index of the child with the name as a parameter
	int findChildPosition(node* child){
		for (size_t i = 0; i < children->size(); i++){
			if (child->getFirst() == children->at(i)->getFirst()){
				if (child->getSecond() == children->at(i)->getSecond()){
					if (child->getThird() == children->at(i)->getThird()){
						if (child->getFourth() == children->at(i)->getFourth()){
							return i;
						}
					}
				}
			}
		}
	}
	
	//Add a child to the tree
	void addChild(node* child){
		vector<node*>::iterator it;

		it = children->begin();
		if (children->size() == 0){
			children->push_back(child);
		}
		else{
			for (size_t i = 0; i < children->size(); i++){
				//child's name is less than child's
				if (child->getFirst().compare(children->at(i)->getFirst()) < 0){
					children->insert(it + i, child);
					i = children->size();
				}
				else if (i == (children->size() - 1)){
					children->push_back(child);
					i = children->size();
				}
			}
		}
	}
	
	//Removes a child from the tree. As this is not a tree that can be reorganized
	//the children of the removed child are also removed recusively
	void removeChild(node* child){
		int index = findChildPosition(child);
		children->erase(children->begin() + index);
	}

	//Set the string of the node
	//For nodes other than leaves this will be the only value used
	void setFirst(string first){
		this->first = first;
	}
	//Set a first integer value of node
	//Only used for leaves that need to store an integer (count, number of sessions etc.)
	void setSecond(int second){
		this->second = second;
	}
	//Set a second integer value of node
	//Only used for leaves that need to store an integer (count, number of sessions etc.)
	void setThird(int third){
		this->third = third;
	}
	//Set a float value of node
	//Only used for leaves that need to store a float (grant money etc.)
	void setFourth(float fourth){
		this->fourth = fourth;
	}

	//Get functions
	string getFirst(){ return first; }
	int getSecond(){ return second; }
	int getThird(){ return third; }
	float getFourth(){ return fourth; }
	bool getVisible(){ return visible };
};
