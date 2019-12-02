#include "publisherwidget.h"

PublisherWidget::PublisherWidget(QWidget *parent) : QWidget(parent)
{
    this->grid = new QGridLayout;
    this->addBookBtn = new QPushButton("Add Book");
    this->BackBtn = new QPushButton("<< Back");

    this->bookName = new QLineEdit;
    this->bookPrice = new QLineEdit;
    this->bookType = new QLineEdit;

    this->pubBooksNumLabel = new QLabel("Books Published");
    this->pubNameLabel = new QLabel("Publisher Name");
    this->bookNameLabel = new QLabel("Enter Book Name");
    this->bookPriceLabel= new QLabel("Enter Book Price");
    this->bookTypeLabel = new QLabel("Enter Book Type");


    this->errorBox = new QMessageBox();
    this->errorBox->setWindowIcon(QIcon(QCoreApplication::applicationDirPath()+"/../../Library-Management-System/icons/error.png"));

    this->showInfo = new QPushButton("Profile");

    this->initProfileWidget();
    this->Design();
    this->Signals_Slots();
    this->setLayout(this->grid);
}

void PublisherWidget::Design()
{
    this->grid->addWidget(this->BackBtn,6,0);

   // this->grid->addWidget(this->bookName,1,2);
   //his->grid->addWidget(this->bookPrice,2,2);
   // this->grid->addWidget(this->bookType,3,2);

    //this->grid->addWidget(this->pubBooksNumLabel,0,2);
    //this->grid->addWidget(this->pubNameLabel,0,0);
    //this->grid->addWidget(this->bookNameLabel,1,0);
    //this->grid->addWidget(this->bookPriceLabel,2,0);
    //this->grid->addWidget(this->bookTypeLabel,3,0);
    //this->grid->addWidget(this->bookStateLabel,4,0);
    //this->grid->addWidget(this->state0,4,2);
    //this->grid->addWidget(this->state1,4,3);

    QVBoxLayout* verticalLayout = new QVBoxLayout;
    verticalLayout->addWidget(this->bookNameLabel);
    verticalLayout->addWidget(this->bookName);
    verticalLayout->addWidget(this->bookTypeLabel);
    verticalLayout->addWidget(this->bookType);
    verticalLayout->addWidget(this->bookPriceLabel);
    verticalLayout->addWidget(this->bookPrice);
    verticalLayout->addWidget(this->addBookBtn);
    this->grid->addLayout(verticalLayout,2,5,1,-1);
    this->grid->addWidget(this->showInfo);
}

void PublisherWidget::Signals_Slots()
{
    connect(this->BackBtn,SIGNAL(clicked()),this,SLOT(buttonBack()));
    connect(this->addBookBtn,SIGNAL(clicked()),this,SLOT(bookDataCheck()));
    connect(this->EditBtn,SIGNAL(clicked()),this,SLOT(editButtonClicked()));
    connect(this->OkBtn,SIGNAL(clicked()),this,SLOT(okButtonClicked()));
    connect(this->showInfo,SIGNAL(clicked()),this,SLOT(showInfoBtnClicked()));
}

void PublisherWidget::bookDataCheck()
{
    cout << "ray2" << endl;
    if(this->bookName->text().isEmpty() || this->bookType->text().isEmpty() || this->bookPrice->text().isEmpty())
    {
        this->errorBox->setText("Please Fill all");
        this->errorBox->show();
        return;
    }

    string Name ;
    string Type;
    int Price;
    Name  =this->bookName->text().toStdString();
    Type  =this->bookType->text().toStdString();
    Price =this->bookPrice->text().toInt();
    emit addBookData(this->currentPublisher.getName(),Name,Type,Price);
}

void PublisherWidget::initProfileWidget()
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

void PublisherWidget::error(string text)
{
    this->errorBox->setText(QString::fromStdString(text));
    this->errorBox->show();
}

void PublisherWidget::buttonBack()
{
    emit setCurrentWidget(START_WIDGET);
}

void PublisherWidget::publisherLoggedIn(Publisher Publisher)
{
    this->currentPublisher = Publisher;
    this->nameEdit->setText(QString::fromStdString(this->currentPublisher.getName()));
    this->passEdit->setText(QString::fromStdString(this->currentPublisher.getPassword()));
    this->emailEdit->setText(QString::fromStdString(this->currentPublisher.getEmail()));
    this->cashEdit->setText(QString::fromStdString(to_string(this->currentPublisher.getCash())));
}

void PublisherWidget::showInfoBtnClicked()
{
    this->ProfileWidget->show();
}

void PublisherWidget::editButtonClicked()
{
    this->nameEdit->setReadOnly(false);
    this->passEdit->setReadOnly(false);
    this->emailEdit->setReadOnly(false);
    this->cashEdit->setReadOnly(false);
}

void PublisherWidget::okButtonClicked()
{
    // update Publisher DataBase
    string name = this->nameEdit->text().toStdString();
    string pass = this->passEdit->text().toStdString();
    string email = this->emailEdit->text().toStdString();
    int cash = this->cashEdit->text().toInt();

    emit updatePublisher(this->currentPublisher.getName(),name,pass,email,cash);

    this->currentPublisher.setName(name);
    this->currentPublisher.setPassword(pass);
    this->currentPublisher.setEmail(email);
    this->currentPublisher.setCash(cash);

    this->nameEdit->setReadOnly(true);
    this->passEdit->setReadOnly(true);
    this->emailEdit->setReadOnly(true);
    this->cashEdit->setReadOnly(true);

    this->ProfileWidget->hide();
}

