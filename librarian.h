#ifndef LIBRARIAN_H
#define LIBRARIAN_H

#include <bits/stdc++.h>
#include "user.h"
#include "book.h"
#include "database.h"
#include "student.h"
//#include <QObject>

using namespace std;

class Librarian//: public QObject
{
 //   Q_OBJECT
private:
    int flag,bookState;
signals:
    void librarianWidgetOpen();
public:
    Librarian();
    Librarian(string name , string password,string email);
    bool checkState(Book*);
    Book supplyRequestedBook(string,DataBase*);

public slots:
    void libBookState(int);
};


#endif // LIBRARIAN_H
