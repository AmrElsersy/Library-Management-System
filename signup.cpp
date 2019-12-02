#include "signupwidget.h"

SignUp::SignUp(QWidget* parent): QWidget(parent)
{
    this->grid = new QGridLayout;
    this->SignUpBtn = new QPushButton("Sign Up");
    this->BackBtn = new QPushButton("Back");

    this->Name = new QLineEdit;
    this->Email = new QLineEdit;
    this->Password = new QLineEdit;
    this->ConfirmPassword = new QLineEdit;

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
    this->Signals_Slots();
    this->setLayout(this->grid);
}

void SignUp::Design()
{
    this->grid->addWidget(this->nameLabel,0,0);
    this->grid->addWidget(this->Name,0,1,1,-1);

    this->grid->addWidget(this->emailLabel,1,0);
    this->grid->addWidget(this->Email,1,1,1,-1);

    this->grid->addWidget(this->passLabel,2,0);
    this->grid->addWidget(this->Password,2,1,1,-1);

    this->grid->addWidget(this->confirmLabel,3,0);
    this->grid->addWidget(this->ConfirmPassword,3,1,1,-1);

    this->grid->addWidget(this->publisherBtn,4,0);
    this->grid->addWidget(this->studentBtn,4,1);

    QHBoxLayout* verticalLayout = new QHBoxLayout;
    verticalLayout->addWidget(this->SignUpBtn);
    verticalLayout->addWidget(this->BackBtn);
    this->grid->addLayout(verticalLayout,5,0,1,-1);
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
    emit setCurrentWidget(START_WIDGET);
}
