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
	vector<bool>* visible;
	node* parent;
public:
	//Constructor
	node(){
		first = "";
		second = 0;
		third = 0;
		fourth = 0;
		children = new vector<node*>();
		visible = new vector<bool>(5, true);
		parent = NULL;
	}
	
	//Constructor for all known values
	node(string first, int second, int third, float fourth){
		this->first = first;
		this->second = second;
		this->third = third;
		this->fourth = fourth;
		children = new vector<node*>();
		visible = new vector<bool>(5, true);
		parent = NULL;
	}
	/*
	//Constructor with another tree as argument
	node(node& orig){
		this->first = orig.getFirst();
		this->second = orig.getSecond();
		this->third = orig.getThird();
		this->fourth = orig.getFourth();
		visible = new vector<bool>(5, true);
		children = new vector<node*>();
		parent = NULL;
	}*/

	//Should delete node and all of this children recursively
	~node(){
		for (int i = 0; i < children->size(); i++)
			delete children->at(i);
	}

	//Return the location of children vector
	vector<node*>* getChildren(){ return children; }

	//return index of the child with the name as a parameter
	int findChildPosition(node* child){
		return std::distance(children->begin(),std::find(children->begin(), children->end(), child));
	}
	
	//Add a child to the tree
	void addChild(node* child){
		vector<node*>::iterator it;

		it = children->begin();
		if (children->size() == 0){
			children->push_back(child);
			child->setParent(this);
		}
		else{
			for (size_t i = 0; i < children->size(); i++){
				//child's name is less than child's
				if (child->getFirst().compare(children->at(i)->getFirst()) < 0){
					children->insert(it + i, child);
					i = children->size();
					child->setParent(this);
				}
				else if (i == (children->size() - 1)){
					children->push_back(child);
					i = children->size();
					child->setParent(this);
				}
			}
		}
	}
	
	//Removes a child from the tree. As this is not a tree that can be reorganized
	//the children of the removed child are also removed recusively
	void removeChild(node* child){
		int i = findChildPosition(child);
		delete children->at(i);
		children->erase(children->begin() + i);
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
	//set parent of the node
	void setParent(node* parent){
		this->parent = parent;
	}
	//set visibility of the node
	//Visible (count, date, domain, funding, hours)
	void setVisible(string filterType, bool visible){
		if (filterType.compare("count")){
			this->visible->at(0) = visible;
		}
		else if (filterType.compare("date")){
			this->visible->at(1) = visible;
		}
		else if (filterType.compare("domain")){
			this->visible->at(2) = visible;
		}
		else if (filterType.compare("funding")){
			this->visible->at(3) = visible;
		}
		else if (filterType.compare("hours")){
			this->visible->at(4) = visible;
		}
	}

	//Get functions
	const string getFirst(){ return first; }
	const int getSecond(){ return second; }
	const int getThird(){ return third; }
	const float getFourth(){ return fourth; }
	const node* getParent(){ return parent; }
	const bool getVisible(){ 
		for (int i = 0; i < visible->size(); i++){
			if (visible->at(i) == false)
				return false;
		}
		return true;
	}
	const string const_getFirst() const{ return first; }
	const node* const_getParent() const{ return parent; }
};

inline bool operator==(node& lhs, node& rhs){
	return (lhs.getFirst() == rhs.getFirst()) &&
		(lhs.getSecond() == rhs.getSecond()) &&
		(lhs.getThird() == rhs.getThird()) &&
		(lhs.getFourth() == rhs.getFourth()) &&
		(lhs.getVisible() == rhs.getVisible());
}