#include <iostream>
#include "professorMap.h"
#include "pubProfessor.h"
#include <vector>
#include "createProfessor.h"
#include <map>

using namespace std;

int main(){
    professorMap<pubProfessor> map("Publications_sample.csv");
    vector<pair<string,vector<pair<string,int> > > > returnVector = map.callMe();
	
	for (vector<pair<string, vector<pair<string, int> > > >::const_iterator it = returnVector.begin(); it != returnVector.end(); ++it){ // iterate through the publication types
		cout << it->first << '\n';
		for (vector<pair<string, int> >::const_iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2){
			cout << "hasdfsdafadsfdasello";
			cout << it2->first << " " << it2->second << endl;
		}
	}
	cout << "\nhello";
	int x;
	cin >> x;
    return 0;
    
}