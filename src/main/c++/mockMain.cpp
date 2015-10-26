#include <iostream>
#include "professorMap.h"
#include "pubProfessor.h"
#include <vector>
#include "createProfessor.h"
#include <map>

using namespace std;

void importA(string filename) {
	//read CSV file into 2D array
	vector<vector<string>*> myCSV;
	vector<string>* valueLine;
	ifstream inFile(filename);
	string temp;

	//make 2D vector
	for (string line; getline(inFile, line);)
	{
		istringstream in(line);
		valueLine = new vector<string>();
		while (getline(in, temp, ','))
			valueLine->push_back(temp);

		myCSV.push_back(valueLine);
	}

	for (size_t i = 0; i < myCSV.size(); i++) {
		for (size_t j = 0; j < myCSV[i]->size(); j++) {
			cout << i << " " << j << ": " << myCSV[i]->at(j);
			cout << '\n';
		}
	}
}

int main(){
    professorMap<pubProfessor> map("Publications_sample.csv");
   /* vector<pair<string,vector<pair<string,int> > > > returnVector = map.callMe();
	
	for (vector<pair<string, vector<pair<string, int> > > >::const_iterator it = returnVector.begin(); it != returnVector.end(); ++it){ // iterate through the publication types
		cout << "TYPE: " << it->first << '\n';
		for (vector<pair<string, int> >::const_iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2){
			//cout << "hasdfsdafadsfdasello";
			cout << "prof name: " << it2->first << endl;
			cout << "numPubs: " << it2->second << endl;
		}
	}*/

	//importA("database.txt");

	int x;
	cin >> x;
    return 0;
    
}
