#pragma once
#include <string>

using namespace std;

#include "professor.h"
class pubProfessor :public professor {
private:
	int abstracts;
	int journalArticles;
	int books;
	int booksEdited;
	int bookChapters;
	int editorLetters;
	int caseReports;
	int clinicalGuidelines;
	int commentaries;
	int conferenceProceedings;
	int editorials;
	int invitedArticles;
	int magazineEntries;
	int manuals;
	int monographs;
	int multimedia;
	int newsletterArticles;
	int newspaperArticles;
	int studentPubs;
	int websitesVideos;
	int workingPapers;

public:
	int getAbstracts();
	int getJournalArticles();
	int getBooks();
	int getBooksEdited();
	int getBookChapters();
	int getEditorLetters();
	int getCaseReports();
	int getClinicalGuidelines();
	int getCommentaries();
	int getConferenceProceedings();
	int getEditorials();
	int getInvitedArticles();
	int getMagazineEntries();
	int getManuals();
	int getMonographs();
	int getMultimedia();
	int	getNewsletterArticles();
	int getNewspaperArticles();
	int getStudentPubs();
	int getWebsitesVideos();
	int getWorkingPapers();

	void incAbstracts();
	void incJournalArticles();
	void incBooks();
	void incBooksEdited();
	void incBookChapters();
	void incEditorLetters();
	void incCaseReports();
	void incClinicalGuidelines();
	void incCommentaries();
	void incConferenceProceedings();
	void incEditorials();
	void incInvitedArticles();
	void incMagazineEntries();
	void incManuals();
	void incMonographs();
	void incMultimedia();
	void incNewsletterArticles();
	void incNewspaperArticles();
	void incStudentPubs();
	void incWebsitesVideos();
	void incWorkingPapers();

	void decAbstracts();
	void decJournalArticles();
	void decBooks();
	void decBooksEdited();
	void decBookChapters();
	void decEditorLetters();
	void decCaseReports();
	void decClinicalGuidelines();
	void decCommentaries();
	void decConferenceProceedings();
	void decEditorials();
	void decInvitedArticles();
	void decMagazineEntries();
	void decManuals();
	void decMonographs();
	void decMultimedia();
	void decNewsletterArticles();
	void decNewspaperArticles();
	void decStudentPubs();
	void decWebsitesVideos();
	void decWorkingPapers();
};