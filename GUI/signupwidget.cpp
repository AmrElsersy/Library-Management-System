#include "signupwidget.h"

SignUp::SignUp(QWidget* parent): QWidget(parent)
{
    this->main_grid = new QGridLayout;
    this->widget = new QWidget;

    this->image = new QLabel;
    this->pixMap =new QPixmap(QCoreApplication::applicationDirPath()+"/../../Library-Management-System/icons/signup.jpg");
    this->image->setPixmap(pixMap->scaled(this->image->width()/2,this->image->height()/2,Qt::KeepAspectRatio) );
    this->image->setScaledContents(true);

    this->grid = new QGridLayout;
    this->SignUpBtn = new QPushButton("Sign Up");
    this->SignUpBtn->setStyleSheet("background: #00BFFF; border-radius: 10px; padding: 10px 0px; color: white;");
    this->SignUpBtn->setCursor(Qt::PointingHandCursor);
    this->BackBtn = new QPushButton("Back");
    this->BackBtn->setStyleSheet("background: #00BFFF; border-radius: 10px; padding: 10px 0px; color: white; ");
    this->BackBtn->setCursor(Qt::PointingHandCursor);
    this->Name = new QLineEdit;
    this->Name->setStyleSheet("QLineEdit{ background-color:white;border: 2px solid #00BFFF;border-radius: 5px;}");

    this->Email = new QLineEdit;
    this->Email->setStyleSheet("QLineEdit{ background-color:white;border: 2px solid #00BFFF;border-radius: 5px;}");

    this->Password = new QLineEdit;
    this->Password->setStyleSheet("QLineEdit{ background-color:white;border: 2px solid #00BFFF;border-radius: 5px;}");

    this->ConfirmPassword = new QLineEdit;
    this->ConfirmPassword->setStyleSheet("QLineEdit{ background-color:white;border: 2px solid #00BFFF;border-radius: 5px;}");

    this->nameLabel = new QLabel("Name");
    this->emailLabel= new QLabel("Email");
    this->passLabel = new QLabel("Password");
    this->confirmLabel = new QLabel("Confirm Password");

    this->publisherBtn = new QRadioButton("Publisher");
    this->studentBtn = new QRadioButton("Student");
    this->studentBtn->setChecked(true);

    this->errorBox = new QMessageBox();
    this->errorBox->setWindowIcon(QIcon(QCoreApplication::applicationDirPath()+"/../../Library-Management-System/icons/error.png"));

    this->Design();
    this->outDesign();
    this->Signals_Slots();
}
void SignUp::outDesign()
{
    QWidget *w1 = new QWidget; QWidget *w2 = new QWidget;
    this->main_grid->addWidget(w1,0,0,1,3);
    this->main_grid->addWidget(w2,2,0,1,3);

    this->main_grid->addWidget(this->widget,1,1);
    this->setLayout(this->main_grid);
}
void SignUp::Design()
{
    this->widget->setStyleSheet("background-color:white;");
    this->grid->addWidget(this->image,0,0,-1,1);

    QGridLayout* tempGrid = new QGridLayout;
    tempGrid->addWidget(this->nameLabel,0,0);
    tempGrid->addWidget(this->Name,0,1,1,-1);

    tempGrid->addWidget(this->emailLabel,1,0);
    tempGrid->addWidget(this->Email,1,1,1,-1);

    tempGrid->addWidget(this->passLabel,2,0);
    tempGrid->addWidget(this->Password,2,1,1,-1);

    tempGrid->addWidget(this->confirmLabel,3,0);
    tempGrid->addWidget(this->ConfirmPassword,3,1,1,-1);

    tempGrid->addWidget(this->publisherBtn,4,0);
    tempGrid->addWidget(this->studentBtn,4,1);

    QHBoxLayout* verticalLayout = new QHBoxLayout;
    verticalLayout->addWidget(this->SignUpBtn);
    verticalLayout->addWidget(this->BackBtn);
    tempGrid->addLayout(verticalLayout,5,0,1,-1);

    this->grid->addLayout(tempGrid,0,1,-1,2);
    this->widget->setMinimumWidth(700);
    this->widget->setMinimumHeight(400);

    this->widget->setLayout(this->grid);
}

void SignUp::Signals_Slots()
{
    connect(this->SignUpBtn,SIGNAL(clicked()),this,SLOT(signUpCheck()));
    connect(this->BackBtn,SIGNAL(clicked()),this,SLOT(buttonBack()));
}

void SignUp::signUpCheck()
{
    cout << "ray2" << endl;
    if(this->Name->text().isEmpty() || this->Email->text().isEmpty() || this->Password->text().isEmpty()
            || this->ConfirmPassword->text().isEmpty() )
    {
        this->errorBox->setText("Please Fill all");
        this->errorBox->show();
        return;
    }
    if (this->Password->text() != this->ConfirmPassword->text())
    {
        this->errorBox->setText("Passwords Don't Match");
        this->errorBox->show();
        return;
    }

    string name,pass,email;int type=0;
    name=this->Name->text().toStdString();
    email=this->Email->text().toStdString();
    pass=this->Password->text().toStdString();
    if(this->studentBtn->isChecked())type=1;
    if(this->publisherBtn->isChecked())type=2;

    emit signUpData(name,email,pass,type);
}

void SignUp::error(string text)
{
    this->errorBox->setText(QString::fromStdString(text));
    this->errorBox->show();
}

void SignUp::buttonBack()
{
    emit setCurrentWidget(0);
}
