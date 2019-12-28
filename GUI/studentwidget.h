#ifndef STUDENTWIDGET_H
#define STUDENTWIDGET_H
#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTabBar>
#include <QTabWidget>
#include <QToolBar>
#include <QToolButton>
#include <QLineEdit>
#include <QPushButton>
#include <QSize>
#include <QColor>
#include <QCoreApplication>
#include <QString>
#include "indexs.h"
#include <QScrollArea>
#include "student.h"
#include <vector>
#include <QLabel>
#include "book.h"
#include "bookwidget.h"
#include <string>
#include <QTreeWidget>
#include <QTabWidget>
#include <cstdlib>
#include <iostream>
#include "GUI/imagewidget.h"
#include <vector>
#include <QFrame>
using namespace std;

class StudentWidget : public QWidget
{
    Q_OBJECT
private:
    QGridLayout* grid;
    QLineEdit* searchLineEdit;
    QToolBar* toolBar;
    QWidget* viewBooksWidget;
    QScrollArea* viewBooksScroll;
    QGridLayout* viewBooksLayout;
    std::vector<imageWidget*> books;
    uint row ;
    uint colomn;



    QWidget* ProfileWidget;
    QGridLayout* ProfileLayout;
    QLineEdit* nameEdit ,*passEdit , * emailEdit ,* cashEdit ;
    QPushButton *EditBtn , *OkBtn;

    QWidget* ReturnWidget;
    QGridLayout* ReturnLayout;
    QLineEdit* ReturnBook;
    QPushButton *BackBtn , *OkkBtn;

    QWidget* BorrowedWidget;
    QTreeWidget *borrowedList;
    QPushButton *Ok1Btn;
    void addRoot(string,string,string,string);

    QWidget* SearchWidget;
    QVBoxLayout* SearchLayout;
    QLineEdit* SearchBook;
    QPushButton *NameBtn,*TypeBtn,*PriceBtn,*PubBtn,*DoneBtn;

    QWidget* HistoryWidget;
    QTreeWidget *HistoryList;
    QPushButton *OkBtnh;
    void addRoot(string);

    Student currentStudent;
    QSize lastSize;
    vector<QWidget*> BooksWidgets;
    QString Path;

    QPushButton* increaseTime;
    QLabel* today,*todayIs;
    QMessageBox* errorBox;
    QMessageBox* successBox;

    QTabWidget *tabWidget;

    QWidget* librarianWidget;
    QVBoxLayout* librarianLayout;
    QLabel* libLabel;
    QLineEdit* bookState;
    QPushButton *Ok2Btn;

public:
    StudentWidget(QWidget* parent = nullptr);
    void initToolBar();
    void initProfileWidget();
    void initReturnWidget();
    void initBorrowedWidget();
    void initSearchWidget();
    void initHistoryWidget();
    void initLibrarianWidget();
    void Design();
    void Signals_Slots();
    void UpdateBooks();

signals:
    void updateStudent(string,string,string,string,int);
    void getBookInfo(string);
    void getBookInfo(Book);
    void returnBook(string,string);
    void aa(string);
    void searchBookByName(string,string);
    void searchBookByType(string,string);
    void searchBookByPrice(int,string);
    void searchBookByPub(string,string);
    void getSearchHistory(string);
    void setCurrentWidget(int);
    void setLoggedInUserName(string);
    map<string, string> getAllBooks();
//    void libBookState(int);

public slots:
    void studentLoggedIn(Student);
    void ButtonClicked(QAction *action);
    void editButtonClicked();
    void okButtonClicked();
    void backButtonClicked();
    void okkButtonClicked();
    void increaseIsClicked();
    void error_return(string);
    void bookReturned(int,int);
    void borrowedBooks(vector<Book>);
    void ok1ButtonClicked();
    void okButtonhClicked();
    void nameButtonClicked();
    void typeButtonClicked();
    void priceButtonClicked();
    void pubButtonClicked();
    void doneButtonClicked();
    void booksFound(vector<Book>);
    void searchedBooks(vector<string>);
    void bookClicked(string name);
//    void librarianWidgetOpen();
//    void Ok2ButtonClicked();

};

#endif // STUDENTWIDGET_H
