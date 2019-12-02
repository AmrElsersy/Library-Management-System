#ifndef LIBRARIAN
#define LIBRARIAN

#include "librarian.h"

Librarian::Librarian() //: public QObject
{

}

Librarian::Librarian(string name, string password, string email)
{

}

bool Librarian::checkState(Book *b)
{
    cout<<"Ya librarian, enter the book state elly enta shayefha: 1 for bad , 0 for good"<<endl;
    //emit librarianWidgetOpen();
    //while (flag==0) {}
    //b->setState(bookState);
    //return bookState;
    return 1;
}

Book Librarian::supplyRequestedBook(string stuName, DataBase* db)
{
    Book b;string type;int price;
    Student s= db->loadStudent(stuName);
    string bookName = s.getRequestedBookName();
    b.setName(bookName);
    cout<<"Ya librarian bsha, enter book's type : "<<endl;
    cin>>type;b.setType(type);
    cout<<"w ma3lesh kman, enter book's price : "<<endl;
    cin>>price;b.setPrice(price);
    b.setPublisherName("OUTSIDE");
    db->saveBook(b);
    s.setRequestedBook("");
    db->updateStudent(s,s.getName());
}

void Librarian::libBookState(int libBookState)
{
    flag=1;
    bookState = libBookState;
}


#endif LIBRARIAN
