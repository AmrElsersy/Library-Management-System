#include "controller.h"
extern int todayDate;
Controller::Controller() : QObject()
{
    QString path = QCoreApplication::applicationDirPath();
    this->db.init(path);
}
void Controller::start()
{
}

void Controller::sign_up(string name ,string email , string password , int choice)
{
    Student student1;
    Publisher publisher1;
    if (choice == 1) // user is student
    {
        student1.setName(name);
        student1.setPassword(password);
        student1.setEmail(email);
        if(!db.saveStudent(student1))
        {
            emit error("Student Name already Exist ! Enter another name");
            cout << "Student Name already Exist ! Enter another name" << endl;
            return;
        }
        cout<<"You signed up successfully"<<endl;
    }
    else
    {
        publisher1.setName(name);
        publisher1.setPassword(password);
        publisher1.setEmail(email);

        if(! db.savePublisher(publisher1))
        {
            emit error("Publisher Name already Exist ! Enter another name");
            cout << "Publisher Name already Exist ! Enter another name" << endl;
            return;
        }
        cout<<"You signed up successfully"<<endl;
    }
    this->log_in(name,password,choice);
}
void Controller::log_in(string name , string password , int choice)
{
    if(choice==1)
    {
        Student s;
        int mode = db.checkStudent(name,password);
        if (mode==1)
        {
            emit error_login("No name matches the name you entered");
        }
        else if(mode==2)
        {
            emit error_login("Wrong Password");
        }
        else if(mode==0)
        {
            s = db.loadStudent(name);
            cout<<"You've logged in successfully"<<endl;
            emit studentLoggedin(s);
            emit setCurrentWidget(STUDENT_WIDGET);
        }
    }
    else if(choice==2)
    {
        Publisher p;
        int mode = db.checkPublisher(name,password);
        if (mode==1)
        {
            emit error_login("No name matches the name you entered");
        }
        else if(mode==2)
        {
            emit error_login("Wrong Password");
        }
        else if(mode==0)
        {
            p = db.loadPublisher(name);
            cout<<"You've logged in successfully"<<endl;
            emit publisherLoggedin(p);
            emit setCurrentWidget(PUBLISHER_WIDGET);
        }
    }

}
void Controller::publisherLoggedIn(string pubName)
{
    while(1)
    {
        cout <<"what do yo want to do ? \n";
        cout << "1-Upload book" << endl;
        cout << "2-Update book"<<endl;
        cout << "3-view books" << endl;
        cout << "4-view cash" << endl;
        cout << "5-view profile" << endl;
        cout << "6-edit profile"<<endl;
        cout << "7-Log Out"<<endl;
        int choice;
        cin>>choice;
        if(choice==1)
        {
            string name,type;
            int price;
            cout<<"Enter Book Name : ";
            cin>>name;
            cout<<"Enter Book Type : ";
            cin>>type;
            cout<<"Enter Book Price : ";
            cin>>price;
            this->Upload_book(pubName,name,type,price);
        }
        else if(choice==2)
        {
            Book book1;
            string nameInitial,type,name;
            int price,x;
            cout<<"Which book you want to update? :";
            cin>>nameInitial;
            book1=db.loadBook(nameInitial);
            cout<<"What do you want to edit in this book ?"<<endl;
            cout<<"1-Name"<<endl;
            cout<<"2-Type"<<endl;
            cout<<"3-Price"<<endl;
            cin>>x;
            if(x==1){cout<<"Enter Book Name : ";cin>>name;book1.setName(name);}
            if(x==2){cout<<"Enter Book Type : ";cin>>type;book1.setType(type);}
            if(x==3){cout<<"Enter Book Price : ";cin>>price;book1.setPrice(price);}
            db.updateBook(book1,nameInitial);
        }
        else if(choice==3)
        {
            vector<string> s = db.loadPublisher(pubName).viewMyBooks();
            cout<<"Your books are : ";
            for (int i =0 ; i < s.size() ; i++)
                cout << s[i] << " ";
            cout << endl;
        }
        else if(choice==4) cout<<"You Have : "<< db.loadPublisher(pubName).getCash() << " L.E.\n" ;
        else if(choice==5) db.loadPublisher(pubName).showInfo();
        else if(choice==6)
        {
            Publisher pub;
            string email,name,pass;
            int cashAmount,x;
            pub=db.loadPublisher(pubName);
            cout<<"What do you want to edit in the profile ?"<<endl;
            cout<<"1-Name"<<endl;
            cout<<"2-Password"<<endl;
            cout<<"3-Email"<<endl;
            cout<<"4-Cash amount"<<endl;
            cin>>x;
            if(x==1){cout<<"Enter new Name : ";cin>>name;pub.setName(name);}
            if(x==2){cout<<"Enter new Password : ";cin>>pass;pub.setPassword(pass);}
            if(x==3){cout<<"Enter new Email : ";cin>>pass;pub.setPassword(pass);}
            if(x==4){cout<<"Enter new Cash amount : ";cin>>cashAmount;pub.setCash(cashAmount);}
            db.updatePublisher(pub,pubName);
            break;
        }
        else if(choice==7) return;
        else cout<<"Wrong Choice. "<<endl;
    }
}

void Controller::Upload_book(string pubName ,string name ,string type,int price)
{
    Book book1;
    book1.setName(name);
    book1.setPrice(price);
    book1.setType(type);
    book1.setPublisherName(pubName);
    book1.setState(1);
    book1.setAvailability(1);
    db.saveBook(book1);
//    if(!db.saveBook(book1))
//    {
//        cout << "book already exist! " << endl;
//        return;
//    }
    db.addPublisherBooks(book1,pubName);
    db.addPublisherCash(price*10,pubName);
    cout<<"Book saved succesfully and cash added to your account <3"<<endl;
}
void Controller::searchBookByName(string BookNameOrID,string stuName)
{
    //Book b = db.loadBookByRowId(BookNameOrID);

    Book b;
    // check for available books
    b= db.loadBook(BookNameOrID);
    // if not found -> get any un available book to just show it to user and know that there is no available books
    if(b.getName().empty())
        b= db.loadBookForce(BookNameOrID);
    if(b.getName().empty())
    {
        emit error_noBook("Not Found Book");
        return;
    }
    emit bookInfo(b);
    Student s =db.loadStudent(stuName);
    db.addSearchHistory(b,stuName);
    db.updateStudent(s,stuName);
}

void Controller::searchBookByType(string type , string stuName)
{
    vector<Book> v = db.searchBookByType(type);
    Student s =db.loadStudent(stuName);
    for(int i=0;i<v.size();i++)
    {
        db.addSearchHistory(v[i],stuName);
        db.updateStudent(s,stuName);
    }

    emit booksFound(v);
}

void Controller::searchBookByPrice(int price, string stuName)
{
    vector<Book> v = db.searchBookByPrice(price);
    emit booksFound(v);
    Student s =db.loadStudent(stuName);
    for(int i=0;i<v.size();i++)
    {
        db.addSearchHistory(v[i],stuName);
        db.updateStudent(s,stuName);
    }
}

void Controller::searchBookByPub(string pub, string stuName)
{
    vector<Book> v = db.searchBookByPubName(pub);
    emit booksFound(v);
    Student s =db.loadStudent(stuName);
    for(int i=0;i<v.size();i++)
    {
        db.addSearchHistory(v[i],stuName);
        db.updateStudent(s,stuName);
    }
}

void Controller::borrowBook(string bookName,string stuName,int expectedReturnDate)
{
    if(db.loadBook(bookName).getName().empty())
    {
        emit error_noBook("This book is not available");
        return;
    }
    else {
        int borrowDate=todayDate;
        Student s = db.loadStudent(stuName);
        Book b = db.loadBook(bookName);
        s.setCurrentBook(db.loadBook(bookName).getRowId());
        b.setBorrowedDate(borrowDate);
        b.setExpectedReturnDate(expectedReturnDate);
        db.addCurrentBooks(b,stuName);
        db.addBorrowedBooks(b,stuName);
        b.setAvailability(0);
        //db.updateStudent(s,stuName);
        db.updateBookByRowId(b,db.loadBook(bookName).getRowId());
        Publisher pub = db.loadPublisher(b.getPublisherName());
        pub.addCash(b.getPrice()/2);
        db.updatePublisher(pub,pub.getName());
        cout<<"You borrowed the book successfully, your book's ID is : "<<b.getRowId()<<endl;
        cout<<"You will pay : "<<ceil((expectedReturnDate-borrowDate)/7.0)*b.getPrice()<<endl;
        cout<<"Warning 1 : if you return the book late, you'll pay a fee of 5$ for each week late"<<endl;
        cout<<"Warning 2 : if you return the book damaged, you'll pay a fee of half the book's price"<<endl;
    }}

void Controller::returnBook(string bookName, string stuName)
{
    int bill=0,actualReturnDate,actualBorrowedPeriod,expectedBorrowedPeriod;int flag=0,flag2=0,flag3=0,flag4=0,mode;
    string rowid;Librarian l;vector<string> v;Book b;
    Student s=db.loadStudent(stuName);
    v= split_string(s.getCurrentBookName(),",");
    for(int i=0;i<v.size();i++)
    {
        if(db.loadBookByRowId(v[i]).getName()==bookName)
        {
            flag2=1;
            b=db.loadBookByRowId(v[i]);
            v.erase(v.begin()+i);
        }
    }
    if(!flag2)
        emit error_return("You didn't borrow this book");
    else
    {
        actualReturnDate=todayDate;
        b.setActualReturnDate(actualReturnDate);
        actualBorrowedPeriod = b.getActualReturnDate() - b.getBorrowedDate();
        expectedBorrowedPeriod=b.getExpectedReturnDate()-b.getBorrowedDate();
        bill=ceil(actualBorrowedPeriod/7.0)*b.getPrice();
        if(actualBorrowedPeriod>expectedBorrowedPeriod)
        {
            int fee;
            fee=5*ceil((actualBorrowedPeriod-expectedBorrowedPeriod)/7.0);
            bill+=fee;
            flag=1;flag3=1;
        }
        //int state = l.checkState(&b);
        if(1)
        {
            int fee;
            fee=b.getPrice()/2;
            bill+=fee;
            flag=1;flag4=1;
        }
        if(!flag3&&flag4)mode=1;       //late
        else if(flag3&&!flag4)mode=2;  //damaged
        else if(flag3&&flag4)mode=3;   //late and damaged (7ayawan ya3ni)
        else mode=0;                   //wa7ed mo7taram <3
        emit bookReturned(bill,mode);
        s.addCash(-1*bill);
        string str=s.getCurrentBookName();
        int x;
        for(int i=0;i<str.size();i++)
        {if(b.getRowId()[0]==str[i])x=i;}
        if(str.size()==1)str="";
        else if(x==(str.size()-1)) str.erase (str.end()-2, str.end());
        else str.erase(x,2);
        s.setCurrentBook(str);
        b.setAvailability(1);
        b.setState(1);
        db.updateStudent(s,stuName);
        db.updateBookByRowId(b,b.getRowId());
    }
}

void Controller::aa(string stuName)
{
    vector<Book> v = db.loadStudent(stuName).getCurrentBookVector(&db);
    emit borrowedBooks(v);
}

void Controller::getBookInfo(string BookNameOrID)
{
    //Book b = db.loadBookByRowId(BookNameOrID);
    Book b;
    b= db.loadBook(BookNameOrID);
    if(b.getName().empty())
        b= db.loadBookForce(BookNameOrID);
    if(b.getName().empty())
    {
        emit error_noBook("Not Found Book");
        return;
    }
    emit bookInfo(b);
}

void Controller::getSearchHistory(string stuName)
{
    Student s = db.loadStudent(stuName);
    vector<string> v = s.getSearchHistory();
    //could load books instead of bookNames
    emit searchedBooks(v);
}

map<string, string> Controller::getAllBooks()
{
    return this->db.getAllBooks();
}

void Controller::updatePublisher(string pubName, string name, string pass, string email, int cashAmount)
{
    Publisher p;
    p=db.loadPublisher(pubName);
    p.setName(name);
    p.setPassword(pass);
    p.setEmail(email);
    p.setCash(cashAmount);
    db.updatePublisher(p,pubName);
}

void Controller::updateStudent(string stuName, string name, string pass, string email, int cashAmount)
{
    Student s;
    s=db.loadStudent(stuName);
    s.setName(name);
    s.setPassword(pass);
    s.setEmail(email);
    s.setCash(cashAmount);
    db.updateStudent(s,stuName);
}
void Controller::studentLoggedIn(string stuName)
{
    int choice;
    while(1)
    {
        cout<<"what do yo want to do ? "<<endl;
        cout << "1-Search" << endl;
        cout << "2-Borrow" << endl;
        cout << "3-Return" << endl;
        cout << "4-view search history" << endl;
        cout << "5-view favorite books" << endl;
        cout << "6-view your borrowed books"<<endl;
        cout << "7-check your cash"<<endl;
        cout << "8-view profile" << endl;
        cout << "9-edit profile" << endl;
        cout << "10-Log Out"<<endl;
        cin>>choice;
        if(choice==1)
        {
            int choice1;
            while(1){
                cout<<"Do you wanna search books by :"<<endl;
                cout<<"1-Name"<<endl;
                cout<<"2-Type"<<endl;
                cout<<"3-Publisher"<<endl;
                cout<<"4-Price"<<endl;
                cout<<"5-Exit"<<endl;
                cin>>choice1;
                if(choice1==1)
                {
                    string name;
                    cout<<"Enter book's name : ";
                    cin>>name;
                    if(db.loadBook(name).getName().empty()) cout<<"Your book is not available :( "<<endl;
                    else {

                        Book ray2 = db.loadBook(name);
                        ray2.showInfo();
                    }
                    db.addSearchHistory(db.loadBook(name),stuName);
                }
                else if(choice1==2)
                {
                    string type;
                    cout<<"Enter type : ";
                    cin>>type;
                    vector<Book> v = db.searchBookByType(type);
                    cout<<"We've found "<<v.size()<<" books that matches your search :"<<endl;
                    for(int i=0; i<v.size();i++)
                    {  v[i].showInfo();
                        db.addSearchHistory(v[i],stuName);
                    }
                }
                else if(choice1==3)
                {
                    string publisherName;
                    cout<<"Enter name of publisher : ";
                    cin>>publisherName;
                    vector<Book> v = db.searchBookByPubName(publisherName);
                    cout<<"We've found "<<v.size()<<" books that matches your search :"<<endl;
                    for(int i=0; i<v.size();i++)
                    {
                        v[i].showInfo();
                        db.addSearchHistory(v[i],stuName);
                    }
                }
                else if(choice1==4)
                {
                    int price;
                    cout<<"Enter your price range : ";
                    cin>>price;
                    vector<Book> v = db.searchBookByPrice(price);
                    cout<<"We've found "<<v.size()<<" books that matches your search :"<<endl;
                    for(int i=0; i<v.size();i++)
                    {
                        v[i].showInfo();
                        db.addSearchHistory(v[i],stuName);
                    }
                }
                else if (choice1==5) break;
                else cout<<"Wrong choice , rakkez b2a mate2refnash"<<endl;
            }
        }
        else if(choice==2)
        {
            string name;Librarian l;
            int borrowDate,expectedReturnDate;
            cout<<"Enter book's name : ";
            cin>>name;
            if(db.loadBook(name).getName().empty())
            {
                Book b;int x;
                cout<<"This book is not available 😞 "<<endl;
                cout<<"Do you want to request this book ? 0 for no , 1 for yes"<<endl;
                cin>>x;
                if(x) b=l.supplyRequestedBook(stuName,&db);
            }
            else
            {
                cout<<"Enter today's date : ";//el 7etta dih el mafrod ne3melha men barra bas for now 5aliha keda
                cin>>borrowDate;
                cout<<"Enter return date : ";
                cin>>expectedReturnDate;
                Student s = db.loadStudent(stuName);
                Book b = db.loadBook(name);
                s.setCurrentBook(db.loadBook(name).getRowId());
                b.setBorrowedDate(borrowDate);
                b.setExpectedReturnDate(expectedReturnDate);
                db.addBorrowedBooks(b,stuName);
                b.setAvailability(0);
                db.updateStudent(s,stuName);
                db.updateBookByRowId(b,db.loadBook(name).getRowId());
                Publisher pub = db.loadPublisher(db.loadBook(b.getName()).getPublisherName());
                pub.addCash(db.loadBook(b.getName()).getPrice()/2);
                db.updatePublisher(pub,pub.getName());
                cout<<"You borrowed the book successfully, your book's ID is : "<<b.getRowId()<<endl;
                cout<<"You will pay : "<<ceil((expectedReturnDate-borrowDate)/7.0)*b.getPrice()<<endl;
                cout<<"Warning 1 : if you return the book late, you'll pay a fee of 5$ for each week late"<<endl;
                cout<<"Warning 2 : if you return the book damaged, you'll pay a fee of half the book's price"<<endl;
            }
        }
        else if(choice==3)
        {
            int bill=0,actualReturnDate,actualBorrowedPeriod,expectedBorrowedPeriod;bool flag=0;
            string rowid;Librarian l;
            cout<<"Enter your book's ID : ";
            cin>>rowid;
            Book b=db.loadBookByRowId(rowid);
            Student s=db.loadStudent(stuName);
            if(b.getRowId()!=s.getCurrentBookName())
                cout<<"This is not the book you borrowed!"<<endl;
            else
            {
                cout<<"Enter today's date : ";
                cin>>actualReturnDate;
                b.setActualReturnDate(actualReturnDate);
                actualBorrowedPeriod = b.getActualReturnDate() - b.getBorrowedDate();
                expectedBorrowedPeriod=b.getExpectedReturnDate()-b.getBorrowedDate();
                bill=ceil(actualBorrowedPeriod/7.0)*b.getPrice();
                if(actualBorrowedPeriod>expectedBorrowedPeriod)
                {
                    int fee;
                    fee=5*ceil((actualBorrowedPeriod-expectedBorrowedPeriod)/7.0);
                    bill+=fee;
                    flag=1;
                }
                int state = l.checkState(&b);
                if(state)
                {
                    int fee;
                    fee=b.getPrice()/2;
                    bill+=fee;
                    flag=1;
                }
                if(!flag)
                    cout<<"You're a good boy, you returned the book sound and in the right time, here's your bill : "<<bill<<endl;
                else cout<<"Enta 3ayel 3el2 w hatedfa3 8arama, 5od b2a : "<<bill<<endl;
                s.addCash(-1*bill);
                b.setAvailability(1);
                db.updateStudent(s,stuName);
                db.updateBookByRowId(b,b.getRowId());
            }}
        else if(choice==4)
        {
            Student s = db.loadStudent(stuName);
            //s.getSearchHistory
        }
        else if(choice==5)
        {
            Student s = db.loadStudent(stuName);
            //s.getBorrowedBooks
        }
        else if(choice==6)
        {
            Student s = db.loadStudent(stuName);
            //s.getFavoriteBooks
        }
        else if(choice==7)
            cout<<"You Have : "<< db.loadStudent(stuName).getCash() << " L.E.\n" ;
        else if(choice==8)
            db.loadStudent(stuName).showInfo();
        else if(choice==9)
        {
            Student s;
            string email,name,pass;
            int cashAmount,x;
            s=db.loadStudent(stuName);
            cout<<"What do you want to edit in the profile ?"<<endl;
            cout<<"1-Name"<<endl;
            cout<<"2-Password"<<endl;
            cout<<"3-Email"<<endl;
            cout<<"4-Cash amount"<<endl;
            cin>>x;
            if(x==1){cout<<"Enter new Name : ";cin>>name;s.setName(name);}
            if(x==2){cout<<"Enter new Password : ";cin>>pass;s.setPassword(pass);}
            if(x==3){cout<<"Enter new Email : ";cin>>pass;s.setPassword(pass);}
            if(x==4){cout<<"Enter new Cash amount : ";cin>>cashAmount;s.setCash(cashAmount);}
            db.updateStudent(s,stuName);
            break;
        }
        else if(choice==10)
            break;
        else
            cout<<"Enter correct choice"<<endl;
    }

}
vector<string> Controller :: split_string(string s,string splitter)
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
