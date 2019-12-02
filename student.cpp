#ifndef STUDENT
#define STUDENT

#include "student.h"

Student::Student(): User()
{
}

Student::Student(string name, string password, string email) : User(name,email,password)
{

}

void Student::addSearchHistory(vector<string> x)
{
    for(int i =0; i<x.size();i++)
    this->searchHistory_names.push_back(x[i]);
}

void Student::addFavoriteBooks(vector<string> x)
{
    for(int i =0; i<x.size();i++)
        this->favoriteBooks_names.push_back(x[i]);
}

void Student::showInfo()
{
    cout <<"User's info : "<<endl;
    cout << "Name : " << Name << endl << "E-mail : " << Email << endl << "Cash Amount : "<< cash_amount << endl;
    cout << "borrowdBooks:";
    for (int i =0 ; i<borrowedBooks_names.size(); i++)
        cout << this->borrowedBooks_names[i] << " ";
    cout << endl;
    cout << "searchHisory:";
    for (int i =0 ; i<searchHistory_names.size(); i++)
        cout << this->searchHistory_names[i] << " ";
    cout << endl;
    cout << "favoriteBooks:";
    for (int i =0 ; i<favoriteBooks_names.size(); i++)
        cout << this->favoriteBooks_names[i] << " ";
    cout << endl;
    cout << "current:" << currentBook_name << " ,requested:" << requestedBook_name << endl;
}

void Student::setCurrentBook(string name)
{
    this->currentBook_name = name;
}

void Student::setRequestedBook(string name)
{
    this->requestedBook_name = name;
}

void Student::addBorrowedBooks(vector<string> x)
{
    for(int i =0; i<x.size();i++)
    this->borrowedBooks_names.push_back(x[i]);
}

string Student::getCurrentBookName()
{
    return this->currentBook_name;
}

vector<Book> Student::getCurrentBookVector(DataBase *db)
{
    vector<string> v= this->split_string(currentBook_name,",");
    vector<Book> vb;
    for(int i=0;i<v.size();i++)
        vb.push_back(db->loadBookByRowId(v[i]));
    return vb;
}

string Student::getRequestedBookName()
{
    return this->requestedBook_name;
}

vector<string> Student::getSearchHistory()
{
    return this->searchHistory_names;
}

vector<string> Student :: split_string(string s,string splitter)
{
    vector<string> splitted;
    int n = s.length();
    int pos = 0;
    int start = pos;
    while (pos != string::npos)
    {
        pos = s.find_first_of(splitter,pos+1);
        string splitted_string = s.substr(start,pos-start);
        splitted.push_back(splitted_string);
        start = pos+1;
    }

    return splitted;
}

#endif STUDENT
