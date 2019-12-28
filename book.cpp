#include "book.h"
#include "publisher.h"

Book::Book(string name, string Type, Publisher* author, string Rowid, int price, bool State , bool Availability)
{
    Name = name;
    type = Type;
    publisher = author ;
    Price = price ;
    state = State;
    availability = 1;
    rowid=Rowid;
}

Book::Book()
{

}

void Book::setName(string name)
{
    this->Name =  name;
}

void Book::setPrice(int price)
{
    this->Price = price;
}

void Book::setType(string Type)
{
    this->type = Type;
}

void Book::setPublisher(Publisher* myPublisher)
{
    this->publisher = myPublisher;
}

void Book::setPublisherName(string name)
{
    this->publisher_name = name;
}

void Book::setImagePath(string path)
{
    this->imagePath = path;
}

void Book::setState(bool State)
{
    this->state = State;
}

void Book::setAvailability(bool Availability)
{
    this->availability = Availability;
}

void Book::setBorrowedDate(int date)
{
    this->borrowedDate = date;
}

void Book::setExpectedReturnDate(int date)
{
    this->expectedReturnDate = date;
}

void Book::setActualReturnDate(int date)
{
    this->actualReturnDate = date ;
}

void Book::setRowId(string Rowid)
{
    this->rowid = Rowid;
}

string Book::getRowId()
{
    return this->rowid;
}

string Book::getName()
{
    return this->Name;
}

int Book::getPrice()
{
    return this->Price;
}

string Book::getType()
{
    return this->type;
}

Publisher* Book::getPublisher()
{
    return publisher;
}

string Book::getPublisherName()
{
    return this->publisher_name;
}

string Book::getImagePath()
{
    return this->imagePath;
}

bool Book::getState()
{
    return this->state;
}

bool Book::getAvailability()
{
    return this->availability;
}

int Book::getBorrowedDate()
{
    return this->borrowedDate;
}

int Book::getExpectedReturnDate()
{
    return this->expectedReturnDate;
}

int Book::getActualReturnDate()
{
    return this->actualReturnDate;
}

void Book::showInfo()
{
    cout << "Name:" << this->Name ;
    cout << endl;
    cout << "Price:" << this->Price;
    cout << endl;
    cout << "State:" << this->state;
    cout << endl;
    cout << "Type:" << this->type ;
    cout << endl;
    cout << "Publisher_name: " << this->publisher_name << endl;
}

bool Book::operator ==(Book &)
{

}
