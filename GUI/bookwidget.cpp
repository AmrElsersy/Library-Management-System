#include "bookwidget.h"

extern int todayDate;
BookWidget::BookWidget(Book b)
{
    currentBook =b;
}

BookWidget::BookWidget(QWidget *parent) : QWidget(parent)
{
    this->Path = QCoreApplication::applicationDirPath();
    this->grid = new QGridLayout();
    this->bookName = new QLabel();
    this->bookType = new QLabel();
    this->bookPrice = new QLabel();
    this->bookPublisher = new QLabel();
    this->bookAvailability = new QLabel();
    this->name = new QLabel("Name :");
    this->type = new QLabel("Type :");
    this->price = new QLabel("Price :");
    this->publisher = new QLabel("Publisher :");
    this->availability = new QLabel("Status :");
    this->bookImage = new QLabel();
//    this->backBtn = new QPushButton("Ok");
    this->borrowBtn = new QPushButton("Borrow book");
    this->borrowed = new QMessageBox();
    this->errorBox = new QMessageBox();
    this->errorBox->setWindowIcon(QIcon(QCoreApplication::applicationDirPath()+"/../../Library-Management-System/icons/error.png"));

    this->grid->addWidget(this->name,0,0,1,1);
    this->grid->addWidget(this->type,1,0,1,1);
    this->grid->addWidget(this->price,2,0,1,1);
    this->grid->addWidget(this->publisher,3,0,1,1);
    this->grid->addWidget(this->availability,4,0,1,1);
    this->grid->addWidget(this->bookName,0,1,1,2);
    this->grid->addWidget(this->bookType,1,1,1,2);
    this->grid->addWidget(this->bookPrice,2,1,1,2);
    this->grid->addWidget(this->bookPublisher,3,1,1,2);
    this->grid->addWidget(this->bookAvailability,4,1,1,2);
//    this->grid->addWidget(this->backBtn,5,0,1,2);
    this->grid->addWidget(this->borrowBtn,5,2,1,2);
    this->grid->addWidget(this->bookImage,0,4,6,3);

    this->setLayout(this->grid);

    this->ReturnWidget = new QWidget();
    this->ReturnLayout = new QGridLayout();
    QLabel* enterBook = new QLabel("Enter expected return date :");
    this->ReturnDate = new QLineEdit();
    this->OkkBtn = new QPushButton("Ok");
    this->ReturnLayout->addWidget(enterBook,0,0,Qt::AlignLeft);
    this->ReturnLayout->addWidget(ReturnDate,0,1);
    QHBoxLayout* verticlaLayout = new QHBoxLayout;
    verticlaLayout->addWidget(OkkBtn);
    this->ReturnLayout->addLayout(verticlaLayout,2,0,1,-1);
    this-> ReturnWidget->setLayout(ReturnLayout);

    this->Signals_Slots();

    //emit getBookInfo(currentBook);
//    this->bookInfo(currentBook);
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
    emit borrowBook(bookNameStr,"amgad",expectedReturnDate);
    this->ReturnWidget->hide();
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

