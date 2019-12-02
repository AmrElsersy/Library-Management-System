#ifndef BOOK_H
#define BOOK_H

#include <bits/stdc++.h>
#include <iostream>
class Publisher;

using namespace std;

class Book
{
private:
    string rowid;
    string Name;
    int Price;
    bool state;
    string type;
    string imagePath;
    Publisher* publisher;
    bool availability;
    string publisher_name;

    int borrowedDate=0, expectedReturnDate=0, actualReturnDate=0 ;

public:
    Book();
    Book(string name , string type , Publisher* author , string Rowid ,int price = 0 , bool State = true, bool Availability = true);
    // ========= Setters ===========
    void setName(string);
    void setPrice(int);
    void setType(string);
    void setPublisher(Publisher*);
    void setPublisherName(string);
    void setImagePath(string);
    void setState(bool);
    void setAvailability(bool);
    void setBorrowedDate(int);
    void setExpectedReturnDate(int);
    void setActualReturnDate(int);
    void setRowId(string);
    // ========== Getters ===========
    string getRowId();
    string getName();
    int getPrice();
    string getType();
    Publisher* getPublisher();
    string getPublisherName();
    string getImagePath();
    bool getState();
    bool getAvailability();
    int getBorrowedDate();
    int getExpectedReturnDate();
    int getActualReturnDate();

    void showInfo();
    bool operator == (Book&);
};

#endif // BOOK_H
