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
public:
	//Constructor
	node();
	//Constructor for all known values
	node(string first, int second, int third, float fourth);
	//Constructor with another tree as argument
	node(node& orig);
	//Should delete node and all of this children recursively
	~node();

	//Return the location of children vector
	vector<node*>* getChildren();
	//Organize children alphabetically (can also contain numbers)
	void organizeChildren();
	//Add a child to the tree
	void addChild(node* child);
	//Removes a child from the tree. As this is not a tree that can be reorganized
	//the children of the removed child are also removed recusively
	void removeChild(node* child);

	//Set the string of the node
	//For nodes other than leaves this will be the only value used
	void setFirst(string first);
	//Set a first integer value of node
	//Only used for leaves that need to store an integer (count, number of sessions etc.)
	void setSecond(int second);
	//Set a second integer value of node
	//Only used for leaves that need to store an integer (count, number of sessions etc.)
	void setThird(int third);
	//Set a float value of node
	//Only used for leaves that need to store a float (grant money etc.)
	void setFourth(float fourth);

	//Get functions
	string getFirst();
	int getSecond();
	int getThird();
	float getFourth();
};
