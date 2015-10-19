#include "stdafx.h"
#include <string>
#include "vectorToProfessor.h"
#include "csvHolder.h"
#include "professor.h"
#include "pubProfessor.h"
#include "errorHandling.h"

using namespace std;

//Create professor object, filling in all information and pass reference back
pubProfessor* vectorToProfessor::createProfessor(string professorName, csvHolder& modelArray) {

	int rowCount = modelArray.getNumberofRows(professorName);
	int firstRow = modelArray.getRowPosition(professorName);
	int column = modelArray.getColumnPosition(string(""));

	pubProfessor* prof = new pubProfessor();
	prof->setName(professorName);

	for (int i = 0; i < rowCount; i++) {
		string type = modelArray.getCell(professorName, i, column);
		if (errorHandling::checkIfPublished(
			modelArray.getCell(professorName, i, modelArray.getColumnPosition("Publication Status")))){
			if (type == "Book Chapters") { prof->incBookChapters(); continue; }
			if (type == "Books") { prof->incBooks(); continue; }
			if (type == "Books Edited") { prof->incBooksEdited(); continue; }
			if (type == "Case Reports") { prof->incCaseReports(); continue; }
			if (type == "Clinical Care Guidelines") { prof->decClinicalGuidelines(); continue; }
			if (type == "Commentaries") { prof->incCommentaries(); continue; }
			if (type == "Conference Proceedings") { prof->incConferenceProceedings(); continue; }
			if (type == "Editorials") { prof->incEditorials(); continue; }
			if (type == "Invited Articles") { prof->incInvitedArticles(); continue; }
			if (type == "Journal Article") { prof->incJournalArticles(); continue; }
			if (type == "Letters to Editor") { prof->incEditorLetters(); continue; }
			if (type == "Magazine Entries") { prof->incMagazineEntries(); continue; }
			if (type == "Manuals") { prof->incManuals(); continue; }
			if (type == "Monographs") { prof->incMonographs(); continue; }
			if (type == "Multimedia") { prof->incMultimedia(); continue; }
			if (type == "Newsletter Articles") { prof->incNewsletterArticles(); continue; }
			if (type == "Newspaper Articles") { prof->incNewspaperArticles(); continue; }
			if (type == "Published Abstract") { prof->incAbstracts(); continue; }
			if (type == "Supervised Student Publications") { prof->incStudentPubs(); continue; }
			if (type == "Websites / Videos") { prof->incWebsitesVideos(); continue; }
			if (type == "Working Papers") { prof->incWorkingPapers(); continue; }
		}
	}
	return prof;
}