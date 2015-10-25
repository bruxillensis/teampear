#include "stdafx.h"
#include "pubProfessor.h"
#include "modelExceptions.h"

using namespace std;

pubProfessor::pubProfessor(){
    this->memberName = "";	//Member Name
    this->primaryDomain = "";	//Primary Domain
    this->numberOfBookChapters = 0;
    this->numberOfBooks = 0;
    this->numberOfBookEdits = 0;
    this->numberOfCaseReports = 0;
    this->numberOfClinicalCareGuides = 0;
    this->numberOfCommentaries = 0;
    this->numberOfConferences = 0;
    this->numberOfEditorials = 0;
    this->numberOfInvitedArticles = 0;
    this->numberOfJournalArticles = 0;
    this->numberOfLetters = 0;
    this->numberOfMagazine = 0;
    this->numberOfManuals = 0;
    this->numberOfMonographs = 0;
    this->numberOfMultimedia = 0;
    this->numberOfNewsletterArticles = 0;
    this->numberOfNewspaperArticles = 0;
    this->numberOfAbstracts = 0;
    this->numberOfStudentPubs = 0;
    this->numberOfWebVids = 0;
    this->numberOfWorkingPapers = 0;
    this->publicationStatus = new vector<string>();
    this->type = new vector<string>();
    this->role = new vector<string>();
    this->publicationName = new vector<string>();
    this->authors = new vector<string>();
    this->title = new vector<string>();
}
pubProfessor::pubProfessor(string memberName, string primaryDomain){
    this->memberName = memberName;	//Member Name
    this->primaryDomain = primaryDomain;	//Primary Domain
    this->numberOfBookChapters = 0;
    this->numberOfBooks = 0;
    this->numberOfBookEdits = 0;
    this->numberOfCaseReports = 0;
    this->numberOfClinicalCareGuides = 0;
    this->numberOfCommentaries = 0;
    this->numberOfConferences = 0;
    this->numberOfEditorials = 0;
    this->numberOfInvitedArticles = 0;
    this->numberOfJournalArticles = 0;
    this->numberOfLetters = 0;
    this->numberOfMagazine = 0;
    this->numberOfManuals = 0;
    this->numberOfMonographs = 0;
    this->numberOfMultimedia = 0;
    this->numberOfNewsletterArticles = 0;
    this->numberOfNewspaperArticles = 0;
    this->numberOfAbstracts = 0;
    this->numberOfStudentPubs = 0;
    this->numberOfWebVids = 0;
    this->numberOfWorkingPapers = 0;
    this->publicationStatus = new vector<string>();
    this->type = new vector<string>();
    this->role = new vector<string>();
    this->publicationName = new vector<string>();
    this->authors = new vector<string>();
    this->title = new vector<string>();
}
pubProfessor::~pubProfessor(){
    delete this->publicationStatus;
    delete this->type;
    delete this->role;
    delete this->publicationName;
    delete this->authors;
    delete this->title;
}

const string pubProfessor::getName()						{ return this->memberName; }
const string pubProfessor::getDomain()						{ return this->primaryDomain; }
const int getNumberOfBookChapters()							{ return this->numberOfBookChapters; }
const int getNumberOfBooks()								{ return this->numberOfBooks; }
const int getNumberOfBookEdits()							{ return this->numberOfBookEdits; }
const int getNumberOfCaseReports()							{ return this->numberOfCaseReports; }
const int getNumberOfClinicalCareGuides()					{ return this->numberOfClinicalCareGuides; }
const int getNumberOfCommentaries()							{ return this->numberOfCommentaries; }
const int getNumberOfConferences()							{ return this->numberOfConferences; }
const int getNumberOfEditorials()							{ return this->numberOfEditorials; }
const int getNumberOfInvitedArticles()						{ return this->numberOfInvitedArticles; }
const int getNumberOfJournalArticles()						{ return this->numberOfJournalArticles; }
const int getNumberOfLetters()								{ return this->numberOfLetters; }
const int getNumberOfMagazine()								{ return this->numberOfMagazine; }
const int getNumberOfManuals()								{ return this->numberOfManuals; }
const int getNumberOfMonographs()							{ return this->numberOfMonographs; }
const int getNumberOfMultimedia()							{ return this->numberOfMultimedia; }
const int getNumberOfNewsletterArticles()					{ return this->numberOfNewsletterArticles; }
const int getNumberOfNewspaperArticles()					{ return this->numberOfNewspaperArticles; }
const int getNumberOfAbstracts()							{ return this->numberOfAbstracts; }
const int getNumberOfStudentPubs()							{ return this->numberOfStudentPubs; }
const int getNumberOfWebVids()								{ return this->numberOfWebVids; }
const int getNumberOfWorkingPapers()						{ return this->numberOfWorkingPapers; }
const vector<string>* pubProfessor::getPublicationStatus()	{ return this->publicationStatus; }
const vector<string>* pubProfessor::getType()				{ return this->type; }
const vector<string>* pubProfessor::getRole()				{ return this->role; }
const vector<string>* pubProfessor::getPublicationName()	{ return this->publicationName; }
const vector<string>* pubProfessor::getAuthors()			{ return this->authors; }
const vector<string>* pubProfessor::getTitle()				{ return this->title; }

//Add an entry to all vectors
void pubProfessor::addEntry(string publicationStatus, string type, string role, string publicationName,
                            string authors, string title){
    switch(type){
        case "Book Chapters":
            this->numberOfBookChapters++;
            break;
        case "Books":
            this->numberOfBooks++;
            break;
        case "Books Edited":
            this->numberOfBookEdits++;
            break;
        case "Case Reports":
            this->numberOfCaseReports++;
            break;
        case "Clinical Case Guidelines":
            this->numberOfClinicalCareGuides++;
            break;
        case "Commentaries":
            this->numberOfCommentaries++;
            break;
        case "Conference Proceedings":
            this->numberOfConferences++;
            break;
        case "Editorials":
            this->numberOfEditorials++;
            break;
        case "Invited Articles":
            this->numberOfInvitedArticles++;
            break;
        case "Journal Article"
            this->numberOfJournalArticles++;
            break;
        case "Letters to Editor":
            this->numberOfLetters++;
            break;
        case "Magazine Entries":
            this->numberOfMagazine++;
            break;
        case "Manuals":
            this->numberOfManuals++;
            break;
        case "Monographs":
            this->numberOfMonographs++;
            break;
        case "Multimedia":
            this->numberOfMultimedia++;
            break;
        case "Newsletter Articles":
            this->numberOfNewsletterArticles++;
            break;
        case "Newspaper Articles":
            this->numberOfNewspaperArticles++;
            break;
        case "Published Abstracts":
            this->numberOfAbstracts++;
            break;
        case "Supervised Student Publications":
            this->numberOfStudentPubs++;
            break;
        case "Websites / Videos":
            this->numberOfWebVids++;
            break;
        case "Working Papers":
            this->numberOfWorkingPapers++;
            break;
    };
    this->publicationStatus->push_back(publicationStatus);
    this->type->push_back(type);
    this->role->push_back(role);
    this->publicationName->push_back(publicationName);
    this->authors->push_back(authors);
    this->title->push_back(title);
}

//Remove an entry, based on given index value (0 indexed)
void pubProfessor::removeEntry(int indexToRemove){
    if (indexToRemove >= this->numberOfPublications)
        throw new indexOutOfBoundsException();
    
    switch(type){
        case "Book Chapters":
            this->numberOfBookChapters--;
            break;
        case "Books":
            this->numberOfBooks--;
            break;
        case "Books Edited":
            this->numberOfBookEdits--;
            break;
        case "Case Reports":
            this->numberOfCaseReports--;
            break;
        case "Clinical Case Guidelines":
            this->numberOfClinicalCareGuides--;
            break;
        case "Commentaries":
            this->numberOfCommentaries--;
            break;
        case "Conference Proceedings":
            this->numberOfConferences--;
            break;
        case "Editorials":
            this->numberOfEditorials--;
            break;
        case "Invited Articles":
            this->numberOfInvitedArticles--;
            break;
        case "Journal Article"
            this->numberOfJournalArticles--;
            break;
        case "Letters to Editor":
            this->numberOfLetters--;
            break;
        case "Magazine Entries":
            this->numberOfMagazine--;
            break;
        case "Manuals":
            this->numberOfManuals--;
            break;
        case "Monographs":
            this->numberOfMonographs--;
            break;
        case "Multimedia":
            this->numberOfMultimedia--;
            break;
        case "Newsletter Articles":
            this->numberOfNewsletterArticles--;
            break;
        case "Newspaper Articles":
            this->numberOfNewspaperArticles--;
            break;
        case "Published Abstracts":
            this->numberOfAbstracts--;
            break;
        case "Supervised Student Publications":
            this->numberOfStudentPubs--;
            break;
        case "Websites / Videos":
            this->numberOfWebVids--;
            break;
        case "Working Papers":
            this->numberOfWorkingPapers--;
            break;
    };
    this->publicationStatus->erase(this->publicationStatus->begin() + indexToRemove);
    this->type->erase(this->publicationStatus->begin() + indexToRemove);
    this->role->erase(this->publicationStatus->begin() + indexToRemove);
    this->publicationName->erase(this->publicationStatus->begin() + indexToRemove);
    this->authors->erase(this->publicationStatus->begin() + indexToRemove);
    this->title->erase(this->publicationStatus->begin() + indexToRemove);
    
}