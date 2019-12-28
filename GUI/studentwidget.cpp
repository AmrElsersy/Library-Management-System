#include "studentwidget.h"

extern int todayDate;
Book b;

StudentWidget::StudentWidget(QWidget *parent) : QWidget(parent)
{b.setPrice(10);
    this->Path = QCoreApplication::applicationDirPath();
    this->grid = new QGridLayout();
    this->toolBar = new QToolBar();
    this->searchLineEdit = new QLineEdit();
    this->searchLineEdit->setStyleSheet("background: white;");

    this->viewBooksScroll = new QScrollArea();
    this->viewBooksWidget = new QWidget();
    this->viewBooksWidget->setStyleSheet("background: white;");
    this->viewBooksLayout = new QGridLayout();
    this->lastSize.setWidth(0);
    this->lastSize.setHeight(0);

    //today   to be designed
    this->increaseTime = new QPushButton("Add day");
    this->increaseTime->setStyleSheet("background: #008080; border-radius: 10px; padding: 10px 0px; color: white;"
                                      "font-weight: bold;"
                                      "font-size: 15px;");
    this->increaseTime->setCursor(Qt::PointingHandCursor);

    this->today = new QLabel();
    this->today->setText(" Today: "+QString::fromStdString(to_string(todayDate)));
    this->today->setStyleSheet("color:#00BFFF;font-weight: bold;font-size: 18px; background-color:white;");

    this->errorBox = new QMessageBox();
    this->successBox = new QMessageBox();
    this->successBox->setWindowIcon(QIcon(QCoreApplication::applicationDirPath()+"/../../Library-Management-System/icons/sucess.png"));
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
    QIcon favorite(this->Path + "/../../Library-Management-System/icons/book.png"); QString favoriteText = "My Books";
    QIcon History(this->Path + "/../../Library-Management-System/icons/history.png"); QString HistoryText = "History";
    QIcon Return(this->Path + "/../../Library-Management-System/icons/return.png"); QString ReturnText = "Return";
    QIcon LogOut(this->Path + "/../../Library-Management-System/icons/logout.png"); QString LogOutText = "Log Out";

    this->toolBar->addAction(Profile,ProfileText);
    this->toolBar->addAction(Search,SearchText);
    this->toolBar->addAction(favorite,favoriteText);
//    this->toolBar->addAction(Borrowed,BorrowedText);
    this->toolBar->addAction(History,HistoryText);
    this->toolBar->addAction(Return,ReturnText);
    this->toolBar->addAction(LogOut,LogOutText);
    this->toolBar->setStyleSheet("QToolButton:hover{padding: 5px;background-color: white; color: black;}"
                                 "QToolButton:select{padding: 5px;background-color: white; color: black;}"
                                 "QToolButton{padding: 10px; border-radius: 10px;}"
                                 "QToolBar{background-color:white;}");
}
void StudentWidget::initProfileWidget()
{
    this->ProfileWidget = new QWidget();
    this->ProfileWidget->setStyleSheet("background: white;color: #2E2E2E; font-size: 15px; font-weight: 400;");
    this->ProfileLayout = new QGridLayout();

    QLabel* name = new QLabel("Name:");             this->nameEdit = new QLineEdit(); nameEdit->setReadOnly(true);  this->nameEdit->setStyleSheet("QLineEdit{ background-color:white;border: 2px solid #00BFFF;border-radius: 5px;}");
    QLabel* password = new QLabel("Password:");     this->passEdit = new QLineEdit(); passEdit->setReadOnly(true);  this->passEdit->setStyleSheet("QLineEdit{ background-color:white;border: 2px solid #00BFFF;border-radius: 5px;}");
    QLabel* email = new QLabel("Email:");           this->emailEdit = new QLineEdit();emailEdit->setReadOnly(true); this->emailEdit->setStyleSheet("QLineEdit{ background-color:white;border: 2px solid #00BFFF;border-radius: 5px;}");
    QLabel* cashAmount = new QLabel("Cash Amount:");this->cashEdit = new QLineEdit(); cashEdit->setReadOnly(true);  this->cashEdit->setStyleSheet("QLineEdit{ background-color:white;border: 2px solid #00BFFF;border-radius: 5px;}");
//    name->setStyleSheet("background: white; color:#00BFFF;");
//    password->setStyleSheet("background: white; color:#00BFFF;");
//    email->setStyleSheet("background: white; color:#00BFFF;");
//    cashAmount->setStyleSheet("background: white; color:#00BFFF;");

    QLabel *image; QPixmap* pixMap;
    image = new QLabel;
    pixMap =new QPixmap(QCoreApplication::applicationDirPath()+"/../../Library-Management-System/icons/person.png");
    image->setPixmap(pixMap->scaled(image->width()/4,image->height()/4,Qt::KeepAspectRatio) );
    image->setScaledContents(true);

    this->EditBtn = new QPushButton("Edit");
    this->EditBtn->setStyleSheet("background: #00BFFF; border-radius: 10px; padding: 10px 0px; color: white; ");
    this->EditBtn->setCursor(Qt::PointingHandCursor);

    this->OkBtn = new QPushButton("Ok");
    this->OkBtn->setStyleSheet("background: #00BFFF; border-radius: 10px; padding: 10px 0px; color: white; ");
    this->OkBtn->setCursor(Qt::PointingHandCursor);

    QLabel* setting =new QLabel("Profile Settings");
    QFrame* line = new QFrame; line->setFrameShape(QFrame::HLine);

    this->ProfileLayout->addWidget(setting,0,0,1,1);
    this->ProfileLayout->addWidget(image,1,0,1,1);
    this->ProfileLayout->addWidget(line,2,0,1,-1);

    this->ProfileLayout->addWidget(name,3,0,Qt::AlignLeft);
    this->ProfileLayout->addWidget(nameEdit,3,1);

    this->ProfileLayout->addWidget(password,4,0,Qt::AlignLeft);
    this->ProfileLayout->addWidget(passEdit,4,1);

    this->ProfileLayout->addWidget(email,5,0,Qt::AlignLeft);
    this->ProfileLayout->addWidget(emailEdit,5,1);

    this->ProfileLayout->addWidget(cashAmount,6,0,Qt::AlignLeft);
    this->ProfileLayout->addWidget(cashEdit,6,1);

    QHBoxLayout* horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(this->EditBtn);
    horizontalLayout->addWidget(this->OkBtn);
    this->ProfileLayout->addLayout(horizontalLayout,7,0,1,-1);

    this->ProfileWidget->setLayout(this->ProfileLayout);
    this->ProfileWidget->setMinimumWidth(500);
    this->ProfileWidget->setMinimumHeight(400);
}
void StudentWidget::initReturnWidget()
{
    this->ReturnWidget = new QWidget();
    this->ReturnWidget->setStyleSheet("background: white;color: #2E2E2E; font-size: 15px; font-weight: 400;");
    this->ReturnLayout = new QGridLayout();

    QLabel* enterBook = new QLabel("Enter return book :"); enterBook->setStyleSheet("color:#00BFFF");
    this->ReturnBook = new QLineEdit();
    this->ReturnBook->setStyleSheet("background: white;");

    this->BackBtn = new QPushButton("Back");
    this->BackBtn->setStyleSheet("background: #00BFFF; border-radius: 10px; padding: 10px 0px; color: white; ");
    this->BackBtn->setCursor(Qt::PointingHandCursor);

    this->OkkBtn = new QPushButton("Ok");
    this->OkkBtn->setStyleSheet("background: #00BFFF; border-radius: 10px; padding: 10px 0px; color: white; ");
    this->OkkBtn->setCursor(Qt::PointingHandCursor);

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
    this->BorrowedWidget->setStyleSheet("color: #2E2E2E; font-size: 15px; font-weight: 400;");
    this->borrowedList = new QTreeWidget();
    this->borrowedList->setStyleSheet("background: white");
    this->Ok1Btn = new QPushButton("Ok");
    this->Ok1Btn->setStyleSheet("background: #00BFFF; border-radius: 10px; padding: 10px 0px; color: white; ");
    this->Ok1Btn->setCursor(Qt::PointingHandCursor);
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
    this->SearchWidget->setStyleSheet("background: white;color: #2E2E2E; font-size: 15px; font-weight: 400;");
    this->SearchLayout = new QVBoxLayout();
    this->SearchBook = new QLineEdit();
    this->SearchBook->setStyleSheet("background: white;");
    QLabel *lbl = new QLabel("You want to search by :"); lbl->setStyleSheet("color:#00BFFF");

    this->NameBtn = new QPushButton("Name");
    this->NameBtn->setStyleSheet("background: #00BFFF; border-radius: 10px; padding: 10px 0px; color: white; ");
    this->NameBtn->setCursor(Qt::PointingHandCursor);

    this->TypeBtn = new QPushButton("Type");
    this->TypeBtn->setStyleSheet("background: #00BFFF; border-radius: 10px; padding: 10px 0px; color: white; ");
    this->TypeBtn->setCursor(Qt::PointingHandCursor);

    this->PriceBtn = new QPushButton("Price");
    this->PriceBtn->setStyleSheet("background: #00BFFF; border-radius: 10px; padding: 10px 0px; color: white; ");
    this->PriceBtn->setCursor(Qt::PointingHandCursor);

    this->PubBtn = new QPushButton("Publisher");
    this->PubBtn->setStyleSheet("background: #00BFFF; border-radius: 10px; padding: 10px 0px; color: white; ");
    this->PubBtn->setCursor(Qt::PointingHandCursor);

    this->DoneBtn = new QPushButton("Done");
    this->DoneBtn->setStyleSheet("background: #00BFFF; border-radius: 10px; padding: 10px 0px; color: white; ");
    this->DoneBtn->setCursor(Qt::PointingHandCursor);

    this->SearchLayout->addWidget(lbl);
    this->SearchLayout->addWidget(NameBtn);
    this->SearchLayout->addWidget(TypeBtn);
    this->SearchLayout->addWidget(PriceBtn);
    this->SearchLayout->addWidget(PubBtn);
    this->SearchLayout->addWidget(SearchBook);
    this->SearchLayout->addWidget(DoneBtn);
    this->SearchWidget->setLayout(this->SearchLayout);
    this->SearchWidget->setMinimumWidth(500);
}
void StudentWidget::initHistoryWidget()
{
    this->HistoryWidget = new QWidget();
    this->HistoryWidget->setStyleSheet("background: white;color: #2E2E2E; font-size: 15px; font-weight: 400;");
    this->HistoryList = new QTreeWidget();
    this->HistoryList->setStyleSheet("background: white");
    this->OkBtnh = new QPushButton("Ok");
    this->OkBtnh->setStyleSheet("background: #00BFFF; border-radius: 10px; padding: 10px 0px; color: white; ");
    this->OkBtnh->setCursor(Qt::PointingHandCursor);
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
    this->librarianWidget->setStyleSheet("background: #F6F5E4;color: #2E2E2E; font-size: 15px; font-weight: 400;");
    this->librarianWidget->setWindowTitle("Librarian");
    this->librarianWidget->move(600,0);
    this->librarianLayout = new QVBoxLayout();
    this->libLabel = new QLabel("Enter Book State :");
    this->bookState = new QLineEdit();
    this->bookState->setStyleSheet("background: white;");

    this->Ok2Btn = new QPushButton("Ok");
    this->Ok2Btn->setStyleSheet("background: #2e2e2e; border-radius: 10px; padding: 10px 0px; color: white; ");
    this->Ok2Btn->setCursor(Qt::PointingHandCursor);

    this->librarianLayout->addWidget(libLabel);
    this->librarianLayout->addWidget(bookState);
    this->librarianLayout->addWidget(Ok2Btn);

    this->librarianWidget->setLayout(librarianLayout);
}

void StudentWidget::Design()
{
    this->viewBooksScroll->setWidget(this->viewBooksWidget);
    this->viewBooksScroll->setWidgetResizable(true);
    this->viewBooksScroll->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    this->viewBooksWidget->setStyleSheet("background-color:white");
    this->viewBooksWidget->setLayout(this->viewBooksLayout);

    this->grid->addWidget(this->toolBar,0,1,-1,1);
    this->grid->addWidget(this->viewBooksScroll,0,0);
    this->grid->addWidget(this->increaseTime,1,0);
    this->grid->addWidget(this->today,1,1,Qt::AlignLeft);

    this->setMinimumSize(MIN_SIZE);
    this->setLayout(this->grid);
    this->setStyleSheet("background-color:white;");
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
}

void StudentWidget::UpdateBooks()
{
    // get allBooks from dataBase -> no duplicates
    map<string, string> name_imagePath = emit getAllBooks();
    // convert them into imageWidget (book interface)
    for (auto i = name_imagePath.begin(); i != name_imagePath.end() ;i++)
    {
        imageWidget* book_interface = new imageWidget(i->first,i->second);
        connect(book_interface,SIGNAL(bookClicked(string)),this,SLOT(bookClicked(string)));
        books.push_back(book_interface);
        cout << i->first << ",";
    }
    cout << "  =========== books" << endl;
    // display it in the gridlayout
    uint COLOMN_SIZE = 3;
    uint ROW_SIZE = books.size()/COLOMN_SIZE +1;

    cout << ROW_SIZE << "," << COLOMN_SIZE << endl;
    for (uint i =0 ; i< ROW_SIZE ; i++)
    {
        for(uint j =0 ; j< COLOMN_SIZE; j++)
        {
            uint index =  i * COLOMN_SIZE + j ;
            if(index >= books.size())
                break;
            cout << "i=" << i << ",j=" << j << ",index=" << index << endl;
            // for sizing apperance
            books[index]->setMaximumWidth(this->viewBooksWidget->width()/3);
            books[index]->setMaximumHeight(this->viewBooksWidget->height()/3);

            this->viewBooksLayout->addWidget(books[index],i,j);
        }
    }

}

void StudentWidget::studentLoggedIn(Student student)
{
    this->currentStudent = student;
    emit setLoggedInUserName(this->currentStudent.getName());
    this->nameEdit->setText(QString::fromStdString(this->currentStudent.getName()));
    this->passEdit->setText(QString::fromStdString(this->currentStudent.getPassword()));
    this->emailEdit->setText(QString::fromStdString(this->currentStudent.getEmail()));
    this->cashEdit->setText(QString::fromStdString(to_string(this->currentStudent.getCash())));
    this->UpdateBooks();
}
void StudentWidget::ButtonClicked(QAction *action)
{
    if (action->text() == "Profile")
        this->ProfileWidget->show();
    else if (action->text() == "Return")
        this->ReturnWidget->show();
    else if (action->text() == "My Books")
        emit aa(currentStudent.getName());
    else if (action->text() == "Search")
        this->SearchWidget->show();
    else if (action->text() == "History")
        emit getSearchHistory(currentStudent.getName());
    else if (action->text() == "Log Out")
    {
        emit setCurrentWidget(LOGIN_WIDGET);
        for (int i =0 ; i< this->books.size();i++)
            delete this->books[i];
        this->books.clear();
    }
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
    emit setLoggedInUserName(this->currentStudent.getName());

    this->successBox->setText("Edit Successfully !");
    this->successBox->show();
}

void StudentWidget::backButtonClicked()
{
    this->ReturnWidget->hide();
}

void StudentWidget::okkButtonClicked()
{
    if(this->ReturnBook->text().isEmpty() )
    {
        this->errorBox->setText("Please Enter a Valid Date");
        this->errorBox->show();
        return;
    }
    string returnBookName = this->ReturnBook->text().toStdString();
    emit returnBook(returnBookName,currentStudent.getName());
}

void StudentWidget::increaseIsClicked()
{
    todayDate++;
    this->today->setText(" Today: "+QString::fromStdString(to_string(todayDate)));
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

void StudentWidget::bookClicked(string name)
{
    emit getBookInfo(name);
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
    if(SearchBook->text().isEmpty())
    {
        this->errorBox->setText("Empty Search");
        this->errorBox->show();
        return;
    }
    this->tabWidget->clear();
    emit searchBookByName(this->SearchBook->text().toStdString(),currentStudent.getName());
}

void StudentWidget::typeButtonClicked()
{
    if(SearchBook->text().isEmpty())
    {
        this->errorBox->setText("Empty Search");
        this->errorBox->show();
        return;
    }

    this->tabWidget->clear();
    emit searchBookByType(this->SearchBook->text().toStdString(),currentStudent.getName());
}

void StudentWidget::priceButtonClicked()
{
    if(SearchBook->text().isEmpty())
    {
        this->errorBox->setText("Empty Search");
        this->errorBox->show();
        return;
    }

    this->tabWidget->clear();
    emit searchBookByPrice(this->SearchBook->text().toInt(),currentStudent.getName());
}

void StudentWidget::pubButtonClicked()
{
    if(SearchBook->text().isEmpty())
    {
        this->errorBox->setText("Empty Search");
        this->errorBox->show();
        return;
    }

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
    {
        this->errorBox->setText("Not Found");
        this->errorBox->show();
        return;
    }

    for(uint i=0;i<v.size();i++)
    {
        BookWidget* foundBookWidget  = new BookWidget;
        foundBookWidget->setCurrentBook(v[i]);
        this->tabWidget->addTab(foundBookWidget,QString::fromStdString(v[i].getName()));
    }
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
