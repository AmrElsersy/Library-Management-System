#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include "book.h"
#include <bits/stdc++.h>
#include "publisher.h"
#include "student.h"
#include "user.h"
#include "database.h"
#include "librarian.h"
#include <QObject>
#include "GUI/indexs.h"
#include <vector>
#include <string>
using namespace std;

class Controller : public QObject
{
    Q_OBJECT
private:
    DataBase db;
    vector<string> split_string(string,string);

public :
    Controller();
    void start();

    void studentLoggedIn(string);
    void publisherLoggedIn(string);

public slots:

    void log_in(string name , string password , int choice);
    void sign_up(string ,string ,string,int);
    // publisher
    void Upload_book(string ,string,string,int);
    void updatePublisher(string ,string,string,string,int);
    void updateStudent(string,string,string,string,int);

    // books
    void searchBookByName(string,string);
    void searchBookByType(string,string);
    void searchBookByPrice(int,string);
    void searchBookByPub(string,string);
    void borrowBook(string,string,int);
    void returnBook(string,string);
    void aa(string);
    void getBookInfo(string);
    void getSearchHistory(string);
    map<string,string> getAllBooks();


signals:
    void error(string);
    void error_login(string);
    void studentLoggedin(Student);
    void publisherLoggedin(Publisher);
    void setCurrentWidget(int index);

    // books
    void error_noBook(string);
    void bookInfo(Book);
    void error_return(string);
    void bookReturned(int,int);
    void borrowedBooks(vector<Book>);
    void booksFound(vector<Book>);
    void searchedBooks(vector<string>);

};

#endif // CONTROLLER_H
