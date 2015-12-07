#pragma once
#include <string>
#include <vector>
#include <QErrorMessage>
#include <QString>
#include "errorHandling.h"
#include "professor.h"
#include "modelExceptions.h"
#include "boost/variant.hpp"
#include "boost/date_time/gregorian/gregorian.hpp"

using namespace std;

class createProfessor {
public:
	/* Fields
		Publication Status: String
		Type			  : String
		Role			  : String
		Publication Name  : String
		Title			  :	String
		Authors			  : String
		Date			  : Boost::Gregorian::Date
	*/
	static pair<professor*, int> createNewPubProfessor(vector<vector<string>>& csv) {
		//Define manditory fields for a publication csv
		vector<string> manFields = {"Member Name", "Primary Domain", "Publication Status", "Type", "Status Date",
			"Role", "Journal Name | Published In | Book Title | etc.", "Author(s)", "Title" };
		vector<int> headerNumbers = findHeaders(manFields, csv[0]);
		int count = 0;
		//Create professor
		professor* prof = new professor(findValue(csv, headerNumbers[0]), findValue(csv, headerNumbers[1]), 7);
		for (int i = 1; i < csv.size(); i++) {
			//Add the new entry to the prof
			try {
				//Check row for manditory fields
				errorHandling::checkRow(csv[i], csv[0], vector<string>(manFields.begin()+2, manFields.end()));
				//Create vector will all necessary information
				auto e = new vector<boost::variant<int, float, string, bool, boost::gregorian::date>>{
					csv[i][headerNumbers[2]], csv[i][headerNumbers[3]],
					errorHandling::checkYear(csv[i][headerNumbers[4]]),
					csv[i][headerNumbers[5]], csv[i][headerNumbers[6]],
					csv[i][headerNumbers[7]], csv[i][headerNumbers[8]] };
				//Add entry to prof
				prof->addEntry(e);
				//Clean up
				delete e;
			}
			catch (emptyManditoryCellException& e){
				count++;
				cerr << e.what();
			}
			catch (manditoryHeaderNotFoundException& e){
				QErrorMessage msg;
				msg.showMessage(QString("Mandatory Headers Not Found. Expected Headers are: Member Name, \
										Primary Domain, Publication Status, Type, Status Date, Role, \
										Journal Name | Published In | Book Title | etc., Author(s), Title"));
				msg.exec();
				cerr << e.what();
			}
			catch (invalidDateException& e){
				count++;
				cerr << e.what();
			}
		}
		return pair<professor*, int>(prof,count);
	}
	/* Fields
		Start Date		  : Boost::Gregorian::Date
		End Date		  : Boost::Gregorian::Date
		Type			  : String
		Grant Status	  : String
		Peer Reviewed	  : Boolean
		Industry Grant	  : Boolean
		Role			  : String
		Title			  : String
		Principal Inv.	  : String
		Co-Investigators  : String
		Funding Amount	  : Float
	*/
	static pair<professor*,int> createNewGranProfessor(vector<vector<string>>& csv){
		//Define manditory fields for a grantclinical csv
		vector<string> manFields = { "Member Name", "Primary Domain", "Start Date", "End Date", "Funding Type", "Status",
			"Peer Reviewed?", "Industry Grant?", "Role", "Title",
			"Principal Investigator", "Co-Investigators", "Total Amount" };
		vector<int> headerNumbers = findHeaders(manFields, csv[0]);
		int count = 0;
		//Create professor
		professor* prof = new professor(findValue(csv, headerNumbers[0]), findValue(csv, headerNumbers[1]), 11);
		for (int i = 1; i < csv.size(); i++) {
			//Add the new entry to the prof
			try{
				//Check row for manditory fields
				errorHandling::checkRow(csv[i], csv[0], vector<string>(manFields.begin() + 2, manFields.end()));
				//Create vector will all necessary information
				auto e = new vector<boost::variant<int, float, string, bool, boost::gregorian::date>>{
					errorHandling::checkYear(csv[i][headerNumbers[2]]),
					errorHandling::checkYear(csv[i][headerNumbers[3]]),
					csv[i][headerNumbers[4]], csv[i][headerNumbers[5]],
					errorHandling::toBool(csv[i][headerNumbers[6]]),
					errorHandling::toBool(csv[i][headerNumbers[7]]),
					csv[i][headerNumbers[8]], csv[i][headerNumbers[9]],
					csv[i][headerNumbers[10]], csv[i][headerNumbers[11]],
					errorHandling::toFloat(csv[i][headerNumbers[12]]) };
				//Add entry to prof
				prof->addEntry(e);
				//Clean up
				delete e;
			}
			catch (emptyManditoryCellException& e){
				count++;
				cerr << e.what();
			}
			catch (manditoryHeaderNotFoundException& e){
				QErrorMessage msg;
				msg.showMessage(QString("Mandatory Headers Not Found. Expected Headers are: Member Name, \
										Primary Domain, Start Date, End Date, Funding Type, Status, \
										Peer Reviewed?, Industry Grant?, Role, Title, Principal Investigator, \
										Co-Investigators, Total Amount"));
				msg.exec();
				cerr << e.what();
			}
			catch (failedTypeChangeException& e){
				count++;
				cerr << e.what();
			}
			catch (invalidDateException& e){
				count++;
				cerr << e.what();
			}
		}
		return pair<professor*, int>(prof, count);
	}
	/* Fields
		Start Date		  : Boost::Gregorian::Date
		End Date		  : Boost::Gregorian::Date
		Program 		  : String
		Course Type		  : String
		Geographical Scope:	String
		Hours per Session : Float
		Number of Sessions: Int
		Total Hours		  : Float
	*/
	static pair<professor*, int> createNewTeacProfessor(vector<vector<string>>& csv){
		//Define manditory fields for a teaching csv
		vector<string> manFields = { "Member Name", "Primary Domain", "Start Date", "End Date", "Program", "Type of Course / Activity",
			"Course / Activity", "Geographical Scope", "Hours per Teaching Session or Week",
			"Number of Teaching Sessions or Weeks", "Total Hours" };
		vector<int> headerNumbers = findHeaders(manFields, csv[0]);
		int count = 0;
		//Create professor
		professor* prof = new professor(findValue(csv, headerNumbers[0]), findValue(csv, headerNumbers[1]), 9);
		for (int i = 1; i < csv.size(); i++) {
			//Add the new entry to the prof
			try{
				//Check row for manditory fields
				errorHandling::checkRow(csv[i], csv[0], vector<string>(manFields.begin() + 2, manFields.end()));
				//Create vector will all necessary information
				auto e = new vector<boost::variant<int, float, string, bool, boost::gregorian::date>>{
					errorHandling::checkYear(csv[i][headerNumbers[2]]),
					errorHandling::checkYear(csv[i][headerNumbers[3]]),
					csv[i][headerNumbers[4]], csv[i][headerNumbers[5]],
					csv[i][headerNumbers[6]], csv[i][headerNumbers[7]],
					errorHandling::toFloat(csv[i][headerNumbers[8]]),
					errorHandling::toFloat(csv[i][headerNumbers[9]]),
					errorHandling::toFloat(csv[i][headerNumbers[10]]) };
				//Add entry to prof
				prof->addEntry(e);
				//Clean up
				delete e;
			}
			catch (emptyManditoryCellException& e){
				count++;
				cerr << e.what();
			}
			catch (manditoryHeaderNotFoundException& e){
				QErrorMessage msg;
				msg.showMessage(QString("Mandatory Headers Not Found. Expected Headers are: \
										Member Name, Primary Domain, Start Date, End Date, Program, \
										Type of Course / Activity, Course / Activity, Geographical Scope, \
										Hours per Teaching Session or Week, Number of Teaching Sessions or Weeks, \
										Total Hours"));
				msg.exec();
				cerr << e.what();
			}
			catch (failedTypeChangeException& e){
				count++;
				cerr << e.what();
			}
		}
		return pair<professor*, int>(prof, count);
	}
	/* Fields
		Date			  : Boost::Gregorian::Date
		Type			  : String
		Role			  : String
		Title			  : String
	*/
	static pair<professor*, int> createNewPresProfessor(vector<vector<string>>& csv){
		//Define manditory fields for a presentation csv
		vector<string> manFields = { "Member Name", "Primary Domain", "Type", "Role", "Title", "Date" };
		vector<int> headerNumbers = findHeaders(manFields, csv[0]);
		int count = 0;
		//Create professor
		professor* prof = new professor(findValue(csv, headerNumbers[0]), findValue(csv, headerNumbers[1]), 4);
		for (int i = 1; i < csv.size(); i++) {
			//Add the new entry to the prof
			try{
				//Check row for manditory fields
				errorHandling::checkRow(csv[i], csv[0], vector<string>(manFields.begin() + 2, manFields.end()));
				//Create vector will all necessary information
				auto e = new vector<boost::variant<int, float, string, bool, boost::gregorian::date>>{
					csv[i][headerNumbers[1]], csv[i][headerNumbers[2]],
					csv[i][headerNumbers[4]], errorHandling::checkYear(csv[i][headerNumbers[5]]) };
				//Add entry to prof
				prof->addEntry(e);
				//Clean up
				delete e;
			}
			catch (emptyManditoryCellException& e){
				count++;
				cerr << e.what();
			}
			catch (manditoryHeaderNotFoundException& e){
				QErrorMessage msg;
				msg.showMessage(QString("Mandatory Headers Not Found. Expected Headers are: \
										Member Name, Primary Domain, Type, Role, Title, Date"));
				msg.exec();
				cerr << e.what();
			}
			catch (failedTypeChangeException& e){
				count++;
				cerr << e.what();
			}
		}
		return pair<professor*, int>(prof,count);
	}

	//Find headers given string values
	static vector<int> findHeaders(vector<string> manFields, vector<string> headers){
		vector<int> returnVec;
		for (int i = 0; i < manFields.size(); i++){
			auto& it = std::find(headers.begin(), headers.end(), manFields[i]);
			if (it!=headers.end())
				returnVec.push_back(std::distance(headers.begin(), it));
		}
		return returnVec;
	}
	static string findValue(vector<vector<string>>& csv, int j){
		for (int i = 1; i < csv.size();i++){
			if (csv[i][j] != "")
				return csv[i][j];
		}
		throw new emptyManditoryCellException();
	}
};