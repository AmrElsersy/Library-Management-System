#include "bookwidget.h"

extern int todayDate;
BookWidget::BookWidget(Book b)
{
    currentBook =b;
}

BookWidget::BookWidget(QWidget *parent) : QWidget(parent)
{
    this->setStyleSheet("background: white;color: #00BFFF; font-size: 18px; font-weight: 400;");
    this->Path = QCoreApplication::applicationDirPath();
    this->grid = new QGridLayout();

    this->bookName = new QLabel(); bookName->setStyleSheet("color:#00BFFF;font-weight: bold;font-size: 15px;");
    this->bookType = new QLabel(); bookType->setStyleSheet("color:#00BFFF;font-weight: bold;font-size: 15px;");
    this->bookPrice = new QLabel(); bookPrice->setStyleSheet("color:#00BFFF;font-weight: bold;font-size: 15px;");
    this->bookPublisher = new QLabel(); bookPublisher->setStyleSheet("color:#00BFFF;font-weight: bold;font-size: 15px;");
    this->bookAvailability = new QLabel(); bookAvailability->setStyleSheet("color:#00BFFF;font-weight: bold;font-size: 15px;");

    this->name = new QLabel("Name :"); name->setStyleSheet("color:black;font-weight: bold;font-size: 16px;");
    this->type = new QLabel("Type :"); type->setStyleSheet("color:black;font-weight: bold;font-size: 16px;");
    this->price = new QLabel("Price :"); price->setStyleSheet("color:black;font-weight: bold;font-size: 16px;");
    this->publisher = new QLabel("Publisher :"); publisher->setStyleSheet("color:black;font-weight: bold;font-size: 16px;");
    this->availability = new QLabel("Status :"); availability->setStyleSheet("color:black;font-weight: bold;font-size: 16px;");
    this->bookImage = new QLabel();
    this->borrowBtn = new QPushButton("Borrow book");
    this->borrowBtn->setStyleSheet("background: #00BFFF; border-radius: 10px; padding: 10px 0px; color: white; width: 200px;");
    this->borrowBtn->setCursor(Qt::PointingHandCursor);
    this->borrowed = new QMessageBox();
    this->errorBox = new QMessageBox();
    this->errorBox->setWindowIcon(QIcon(QCoreApplication::applicationDirPath()+"/../../Library-Management-System/icons/error.png"));
    this->successBox = new QMessageBox();
    this->successBox->setWindowIcon(QIcon(QCoreApplication::applicationDirPath()+"/../../Library-Management-System/icons/sucess.png"));


    this->ReturnWidget = new QWidget();
    this->ReturnWidget->setStyleSheet("background: white;color: #00BFFF; font-size: 18px; font-weight: 400;");
    this->ReturnLayout = new QGridLayout();
    this->enterBook = new QLabel("Enter expected return date :"); enterBook->setStyleSheet("color:#00BFFF;");
    this->ReturnDate = new QLineEdit();
    this->OkkBtn = new QPushButton("Ok");
    this->OkkBtn->setStyleSheet("background: #00BFFF; border-radius: 10px; padding: 10px 0px; color: white; ");
    this->OkkBtn->setCursor(Qt::PointingHandCursor);

    this->Design();
    this->Signals_Slots();

}
void BookWidget::Design()
{

    this->grid->addWidget(this->name,0,0);
    this->grid->addWidget(this->type,1,0);
    this->grid->addWidget(this->price,2,0);
    this->grid->addWidget(this->publisher,3,0);
    this->grid->addWidget(this->availability,4,0);
    this->grid->addWidget(this->bookName,0,1,1,-1);
    this->grid->addWidget(this->bookType,1,1,1,-1);
    this->grid->addWidget(this->bookPrice,2,1,1,-1);
    this->grid->addWidget(this->bookPublisher,3,1,1,-1);
    this->grid->addWidget(this->bookAvailability,4,1,1,-1);
    this->grid->addWidget(this->borrowBtn,5,0,1,-1);
    this->grid->addWidget(this->bookImage,0,2,5,-1);

    this->ReturnLayout->addWidget(enterBook,0,0,Qt::AlignLeft);
    this->ReturnLayout->addWidget(ReturnDate,0,1);
    QHBoxLayout* verticlaLayout = new QHBoxLayout;
    verticlaLayout->addWidget(OkkBtn);
    this->ReturnLayout->addLayout(verticlaLayout,2,0,1,-1);
    this-> ReturnWidget->setLayout(ReturnLayout);

    this->setMinimumWidth(400);
    this->setMinimumHeight(300);
    this->setLayout(this->grid);
}


void BookWidget::Signals_Slots()
{
//    connect(this->backBtn,SIGNAL(clicked()),this,SLOT(backIsClicked()));
    connect(this->borrowBtn,SIGNAL(clicked()),this,SLOT(borrowIsClicked()));
    connect(this->OkkBtn,SIGNAL(clicked()),this,SLOT(okkkButtonClicked()));

}

void BookWidget::backIsClicked()
{
    // mlhas lazma
//    this->hide();
}

void BookWidget::borrowIsClicked()
{
    if(!this->currentBook.getAvailability())
    {
        this->errorBox->setText("Book is Not Available");
        this->errorBox->show();
        return;
    }
    ReturnWidget->show();
}

void BookWidget::bookInfo(Book b)
{
    currentBook = b;
    this->bookName->setText(QString::fromStdString(currentBook.getName()));
    this->bookType->setText(QString::fromStdString(currentBook.getType()));
    this->bookPrice->setText(QString::fromStdString(to_string(currentBook.getPrice())));
    this->bookPublisher->setText(QString::fromStdString(currentBook.getPublisherName()));
    if(currentBook.getAvailability()) this->bookAvailability->setText("Available");
    else this->bookAvailability->setText("Not Available");
    QIcon icon(this->Path + QString::fromStdString(currentBook.getImagePath()));
    QPixmap image = icon.pixmap(100,100);
    bookImage->setPixmap(image);
    bookNameStr=currentBook.getName();
    this->show();
}


void BookWidget::error(string text)
{
    this->errorBox->setText(QString::fromStdString(text));
    this->errorBox->show();
}

void BookWidget::okkkButtonClicked()
{
    // check empty search
    if(this->ReturnDate->text().isEmpty())
    {
        this->errorBox->setText("Enter Return Date");
        this->errorBox->show();
        return;
    }
    // return Date must be > todayDate
    if(this->ReturnDate->text().toInt() <= todayDate)
    {
        this->errorBox->setText("Invalid Return Data");
        this->errorBox->show();
        return;
    }

    this->expectedReturnDate = this->ReturnDate->text().toInt();
    emit borrowBook(this->bookNameStr,this->userName ,this->expectedReturnDate);
    this->ReturnWidget->hide();
    this->successBox->setText("Borrowed the Book Successfully !");
    this->successBox->show();

}

void BookWidget::setCurrentBook(Book b)
{
    currentBook =b;
    this->bookName->setText(QString::fromStdString(currentBook.getName()));
    this->bookType->setText(QString::fromStdString(currentBook.getType()));
    this->bookPrice->setText(QString::fromStdString(to_string(currentBook.getPrice())));
    this->bookPublisher->setText(QString::fromStdString(currentBook.getPublisherName()));
    if(currentBook.getAvailability()) this->bookAvailability->setText("Available");
    else this->bookAvailability->setText("Not Available");
    QIcon icon(this->Path + QString::fromStdString(currentBook.getImagePath()));
    QPixmap image = icon.pixmap(100,100);
    bookImage->setPixmap(image);
    bookNameStr=currentBook.getName();

}

void BookWidget::setLoggedInUserName(string name)
{
    this->userName = name;
}

