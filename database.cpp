#include "database.h"
#include "book.h"
#include "publisher.h"
#include "student.h"

DataBase::DataBase()
{

}

void DataBase::init(QString path)
{
    this->db = QSqlDatabase ::addDatabase("QSQLITE");
    QString Path = path + "/../../Library-Management-System/ray2.db";
    Path.toStdString();

    this->db.setDatabaseName(Path);
    this->db.open();

    if (!this->db.isOpen())
        cout << "db doesn't open and you are not ray2" << endl;
}

bool DataBase::saveBook(Book book)
{
    QSqlQuery check(this->db);
    check.prepare("SELECT * FROM Books WHERE Name=?;");
    check.bindValue(0,QString::fromStdString(book.getName()));
    check.exec();
//    if(check.next())
//        return false;
    QSqlQuery query(this->db);
    query.prepare("INSERT INTO Books(Name,Type,Price,Publisher,borrowedDate,expectedReturnDate,actualReturnDate,State,Availability,imagePath) VALUES(?,?,?,?,?,?,?,?,?,?);");
    query.bindValue(0,QString::fromStdString(book.getName()));
    query.bindValue(1,QString::fromStdString(book.getType()));
    query.bindValue(2,book.getPrice());
    query.bindValue(3,QString::fromStdString(book.getPublisherName()));
    query.bindValue(4,book.getBorrowedDate());
    query.bindValue(5,book.getExpectedReturnDate());
    query.bindValue(6,book.getActualReturnDate());
    query.bindValue(7,book.getState());
    query.bindValue(8,book.getAvailability());
    query.bindValue(9,QString::fromStdString(book.getImagePath()));
    query.exec();
    return true;
}

bool DataBase::saveStudent(Student student)
{
    QSqlQuery check(this->db);
    check.prepare("SELECT * FROM Students WHERE Name=?;");
    check.bindValue(0,QString::fromStdString(student.getName()));
    check.exec();
    if(check.next())
        return false;
    QSqlQuery query(this->db);
    query.prepare("INSERT INTO Students(Name,Email,Password,cashAmount) VALUES(?,?,?,?);");
    query.bindValue(0,QString::fromStdString(student.getName()));
    query.bindValue(1,QString::fromStdString(student.getEmail()));
    query.bindValue(2,QString::fromStdString(student.getPassword()));
    query.bindValue(3,student.getCash());
    query.exec();
    return true;
}
bool DataBase::savePublisher(Publisher publisher)
{
    QSqlQuery check(this->db);
    check.prepare("SELECT * FROM Publishers WHERE Name=?;");
    check.bindValue(0,QString::fromStdString(publisher.getName()));
    check.exec();
    if(check.next())
        return false;
    QSqlQuery query(this->db);
    query.prepare("INSERT INTO Publishers(Name,Email,Password,cashAmount) VALUES(?,?,?,?);");
    query.bindValue(0,QString::fromStdString(publisher.getName()));
    query.bindValue(1,QString::fromStdString(publisher.getEmail()));
    query.bindValue(2,QString::fromStdString(publisher.getPassword()));
    query.bindValue(3,publisher.getCash());
    query.exec();
    return true;
}
void DataBase::updateStudent(Student student , string oldStuName)
{
    int x = student.getCash();

    QSqlQuery query(this->db);
    query.prepare("UPDATE Students SET Name=?,Email=?,Password=?,cashAmount=?,currentBook=?,requestedBook=? WHERE Name = ? ;");
    query.bindValue(0,QString::fromStdString(student.getName()));
    query.bindValue(1,QString::fromStdString(student.getEmail()));
    query.bindValue(2,QString::fromStdString(student.getPassword()));
    query.bindValue(3,student.getCash());
    query.bindValue(4,QString::fromStdString(student.getCurrentBookName()));
    query.bindValue(5,QString::fromStdString(student.getRequestedBookName()));
    query.bindValue(6,QString::fromStdString(oldStuName));
    query.exec();

}
void DataBase::updatePublisher(Publisher publisher, string old_name)
{
    QSqlQuery query(this->db);
    query.prepare("UPDATE Publishers SET Name=?,Email=?,Password=?,cashAmount=? WHERE Name = ? ;");
    query.bindValue(0,QString::fromStdString(publisher.getName()));
    query.bindValue(1,QString::fromStdString(publisher.getEmail()));
    query.bindValue(2,QString::fromStdString(publisher.getPassword()));
    query.bindValue(3,publisher.getCash());
    query.bindValue(4,QString::fromStdString(old_name));
    query.exec();
}
void DataBase::updateBook(Book book , string oldBookName)
{
    QSqlQuery query(this->db);
    query.prepare("UPDATE Books SET Name=?,Type=?,Price=?,Publisher=?,borrowedDate=?,expectedReturnDate=?,actualReturnDate=?,State=?,Availability=?,imagePath=? WHERE Name = ? ;");
    query.bindValue(0,QString::fromStdString(book.getName()));
    query.bindValue(1,QString::fromStdString(book.getType()));
    query.bindValue(2,book.getPrice());
    query.bindValue(3,QString::fromStdString(book.getPublisherName()));
    query.bindValue(4,book.getBorrowedDate());
    query.bindValue(5,book.getExpectedReturnDate());
    query.bindValue(6,book.getActualReturnDate());
    query.bindValue(7,book.getState());
    query.bindValue(8,book.getAvailability());
    query.bindValue(9,QString::fromStdString(book.getImagePath()));
    query.bindValue(10,QString::fromStdString(oldBookName));
    query.exec();
}

void DataBase::updateBookByRowId(Book book, string rowid)
{
    QSqlQuery query(this->db);
    query.prepare("UPDATE Books SET Name=?,Type=?,Price=?,Publisher=?,borrowedDate=?,expectedReturnDate=?,actualReturnDate=?,State=?,Availability=?,imagePath=? WHERE rowid = ? ;");
    query.bindValue(0,QString::fromStdString(book.getName()));
    query.bindValue(1,QString::fromStdString(book.getType()));
    query.bindValue(2,book.getPrice());
    query.bindValue(3,QString::fromStdString(book.getPublisherName()));
    query.bindValue(4,book.getBorrowedDate());
    query.bindValue(5,book.getExpectedReturnDate());
    query.bindValue(6,book.getActualReturnDate());
    query.bindValue(7,book.getState());
    query.bindValue(8,book.getAvailability());
    query.bindValue(9,QString::fromStdString(book.getImagePath()));
    query.bindValue(10,QString::fromStdString(rowid));
    query.exec();
}

Book DataBase::loadBook(string name)
{
    QSqlQuery query(this->db);
    query.prepare("SELECT Name,Type,Price,Publisher,borrowedDate,expectedReturnDate,actualReturnDate,State,Availability,imagePath,rowid FROM "
                  "Books WHERE Name=?;");
    query.bindValue(0,QString::fromStdString(name));
    query.exec();
    Book book;
    while(query.next())
    {
        int available = query.value(8).toInt();
        if (!available)
            continue;
        book.setAvailability(available);
        book.setName(query.value(0).toString().toStdString());
        book.setType(query.value(1).toString().toStdString());
        book.setPrice(stoi(query.value(2).toString().toStdString()));
        book.setPublisherName(query.value(3).toString().toStdString());
        book.setBorrowedDate(query.value(4).toInt());
        book.setExpectedReturnDate(query.value(5).toInt());
        book.setActualReturnDate(query.value(6).toInt());
        book.setState(query.value(7).toInt());
        book.setImagePath(query.value(9).toString().toStdString());
        book.setRowId(query.value(10).toString().toStdString());
        break;
    }
    return book;
}
Book DataBase::loadBookByRowId(string rowid)
{
    QSqlQuery query(this->db);
    query.prepare("SELECT Name,Type,Price,Publisher,borrowedDate,expectedReturnDate,actualReturnDate,State,Availability,imagePath,rowid FROM "
                  "Books WHERE rowid=?;");
    query.bindValue(0,QString::fromStdString(rowid));
    query.exec();
    Book book;
    while(query.next())
    {
        book.setName(query.value(0).toString().toStdString());
        book.setType(query.value(1).toString().toStdString());
        book.setPrice(stoi(query.value(2).toString().toStdString()));
        book.setPublisherName(query.value(3).toString().toStdString());
        book.setBorrowedDate(query.value(4).toInt());
        book.setExpectedReturnDate(query.value(5).toInt());
        book.setActualReturnDate(query.value(6).toInt());
        book.setState(query.value(7).toInt());
        book.setAvailability(query.value(8).toInt());
        book.setImagePath(query.value(9).toString().toStdString());
        book.setRowId(query.value(10).toString().toStdString());
    }
    return book;
}
Book DataBase::loadBookForce(string name)
{
    QSqlQuery query(this->db);
    query.prepare("SELECT Name,Type,Price,Publisher,borrowedDate,expectedReturnDate,actualReturnDate,State,Availability,imagePath,rowid FROM "
                  "Books WHERE Name=?;");
    query.bindValue(0,QString::fromStdString(name));
    query.exec();
    Book book;
    while(query.next())
    {
        book.setName(query.value(0).toString().toStdString());
        book.setType(query.value(1).toString().toStdString());
        book.setPrice(stoi(query.value(2).toString().toStdString()));
        book.setPublisherName(query.value(3).toString().toStdString());
        book.setBorrowedDate(query.value(4).toInt());
        book.setExpectedReturnDate(query.value(5).toInt());
        book.setActualReturnDate(query.value(6).toInt());
        book.setState(query.value(7).toInt());
        book.setAvailability(query.value(8).toInt());
        book.setImagePath(query.value(9).toString().toStdString());
        book.setRowId(query.value(10).toString().toStdString());
        break;
    }
    return book;
}
Student DataBase::loadStudent(string name)
{
    QSqlQuery query(this->db);
    query.prepare("SELECT Name,Email,Password,cashAmount,currentBook,requestedBook,borrowedBooks,searchHistory,favoriteBooks FROM Students WHERE Name=?;");
    query.bindValue(0,QString::fromStdString(name));
    query.exec();
    Student student;
    while(query.next())
    {
        student.setName(query.value(0).toString().toStdString());
        student.setEmail(query.value(1).toString().toStdString());
        student.setPassword(query.value(2).toString().toStdString());
        student.setCash(stoi(query.value(3).toString().toStdString()));
        student.setCurrentBook(query.value(4).toString().toStdString());
        student.setRequestedBook(query.value(5).toString().toStdString());
        student.addBorrowedBooks(split_string(query.value(6).toString().toStdString(),","));
        student.addSearchHistory(split_string(query.value(7).toString().toStdString(),","));
        student.addFavoriteBooks(split_string(query.value(8).toString().toStdString(),","));
    }
    return student;
}
Publisher DataBase::loadPublisher(string name)
{
    QSqlQuery query(this->db);
    query.prepare("SELECT Name,Email,Password,cashAmount,my_books FROM Publishers WHERE Name=?;");
    query.bindValue(0,QString::fromStdString(name));
    query.exec();
    Publisher publisher;
    while(query.next())
    {
        publisher.setName(query.value(0).toString().toStdString());
        publisher.setEmail(query.value(1).toString().toStdString());
        publisher.setPassword(query.value(2).toString().toStdString());
        publisher.setCash(stoi(query.value(3).toString().toStdString()));
        // my_books
        vector<string> BooksNames = split_string(query.value(4).toString().toStdString(),",");
        for (int i =0 ; i< BooksNames.size(); i++)
            publisher.addBook(BooksNames[i]);
    }
    return publisher;
}

int DataBase::checkStudent(string name, string password)// 0:name,password are correct | 1:name wrong | 2:name correct & password wrong
{
    int mode=0;
    QSqlQuery query(this->db);
    query.prepare("SELECT Name,Password FROM Students where Name = ? ;");
    query.bindValue(0,QString::fromStdString(name));
    query.exec();
    string namee,pass;
    while(query.next())
    {
        namee = query.value(0).toString().toStdString();
        pass = query.value(1).toString().toStdString();
    }
    if(namee.empty())mode=1;
    else {if(pass!=password)mode=2;}
    return mode;
}
int DataBase::checkPublisher(string name, string password)
{
    int mode=0;
    QSqlQuery query(this->db);
    query.prepare("SELECT Name,Password FROM Publishers where Name = ? ;");
    query.bindValue(0,QString::fromStdString(name));
    query.exec();
    string namee,pass;
    while(query.next())
    {
        namee = query.value(0).toString().toStdString();
        pass = query.value(1).toString().toStdString();
    }
    if(namee.empty())mode=1;
    else {if(pass!=password)mode=2;}
    return mode;
}

void DataBase::addPublisherBooks(Book book,string pubName)
{
    QSqlQuery query(this->db);
    query.prepare("SELECT my_books FROM Publishers WHERE Name=?;");
    query.bindValue(0,QString::fromStdString(pubName));
    query.exec();
    string pubBooks;
    while(query.next())
       pubBooks = query.value(0).toString().toStdString();
    pubBooks += "," + book.getName();
    query.prepare("UPDATE Publishers SET my_books=? WHERE Name=?;");
    query.bindValue(0,QString::fromStdString(pubBooks));
    query.bindValue(1,QString::fromStdString(pubName));
    query.exec();
}
void DataBase::addPublisherCash(int price , string pubName)
{
    QSqlQuery query(this->db);
    query.prepare("SELECT cashAmount FROM Publishers WHERE Name=?;");
    query.bindValue(0,QString::fromStdString(pubName));
    query.exec();
    int cashAmount=0;
    while(query.next())
       cashAmount = query.value(0).toInt();
    cashAmount += price;
    query.prepare("UPDATE Publishers SET cashAmount=? WHERE Name=?;");
    query.bindValue(0,cashAmount);
    query.bindValue(1,QString::fromStdString(pubName));
    query.exec();
}
void DataBase::addCurrentBooks(Book book, string stuName)
{
    QSqlQuery query(this->db);
    query.prepare("SELECT currentBook FROM Students WHERE Name=?;");
    query.bindValue(0,QString::fromStdString(stuName));
    query.exec();
    string currentBooks,currentBooksUnique="";
    while(query.next())
       currentBooks = query.value(0).toString().toStdString();
    currentBooks += "," + book.getRowId();
    vector<string> vec = split_string(currentBooks,",");
    sort( vec.begin(), vec.end() );
    vec.erase( unique( vec.begin(),vec.end() ), vec.end() );
    for(int i=0;i<vec.size();i++)
        currentBooksUnique+=vec[i]+",";
    currentBooksUnique = currentBooksUnique.substr(0, currentBooksUnique.size()-1);
    if(currentBooksUnique[0]==',')currentBooksUnique = currentBooksUnique.substr(1, currentBooksUnique.size());
    query.prepare("UPDATE Students SET currentBook=? WHERE Name=?;");
    query.bindValue(0,QString::fromStdString(currentBooksUnique));
    query.bindValue(1,QString::fromStdString(stuName));
    query.exec();
}

void DataBase::addSearchHistory(Book book , string stuName)
{
    QSqlQuery query(this->db);
    query.prepare("SELECT searchHistory FROM Students WHERE Name=?;");
    query.bindValue(0,QString::fromStdString(stuName));
    query.exec();
    string searchBooks,searchBooksUnique="";
    while(query.next())
       searchBooks = query.value(0).toString().toStdString();
    searchBooks += "," + book.getName();
    vector<string> vec = split_string(searchBooks,",");
    sort( vec.begin(), vec.end() );
    vec.erase( unique( vec.begin(),vec.end() ), vec.end() );
    for(int i=0;i<vec.size();i++)
        searchBooksUnique+=vec[i]+",";
    searchBooksUnique = searchBooksUnique.substr(0, searchBooksUnique.size()-1);
    if(searchBooksUnique[0]==',')searchBooksUnique = searchBooksUnique.substr(1, searchBooksUnique.size());
    query.prepare("UPDATE Students SET searchHistory=? WHERE Name=?;");
    query.bindValue(0,QString::fromStdString(searchBooksUnique));
    query.bindValue(1,QString::fromStdString(stuName));
    query.exec();
}
void DataBase::addBorrowedBooks(Book book, string stuName)
{
    QSqlQuery query(this->db);
    query.prepare("SELECT borrowedBooks FROM Students WHERE Name=?;");
    query.bindValue(0,QString::fromStdString(stuName));
    query.exec();
    string borrowedBooks,borrowedBooksUnique="";
    while(query.next())
       borrowedBooks = query.value(0).toString().toStdString();
    borrowedBooks += "," + book.getName();
    vector<string> vec = split_string(borrowedBooks,",");
    sort( vec.begin(), vec.end() );
    vec.erase( unique( vec.begin(),vec.end() ), vec.end() );
    for(int i=0;i<vec.size();i++)
        borrowedBooksUnique+=vec[i]+",";
    borrowedBooksUnique = borrowedBooksUnique.substr(0, borrowedBooksUnique.size()-1);
    if(borrowedBooksUnique[0]==',')borrowedBooksUnique = borrowedBooksUnique.substr(1, borrowedBooksUnique.size());
    query.prepare("UPDATE Students SET borrowedBooks=? WHERE Name=?;");
    query.bindValue(0,QString::fromStdString(borrowedBooksUnique));
    query.bindValue(1,QString::fromStdString(stuName));
    query.exec();
}
void DataBase::addFavoriteBooks(Book book, string stuName)
{
    QSqlQuery query(this->db);
    query.prepare("SELECT favoriteBooks FROM Students WHERE Name=?;");
    query.bindValue(0,QString::fromStdString(stuName));
    query.exec();
    string favoriteBooks,favoriteBooksUnique="";
    while(query.next())
       favoriteBooks = query.value(0).toString().toStdString();
    favoriteBooks += "," + book.getName();
    vector<string> vec = split_string(favoriteBooks,",");
    sort( vec.begin(), vec.end() );
    vec.erase( unique( vec.begin(),vec.end() ), vec.end() );
    for(int i=0;i<vec.size();i++)
        favoriteBooksUnique+=vec[i]+",";
    favoriteBooksUnique = favoriteBooksUnique.substr(0, favoriteBooksUnique.size()-1);
    if(favoriteBooksUnique[0]==',')favoriteBooksUnique = favoriteBooksUnique.substr(1, favoriteBooksUnique.size());
    query.prepare("UPDATE Students SET favoriteBooks=? WHERE Name=?;");
    query.bindValue(0,QString::fromStdString(favoriteBooksUnique));
    query.bindValue(1,QString::fromStdString(stuName));
    query.exec();
}


vector<Book> DataBase::searchBookByType(string type)
{
    QSqlQuery query(this->db);
    query.prepare("SELECT Name FROM Books where Type = ? ;");
    query.bindValue(0,QString::fromStdString(type));
    query.exec();
    vector<Book> v;
    vector<string> ss;
    while(query.next())
        ss.push_back(query.value(0).toString().toStdString());
    for(int i=0 ; i<ss.size();i++)
        v.push_back(this->loadBookForce(ss[i]));
    return v;
}
vector<Book> DataBase::searchBookByPrice(int price)
{
    QSqlQuery query(this->db);
    query.prepare("SELECT Name FROM Books where Price <= ? ;");
    query.bindValue(0,price);
    query.exec();
    vector<Book> v;
    vector<string> ss;
    while(query.next())
        ss.push_back(query.value(0).toString().toStdString());
    for(int i=0 ; i<ss.size();i++)
        v.push_back(this->loadBookForce(ss[i]));
    return v;
}
vector<Book> DataBase::searchBookByPubName(string pubName)
{
    QSqlQuery query(this->db);
    query.prepare("SELECT Name FROM Books where Publisher = ? ;");
    query.bindValue(0,QString::fromStdString(pubName));
    query.exec();
    vector<Book> v;
    vector<string> ss;
    while(query.next())
        ss.push_back(query.value(0).toString().toStdString());
    for(int i=0 ; i<ss.size();i++)
        v.push_back(this->loadBookForce(ss[i]));
    return v;
}

map<string,string> DataBase::getAllBooks()
{
    QSqlQuery query(this->db);
    query.prepare("SELECT Name,imagePath FROM Books;");
    query.exec();
    map<string,string> name_imagePath ;
    while(query.next())
    {
        string name  = query.value(0).toString().toStdString() ;
        string imagePath = query.value(1).toString().toStdString();
        name_imagePath[name] = imagePath;
    }
    return name_imagePath;

}


vector<string> DataBase :: split_string(string s,string splitter)
{
    vector<string> splitted;
    uint n = s.length();
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
