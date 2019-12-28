#include "publisherwidget.h"

PublisherWidget::PublisherWidget(QWidget *parent) : QWidget(parent)
{
    this->main_grid = new QGridLayout;
    this->widget = new QWidget;
    // ********** header ***************
    this->headerWidget = new QWidget;
    this->headerLayout = new QHBoxLayout;

    this->pixMapHeader = new QPixmap(QCoreApplication::applicationDirPath()+"/../../Library-Management-System/icons/person.png");
    this->iconHeader   = new QLabel;
    this->Name = new QLabel;
    this->toolBar = new QToolBar;

    this->initHeader();

    // book image
    this->image = new QLabel;
    this->image->setMaximumSize(QSize(200,200));
    this->pixMap =new QPixmap(QCoreApplication::applicationDirPath()+"/../../Library-Management-System/icons/addBook.png");
    this->image->setPixmap(pixMap->scaled(this->image->width(),this->image->height(),Qt::KeepAspectRatio) );
    this->image->setScaledContents(true);

    this->setStyleSheet("font-size: 15px; font-weight: 400;");
    this->grid = new QGridLayout;
    this->addBookBtn = new QPushButton("Add Book");
    this->addBookBtn->setStyleSheet("background: #00BFFF; border-radius: 10px; padding: 10px 0px; color: white; width: 200px;"
                                    "hover{background-color:white; color:#00BFFF;}"); // hover is not working
    this->addBookBtn->setCursor(Qt::PointingHandCursor);

//    this->BackBtn = new QPushButton("Logout");
//    this->BackBtn->setStyleSheet("background: #00BFFF; border-radius: 10px; padding: 10px 0px; color: white; width: 100px;");
//    this->BackBtn->setCursor(Qt::PointingHandCursor);

    this->bookName = new QLineEdit;
    this->bookName->setStyleSheet("QLineEdit{ background-color:white;border: 2px solid #00BFFF;border-radius: 5px;}");
    this->bookPrice = new QLineEdit;
    this->bookPrice->setStyleSheet("QLineEdit{ background-color:white;border: 2px solid #00BFFF;border-radius: 5px;}");
    this->bookType = new QLineEdit;
    this->bookType->setStyleSheet("QLineEdit{ background-color:white;border: 2px solid #00BFFF;border-radius: 5px;}");

    this->pubBooksNumLabel = new QLabel("Books Published");
    this->pubNameLabel = new QLabel("Publisher Name");
    this->bookNameLabel = new QLabel("Book Name");
    this->bookPriceLabel= new QLabel("Book Price");
    this->bookTypeLabel = new QLabel("Book Type");


    this->errorBox = new QMessageBox();
    this->errorBox->setWindowIcon(QIcon(QCoreApplication::applicationDirPath()+"/../../Library-Management-System/icons/error.png"));
    this->sucessBox = new QMessageBox();
    this->sucessBox->setWindowIcon(QIcon(QCoreApplication::applicationDirPath()+"/../../Library-Management-System/icons/sucess.png"));

//    this->showInfo = new QPushButton("Profile");
//    this->showInfo->setStyleSheet("background: #00BFFF; border-radius: 10px; padding: 10px 0px; color: white; width: 100px;");
//    this->showInfo->setCursor(Qt::PointingHandCursor);

    this->initProfileWidget();
    this->Design();
    this->outDesign();
    this->Signals_Slots();
}

void PublisherWidget::initHeader()
{
    // ********* tool Bar ************
    this->toolBar->setCursor(Qt::PointingHandCursor);
    QIcon logoutBtn= QIcon(QCoreApplication::applicationDirPath()+"/../../Library-Management-System/icons/logout.png");
    QIcon profileBtn = QIcon (QCoreApplication::applicationDirPath()+"/../../Library-Management-System/icons/profile.png");
    QString logoutString  = "Logout";
    QString profileString = "Profile";
    this->toolBar->addAction(logoutBtn,logoutString);
    this->toolBar->addAction(profileBtn,profileString);
    this->toolBar->setIconSize(QSize(50,50));
    this->toolBar->setOrientation(Qt::Horizontal);
    this->toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    this->toolBar->setStyleSheet("QToolButton:hover{padding: 10px; background-color:white; color:#00BFFF;}"
                                 "QToolButton:select{padding: 10px;}"
                                 "QToolButton{color:white; font-weight: bold;}");

    // ******** Icon *********
    this->iconHeader->setMaximumSize(QSize(50,50));
    this->iconHeader->setPixmap(pixMapHeader->scaled(this->iconHeader->width(),this->iconHeader->height(),Qt::KeepAspectRatio) );
    this->iconHeader->setScaledContents(true);

    // ******** Layout Design *****************
    this->headerLayout->addWidget(this->iconHeader,Qt::AlignLeft);
    this->headerLayout->addWidget(this->Name,Qt::AlignLeft);
    this->headerLayout->addItem(new QSpacerItem(300,20));
    this->headerLayout->addWidget(this->toolBar,Qt::AlignRight);

    this->headerWidget->setLayout(this->headerLayout);
    this->headerWidget->setStyleSheet("background-color:#00BFFF");

    // name
    this->Name->setText("Name"); this->Name->setStyleSheet("font-weight:bold; font-size:18px; color:white;");

    this->headerWidget->setMinimumWidth(600);
    this->headerWidget->show();

}
void PublisherWidget::outDesign()
{
    QWidget *w1 = new QWidget; QWidget *w2 = new QWidget;
    this->main_grid->addWidget(w1,0,0,1,3);
    this->main_grid->addWidget(w2,2,0,1,3);

    this->main_grid->addWidget(this->widget,1,1);
    this->setLayout(this->main_grid);
}
void PublisherWidget::Design()
{
    this->widget->setStyleSheet("background-color:white;");

    this->rightLayout= new QGridLayout;
    this->rightLayout->addWidget(this->bookNameLabel,0,0);
    this->rightLayout->addWidget(this->bookName,0,1,1,-1);
    this->rightLayout->addWidget(this->bookPriceLabel,1,0);
    this->rightLayout->addWidget(this->bookPrice,1,1,1,-1);
    this->rightLayout->addWidget(this->bookTypeLabel,2,0);
    this->rightLayout->addWidget(this->bookType,2,1);
    this->rightLayout->addWidget(this->addBookBtn,3,0,1,-1);

    this->grid->addWidget(this->headerWidget,0,0,1,-1,Qt::AlignTop);
    this->grid->addWidget(this->image,1,0,-1,1);
    this->grid->addLayout(this->rightLayout,1,1,-1,2);

    this->grid->setVerticalSpacing(0);
    this->headerWidget->setMaximumHeight(100);

    this->widget->setMinimumWidth(700);
    this->widget->setMinimumHeight(400);
    this->widget->setLayout(this->grid);
}

void PublisherWidget::Signals_Slots()
{
    connect(this->toolBar,SIGNAL(actionTriggered(QAction*)),this,SLOT(handleToolBar(QAction*)));

    connect(this->addBookBtn,SIGNAL(clicked()),this,SLOT(bookDataCheck()));
    connect(this->EditBtn,SIGNAL(clicked()),this,SLOT(editButtonClicked()));
    connect(this->OkBtn,SIGNAL(clicked()),this,SLOT(okButtonClicked()));
}

void PublisherWidget::bookDataCheck()
{
    cout << "ray2" << endl;
    if(this->bookName->text().isEmpty() || this->bookType->text().isEmpty() || this->bookPrice->text().isEmpty())
    {
        this->errorBox->setText("Please Fill all the Required Data");
        this->errorBox->show();
        return;
    }

    string Name;
    string Type;
    int Price;
    Name  =this->bookName->text().toStdString();
    Type  =this->bookType->text().toStdString();
    Price =this->bookPrice->text().toInt();
    emit addBookData(this->currentPublisher.getName(),Name,Type,Price);

    // check box
    this->sucessBox->setText("Successfully Published Your Book !");
    this->sucessBox->show();
}

void PublisherWidget::initProfileWidget()
{
    this->ProfileWidget = new QWidget();
    this->ProfileWidget->setStyleSheet("background: #F6F5E4;color: #2E2E2E; font-size: 15px; font-weight: 400;");

    this->ProfileLayout = new QGridLayout();

    QLabel* name = new QLabel("Name:");             this->nameEdit = new QLineEdit(); nameEdit->setReadOnly(true); this->nameEdit->setStyleSheet("QLineEdit{ background-color:white;border: 2px solid #00BFFF;border-radius: 5px;}");
    QLabel* password = new QLabel("Password:");     this->passEdit = new QLineEdit(); passEdit->setReadOnly(true); this->passEdit->setStyleSheet("QLineEdit{ background-color:white;border: 2px solid #00BFFF;border-radius: 5px;}");
    QLabel* email = new QLabel("Email:");           this->emailEdit = new QLineEdit();emailEdit->setReadOnly(true);this->emailEdit->setStyleSheet("QLineEdit{ background-color:white;border: 2px solid #00BFFF;border-radius: 5px;}");
    QLabel* cashAmount = new QLabel("Cash Amount:");this->cashEdit = new QLineEdit(); cashEdit->setReadOnly(true); this->cashEdit->setStyleSheet("QLineEdit{ background-color:white;border: 2px solid #00BFFF;border-radius: 5px;}");

    this->EditBtn = new QPushButton("Edit");
    this->EditBtn->setStyleSheet("background: #00BFFF; border-radius: 10px; padding: 10px 0px; color: white; ");
    this->EditBtn->setCursor(Qt::PointingHandCursor);

    this->OkBtn = new QPushButton("Ok");
    this->OkBtn->setStyleSheet("background: #00BFFF; border-radius: 10px; padding: 10px 0px; color: white; ");
    this->OkBtn->setCursor(Qt::PointingHandCursor);

    QLabel *image; QPixmap* pixMap;
    image = new QLabel;
    pixMap =new QPixmap(QCoreApplication::applicationDirPath()+"/../../Library-Management-System/icons/person.png");
    image->setPixmap(pixMap->scaled(image->width()/4,image->height()/4,Qt::KeepAspectRatio) );
    image->setScaledContents(true);

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

    this->Name->setText(QString::fromStdString(this->currentPublisher.getName()));
}

void PublisherWidget::showInfoBtnClicked()
{
    this->ProfileWidget->show();
}

void PublisherWidget::handleToolBar(QAction * action)
{
    QString action_name = action->text();
    if(action_name == "Logout")
        emit setCurrentWidget(START_WIDGET);
    else if (action_name == "Profile")
        this->showInfoBtnClicked();
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

    this->sucessBox->setText("Edit Successfully !");
    this->sucessBox->show();
    this->ProfileWidget->hide();
}

