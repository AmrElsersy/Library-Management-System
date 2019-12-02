#include "studentwidget.h"

extern int todayDate;
Book b;

StudentWidget::StudentWidget(QWidget *parent) : QWidget(parent)
{b.setPrice(10);
    this->Path = QCoreApplication::applicationDirPath();
    //this->bookWidget= new BookWidget();
    this->grid = new QGridLayout();
    this->toolBar = new QToolBar();
    this->searchLineEdit = new QLineEdit();
    this->viewBooksScroll = new QScrollArea();
    this->viewBooksWidget = new QWidget();
    this->viewBooksLayout = new QGridLayout();
    this->lastSize.setWidth(0);
    this->lastSize.setHeight(0);

    // ems7
    QWidget* w1 = new QWidget; w1->setStyleSheet("background-color:green");
    QWidget* w2 = new QWidget; w2->setStyleSheet("background-color:black");
    QWidget* w3 = new QWidget; w3->setStyleSheet("background-color:white");
    this->BooksWidgets.push_back(w1);
    this->BooksWidgets.push_back(w2);
    this->BooksWidgets.push_back(w3);
    this->UpdateBooks();

    //today   to be designed
    this->increaseTime = new QPushButton("Add day");
    this->today = new QLabel();
    this->todayIs = new QLabel("Today is : ");
    this->today->setText(QString::fromStdString(to_string(todayDate)));

    this->errorBox = new QMessageBox();

    this->tabWidget = new QTabWidget();

    this->initProfileWidget();
    this->initReturnWidget();
    this->initBorrowedWidget();
    this->initSearchWidget();
    this->initHistoryWidget();
    this->initLibrarianWidget();
    this->initToolBar();
    this->Design();
    this->Signals_Slots();
}

void StudentWidget::initToolBar()
{
    this->toolBar->setMovable(false);
    this->toolBar->setIconSize(QSize(50,50));
    this->toolBar->setOrientation(Qt::Vertical);
    this->toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    QIcon Profile(this->Path + "/../../Library-Management-System/icons/profile.png"); QString ProfileText = "Profile";
    QIcon Search(this->Path + "/../../Library-Management-System/icons/search.png"); QString SearchText = "Search";
    QIcon favorite(this->Path + "/../../Library-Management-System/icons/favorite1.png"); QString favoriteText = "Expected";
    QIcon Borrowed(this->Path + "/../../Library-Management-System/icons/book1.png"); QString BorrowedText = "Borrow";
    QIcon History(this->Path + "/../../Library-Management-System/icons/history.png"); QString HistoryText = "History";
    QIcon Return(this->Path + "/../../Library-Management-System/icons/return.png"); QString ReturnText = "Return";
    QIcon LogOut(this->Path + "/../../Library-Management-System/icons/logout.png"); QString LogOutText = "Log Out";

    this->toolBar->addAction(Profile,ProfileText);
    this->toolBar->addAction(Search,SearchText);
    this->toolBar->addAction(favorite,favoriteText);
    this->toolBar->addAction(Borrowed,BorrowedText);
    this->toolBar->addAction(History,HistoryText);
    this->toolBar->addAction(Return,ReturnText);
    this->toolBar->addAction(LogOut,LogOutText);

    this->toolBar->setStyleSheet("QToolBar{background-color: #01333e; color: white;}"
                                 "QToolButton:hover{background-color:rgb(220,220,220); color: black;}"
                                 "QToolButton:select{background-color:white; color: black;}"
                                 "QToolButton:font-weight:5px;"
                                 "QToolButton:font-size :50 px;"
                                 );

}

void StudentWidget::initProfileWidget()
{
    this->ProfileWidget = new QWidget();
    this->ProfileLayout = new QGridLayout();

    QLabel* name = new QLabel("Name:");             this->nameEdit = new QLineEdit(); nameEdit->setReadOnly(true);
    QLabel* password = new QLabel("Password:");     this->passEdit = new QLineEdit(); passEdit->setReadOnly(true);
    QLabel* email = new QLabel("Email:");           this->emailEdit = new QLineEdit();emailEdit->setReadOnly(true);
    QLabel* cashAmount = new QLabel("Cash Amount:");this->cashEdit = new QLineEdit(); cashEdit->setReadOnly(true);

    this->EditBtn = new QPushButton("Edit");
    this->OkBtn = new QPushButton("Ok");

    this->ProfileLayout->addWidget(name,0,0,Qt::AlignLeft);
    this->ProfileLayout->addWidget(nameEdit,0,1);

    this->ProfileLayout->addWidget(password,1,0,Qt::AlignLeft);
    this->ProfileLayout->addWidget(passEdit,1,1);

    this->ProfileLayout->addWidget(email,2,0,Qt::AlignLeft);
    this->ProfileLayout->addWidget(emailEdit,2,1);

    this->ProfileLayout->addWidget(cashAmount,3,0,Qt::AlignLeft);
    this->ProfileLayout->addWidget(cashEdit,3,1);

    QHBoxLayout* verticlaLayout = new QHBoxLayout;
    verticlaLayout->addWidget(this->EditBtn);
    verticlaLayout->addWidget(this->OkBtn);
    this->ProfileLayout->addLayout(verticlaLayout,4,0,1,-1);

    this->ProfileWidget->setLayout(this->ProfileLayout);
}
void StudentWidget::initReturnWidget()
{
    this->ReturnWidget = new QWidget();
    this->ReturnLayout = new QGridLayout();

    QLabel* enterBook = new QLabel("Enter return book :");
    this->ReturnBook = new QLineEdit();

    this->BackBtn = new QPushButton("<<Back");
    this->OkkBtn = new QPushButton("Ok");

    this->ReturnLayout->addWidget(enterBook,0,0,Qt::AlignLeft);
    this->ReturnLayout->addWidget(ReturnBook,0,1);

    QHBoxLayout* verticlaLayout = new QHBoxLayout;
    verticlaLayout->addWidget(this->BackBtn);
    verticlaLayout->addWidget(this->OkkBtn);
    this->ReturnLayout->addLayout(verticlaLayout,2,0,1,-1);

    this->ReturnWidget->setLayout(this->ReturnLayout);
}
void StudentWidget::initBorrowedWidget()
{
    this->BorrowedWidget = new QWidget();
    this->borrowedList = new QTreeWidget();
    this->Ok1Btn = new QPushButton("Ok");
    this->BorrowedWidget->setMinimumSize(600,150);

    QStringList headerLabels;
    headerLabels.push_back(tr("Borrowed Book"));
    headerLabels.push_back(tr("Borrowed Date"));
    headerLabels.push_back(tr("Expected Return Date"));
    headerLabels.push_back(tr("Expected Bill"));
    this->borrowedList->setColumnCount(headerLabels.count());
    this->borrowedList->setHeaderLabels(headerLabels);

    this->borrowedList->setColumnWidth(0,150);
    this->borrowedList->setColumnWidth(1,150);
    this->borrowedList->setColumnWidth(2,150);
    this->borrowedList->setColumnWidth(3,100);

    QVBoxLayout* verticlaLayout = new QVBoxLayout;
    verticlaLayout->addWidget(this->borrowedList);
    verticlaLayout->addWidget(this->Ok1Btn);
    this->BorrowedWidget->setLayout(verticlaLayout);
}
void StudentWidget::initSearchWidget()
{
    this->SearchWidget = new QWidget();
    this->SearchLayout = new QVBoxLayout();
    this->SearchBook = new QLineEdit();
    QLabel *lbl = new QLabel("You want to search by :");
    this->NameBtn = new QPushButton("Name");
    this->TypeBtn = new QPushButton("Type");
    this->PriceBtn = new QPushButton("Price");
    this->PubBtn = new QPushButton("Publisher");
    this->DoneBtn = new QPushButton("Done");

    this->SearchLayout->addWidget(lbl);
    this->SearchLayout->addWidget(NameBtn);
    this->SearchLayout->addWidget(TypeBtn);
    this->SearchLayout->addWidget(PriceBtn);
    this->SearchLayout->addWidget(PubBtn);
    this->SearchLayout->addWidget(SearchBook);
    this->SearchLayout->addWidget(DoneBtn);
    this->SearchWidget->setLayout(this->SearchLayout);
}
void StudentWidget::initHistoryWidget()
{
    this->HistoryWidget = new QWidget();
    this->HistoryList = new QTreeWidget();
    this->OkBtnh = new QPushButton("Ok");
    this->HistoryWidget->setMinimumSize(600,150);

    QStringList headerLabels;
    headerLabels.push_back(tr("Searched Book"));
    this->HistoryList->setColumnCount(headerLabels.count());
    this->HistoryList->setHeaderLabels(headerLabels);

    QVBoxLayout* verticlaLayout = new QVBoxLayout;
    verticlaLayout->addWidget(this->HistoryList);
    verticlaLayout->addWidget(this->OkBtnh);
    this->HistoryWidget->setLayout(verticlaLayout);
}

void StudentWidget::initLibrarianWidget()
{
    this->librarianWidget = new QWidget();
    this->librarianWidget->setWindowTitle("Librarian");
    this->librarianWidget->move(600,0);
    this->librarianLayout = new QVBoxLayout();
    this->libLabel = new QLabel("Enter Book State :");
    this->bookState = new QLineEdit();
    this->Ok2Btn = new QPushButton("Ok");

    this->librarianLayout->addWidget(libLabel);
    this->librarianLayout->addWidget(bookState);
    this->librarianLayout->addWidget(Ok2Btn);

    this->librarianWidget->setLayout(librarianLayout);
}

void StudentWidget::Design()
{
    // make the Books Widget Scrollable
    this->viewBooksScroll->setWidget(this->viewBooksWidget);
    this->viewBooksScroll->setWidgetResizable(true);
    this->viewBooksScroll->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->viewBooksScroll->setStyleSheet("background-color:red");
    this->viewBooksScroll->setLayout(this->viewBooksLayout);

    // grid Design
    this->grid->addWidget(this->toolBar,0,0,-1,1);
    this->grid->addWidget(this->searchLineEdit,0,1,1,2,Qt::AlignTop);
    this->grid->addWidget(this->viewBooksScroll,1,1);
    this->grid->addWidget(this->increaseTime,2,1);
    this->grid->addWidget(this->todayIs,3,1);
    this->grid->addWidget(this->today,4,1);

    //
    this->setMinimumSize(MIN_SIZE);
    this->setLayout(this->grid);
}

void StudentWidget::Signals_Slots()
{
    connect(this->toolBar,SIGNAL(actionTriggered(QAction*)),this,SLOT(ButtonClicked(QAction*)));
    connect(this->increaseTime,SIGNAL(clicked()),this,SLOT(increaseIsClicked()));
    connect(this->EditBtn,SIGNAL(clicked()),this,SLOT(editButtonClicked()));
    connect(this->OkBtn,SIGNAL(clicked()),this,SLOT(okButtonClicked()));
    connect(this->BackBtn,SIGNAL(clicked()),this,SLOT(backButtonClicked()));
    connect(this->OkkBtn,SIGNAL(clicked()),this,SLOT(okkButtonClicked()));
    connect(this->Ok1Btn,SIGNAL(clicked()),this,SLOT(ok1ButtonClicked()));
    connect(this->OkBtnh,SIGNAL(clicked()),this,SLOT(okButtonhClicked()));
    connect(this->NameBtn,SIGNAL(clicked()),this,SLOT(nameButtonClicked()));
    connect(this->TypeBtn,SIGNAL(clicked()),this,SLOT(typeButtonClicked()));
    connect(this->PriceBtn,SIGNAL(clicked()),this,SLOT(priceButtonClicked()));
    connect(this->PubBtn,SIGNAL(clicked()),this,SLOT(pubButtonClicked()));
    connect(this->DoneBtn,SIGNAL(clicked()),this,SLOT(doneButtonClicked()));
    connect(this->Ok2Btn,SIGNAL(clicked()),this,SLOT(Ok2ButtonClicked()));

}

void StudentWidget::UpdateBooks()
{
    // clear the screen w ebtdy 3la ndafa
//    for(uint i =0; i < BooksWidgets.size() ; i++)
//        this->viewBooksLayout->removeWidget(this->BooksWidgets[i]);

    for (int i =0 ;i < this->BooksWidgets.size() ;i++)
    {
        this->viewBooksLayout->addWidget(BooksWidgets[i]);
    }
}

void StudentWidget::studentLoggedIn(Student student)
{
    this->currentStudent = student;
    this->nameEdit->setText(QString::fromStdString(this->currentStudent.getName()));
    this->passEdit->setText(QString::fromStdString(this->currentStudent.getPassword()));
    this->emailEdit->setText(QString::fromStdString(this->currentStudent.getEmail()));
    this->cashEdit->setText(QString::fromStdString(to_string(this->currentStudent.getCash())));
}
void StudentWidget::ButtonClicked(QAction *action)
{
    if (action->text() == "Profile")
        this->ProfileWidget->show();
    else if (action->text() == "Borrow")
        emit getBookInfo(searchLineEdit->text().toStdString());   //**********************************
      //  this->bookWidget= new BookWidget(b);
    //this->bookWidget->show();
    else if (action->text() == "Return")
        this->ReturnWidget->show();
    else if (action->text() == "Expected")
        emit aa(currentStudent.getName());
    else if (action->text() == "Search")
        this->SearchWidget->show();
    else if (action->text() == "History")
        emit getSearchHistory(currentStudent.getName());
    else if (action->text() == "Log Out")
        emit setCurrentWidget(LOGIN_WIDGET);

}

void StudentWidget::editButtonClicked()
{
    this->nameEdit->setReadOnly(false);
    this->passEdit->setReadOnly(false);
    this->emailEdit->setReadOnly(false);
    this->cashEdit->setReadOnly(false);
}

void StudentWidget::okButtonClicked()
{
    // update Student DataBase
    string name = this->nameEdit->text().toStdString();
    string pass = this->passEdit->text().toStdString();
    string email = this->emailEdit->text().toStdString();
    int cash = this->cashEdit->text().toInt();

    emit updateStudent(this->currentStudent.getName(),name,pass,email,cash);

    this->currentStudent.setName(name);
    this->currentStudent.setPassword(pass);
    this->currentStudent.setEmail(email);
    this->currentStudent.setCash(cash);

    this->nameEdit->setReadOnly(true);
    this->passEdit->setReadOnly(true);
    this->emailEdit->setReadOnly(true);
    this->cashEdit->setReadOnly(true);
    this->ProfileWidget->hide();

}

void StudentWidget::backButtonClicked()
{
    this->ReturnWidget->hide();
}

void StudentWidget::okkButtonClicked()
{
    string returnBookName = this->ReturnBook->text().toStdString();
    emit returnBook(returnBookName,currentStudent.getName());
}

void StudentWidget::increaseIsClicked()
{
    todayDate++;
    this->today->setText(QString::fromStdString(to_string(todayDate)));
}

void StudentWidget::error_return(string text)
{
    this->errorBox->setText(QString::fromStdString(text));//setIcon if you want
    this->errorBox->show();
}

void StudentWidget::bookReturned(int bill , int mode)
{//set icons if you want
    if(mode==0){
        this->errorBox->setText("Thanks for returning the book sound and in time\n Here's your bill: "+QString::fromStdString(to_string(bill)));
        this->errorBox->show();
    }
    else if(mode==1){
        this->errorBox->setText("You've damaged the book, you will pay half of its price\n Here's your bill: "+QString::fromStdString(to_string(bill)));
        this->errorBox->show();
    }
    else if(mode==2){
        this->errorBox->setText("You're late, a fee will be added to the bill\n Here's your bill: "+QString::fromStdString(to_string(bill)));
        this->errorBox->show();
    }
    else if(mode==3){
        this->errorBox->setText("You're late and you've damaged the book!! \n Here's your bill: "+QString::fromStdString(to_string(bill)));
        this->errorBox->show();
    }
    this->ReturnWidget->hide();
}

void StudentWidget::borrowedBooks(vector<Book> v)
{
    for(int i=0;i<v.size();i++)
    {
        string a = v[i].getName();
        int b = v[i].getBorrowedDate();
        int c = v[i].getExpectedReturnDate();
        int d =ceil((c-b)/7.0)*v[i].getPrice();
        this->addRoot(a,to_string(b),to_string(c),to_string(d));
    }
    this->BorrowedWidget->show();
}

void StudentWidget::searchedBooks(vector<string> v)
{

    for(int i=0;i<v.size();i++)
       this->addRoot(v[i]);

    this->HistoryWidget->show();
}

void StudentWidget::ok1ButtonClicked()
{
    this->BorrowedWidget->hide();
    this->borrowedList->clear();
}

void StudentWidget::okButtonhClicked()
{
    this->HistoryWidget->hide();
    this->HistoryList->clear();
}

void StudentWidget::nameButtonClicked()
{
    this->tabWidget->clear();
    emit searchBookByName(this->SearchBook->text().toStdString(),currentStudent.getName());
}

void StudentWidget::typeButtonClicked()
{
    this->tabWidget->clear();
    emit searchBookByType(this->SearchBook->text().toStdString(),currentStudent.getName());
}

void StudentWidget::priceButtonClicked()
{
    this->tabWidget->clear();
    emit searchBookByPrice(stoi(this->SearchBook->text().toStdString()),currentStudent.getName());
}

void StudentWidget::pubButtonClicked()
{
    this->tabWidget->clear();
    emit searchBookByPub(this->SearchBook->text().toStdString(),currentStudent.getName());
}

void StudentWidget::doneButtonClicked()
{
    this->SearchWidget->hide();
}

void StudentWidget::booksFound(vector<Book> v)
{
    if(v.size()==0)
        this->tabWidget->addTab(new QLabel("No Book matches your search"),QString::fromStdString("xxx"));

    for(int i=0;i<v.size();i++)
        this->tabWidget->addTab(new BookWidget(/*v[i]*/),QString::fromStdString(v[i].getName()));

    this->tabWidget->show();
}


void StudentWidget::addRoot(string s0, string s1,string s2, string s3)
{
    QTreeWidgetItem *i1 = new QTreeWidgetItem(this->borrowedList);
    i1->setText(0,QString::fromStdString(s0));
    i1->setText(1,QString::fromStdString(s1));
    i1->setText(2,QString::fromStdString(s2));
    i1->setText(3,QString::fromStdString(s3));
    borrowedList->addTopLevelItem(i1);

}

void StudentWidget::addRoot(string s)
{
    QTreeWidgetItem *i1 = new QTreeWidgetItem(this->HistoryList);
    i1->setText(0,QString::fromStdString(s));
     HistoryList->addTopLevelItem(i1);
}

//void StudentWidget::librarianWidgetOpen()
//{
//    this->librarianWidget->show();
//}

//void StudentWidget::Ok2ButtonClicked()
//{
//    emit libBookState(stoi(this->bookState->text().toStdString()));
//    this->librarianWidget->hide();
//}
