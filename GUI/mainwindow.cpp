#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    this->stackWidget =new QStackedWidget();
    this->controller = new Controller();
    this->librarian = new Librarian();
    this->studentWidget = new StudentWidget();
    this->startWidget = new StartWidget();
    this->signUpWidget = new SignUp();
    this->logInWidget = new LogInWidget();
    this->publisherWidget = new PublisherWidget();
    this->bookWidget = new BookWidget();

    this->Design();
    this->Signals_Slots();

    this->setCentralWidget(this->stackWidget);
    this->stackWidget->setCurrentIndex(0);
}

void MainWindow::Design()
{
    this->stackWidget->addWidget(this->startWidget);
    this->stackWidget->addWidget(this->signUpWidget);
    this->stackWidget->addWidget(this->logInWidget);
    this->stackWidget->addWidget(this->publisherWidget);
    this->stackWidget->addWidget(this->studentWidget);
//    this->stackWidget->addWidget(this->bookWidget);
}

void MainWindow::Signals_Slots()
{
    connect(this->signUpWidget,SIGNAL(signUpData(string,string,string,int)),this->controller,SLOT(sign_up(string,string,string,int)));
    connect(this->controller,SIGNAL(error(string)),this->signUpWidget,SLOT(error(string)));
    connect(this->signUpWidget,SIGNAL(setCurrentWidget(int)),this,SLOT(changeCurrentWidget(int)));
    connect(this->startWidget,SIGNAL(setCurrentWidget(int)),this,SLOT(changeCurrentWidget(int)));

    connect(this->logInWidget,SIGNAL(LogInWidgetData(string,string,int)),this->controller,SLOT(log_in(string,string,int)));
    connect(this->logInWidget,SIGNAL(setCurrentWidget(int)),this,SLOT(changeCurrentWidget(int)));
    connect(this->controller,SIGNAL(error_login(string)),this->logInWidget,SLOT(error(string)));

    connect(this->controller,SIGNAL(studentLoggedin(Student)),this->studentWidget,SLOT(studentLoggedIn(Student)));
    connect(this->studentWidget,SIGNAL(updateStudent(string,string,string,string,int)),this->controller,SLOT(updateStudent(string,string,string,string,int)));

    connect(this->controller,SIGNAL(setCurrentWidget(int)),this,SLOT(changeCurrentWidget(int)));
    connect(this->controller,SIGNAL(publisherLoggedin(Publisher)),this->publisherWidget,SLOT(publisherLoggedIn(Publisher)));
    connect(this->publisherWidget,SIGNAL(setCurrentWidget(int)),this,SLOT(changeCurrentWidget(int)));
    connect(this->publisherWidget,SIGNAL(addBookData(string,string,string,int)),this->controller,SLOT(Upload_book(string,string,string,int)));
    connect(this->publisherWidget,SIGNAL(updatePublisher(string,string,string,string,int)),this->controller,SLOT(updatePublisher(string ,string,string,string,int)));

    // Books
    connect(this->controller,SIGNAL(bookInfo(Book)),this->bookWidget,SLOT(bookInfo(Book)));
    connect(this->bookWidget,SIGNAL(setCurrentWidget(int)),this,SLOT(changeCurrentWidget(int)));
    connect(this->bookWidget,SIGNAL(borrowBook(string,string,int)),this->controller,SLOT(borrowBook(string,string,int)));
    connect(this->controller,SIGNAL(error_noBook(string)),this->bookWidget,SLOT(error(string)));
    connect(this->studentWidget,SIGNAL(getBookInfo(string)),this->controller,SLOT(getBookInfo(string)));

    connect(this->studentWidget,SIGNAL(returnBook(string,string)),this->controller,SLOT(returnBook(string,string)));
    connect(this->controller,SIGNAL(error_return(string)),this->studentWidget,SLOT(error_return(string)));
    connect(this->controller,SIGNAL(bookReturned(int,int)),this->studentWidget,SLOT(bookReturned(int,int)));
    connect(this->studentWidget,SIGNAL(aa(string)),this->controller,SLOT(aa(string)));
    connect(this->controller,SIGNAL(borrowedBooks(vector<Book>)),this->studentWidget,SLOT(borrowedBooks(vector<Book>)));
    connect(this->studentWidget,SIGNAL(searchBookByName(string,string)),this->controller,SLOT(searchBookByName(string,string)));
    connect(this->studentWidget,SIGNAL(searchBookByType(string,string)),this->controller,SLOT(searchBookByType(string,string)));
    connect(this->studentWidget,SIGNAL(searchBookByPrice(int,string)),this->controller,SLOT(searchBookByPrice(int,string)));
    connect(this->studentWidget,SIGNAL(searchBookByPub(string,string)),this->controller,SLOT(searchBookByPub(string,string)));
    connect(this->controller,SIGNAL(booksFound(vector<Book>)),this->studentWidget,SLOT(booksFound(vector<Book>)));
    connect(this->studentWidget,SIGNAL(getSearchHistory(string)),this->controller,SLOT(getSearchHistory(string)));
    connect(this->controller,SIGNAL(searchedBooks(vector<string>)),this->studentWidget,SLOT(searchedBooks(vector<string>)));
    connect(this->studentWidget,SIGNAL(setCurrentWidget(int)),this,SLOT(changeCurrentWidget(int)));

    //librarian
    //connect(this->librarian,SIGNAL(librarianWidgetOpen()),this->studentWidget,SLOT(librarianWidgetOpen()));
    //connect(this->studentWidget,SIGNAL(libBookState(int)),this->librarian,SLOT(libBookState(int)));

}


void MainWindow::changeCurrentWidget(int index)
{
    this->stackWidget->setCurrentIndex(index);
}

