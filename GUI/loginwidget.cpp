#include "loginwidget.h"

LogInWidget::LogInWidget(QWidget* parent): QWidget(parent)
{
    this->grid = new QGridLayout;
    this->LogInBtn = new QPushButton("Log In");
    this->LogInBtn->setStyleSheet("background: #2e2e2e; border-radius: 10px; padding: 10px 0px; color: white; ");
    this->LogInBtn->setCursor(Qt::PointingHandCursor);

    this->BackBtn = new QPushButton("Back");
    this->BackBtn->setStyleSheet("background: #2e2e2e; border-radius: 10px; padding: 10px 0px; color: white; ");
    this->BackBtn->setCursor(Qt::PointingHandCursor);

    this->Name = new QLineEdit;
    this->Name->setStyleSheet("background: white;");
    this->Password = new QLineEdit;
    this->Password->setStyleSheet("background: white;");

    this->nameLabel = new QLabel("Name");
    this->passLabel = new QLabel("Password");

    this->publisherBtn = new QRadioButton("Publisher");
    this->studentBtn = new QRadioButton("Student");
    this->studentBtn->setChecked(true);

    this->errorBox = new QMessageBox();
    this->errorBox->setWindowIcon(QIcon(QCoreApplication::applicationDirPath()+"/../../Library-Management-System/icons/error.png"));

    this->Design();
    this->Signals_Slots();
    this->setLayout(this->grid);
}

void LogInWidget::Design()
{
    this->grid->addWidget(this->nameLabel,0,0);
    this->grid->addWidget(this->Name,0,1,1,-1);

    this->grid->addWidget(this->passLabel,2,0);
    this->grid->addWidget(this->Password,2,1,1,-1);

    this->grid->addWidget(this->publisherBtn,3,0);
    this->grid->addWidget(this->studentBtn,3,1);

    QHBoxLayout* verticalLayout = new QHBoxLayout;
    verticalLayout->addWidget(this->LogInBtn);
    verticalLayout->addWidget(this->BackBtn);
    this->grid->addLayout(verticalLayout,4,0,1,-1);
}

void LogInWidget::Signals_Slots()
{
    connect(this->LogInBtn,SIGNAL(clicked()),this,SLOT(LogInWidgetCheck()));
    connect(this->BackBtn,SIGNAL(clicked()),this,SLOT(buttonBack()));
}

void LogInWidget::LogInWidgetCheck()
{
    cout << "ray2" << endl;
    if(this->Name->text().isEmpty() || this->Password->text().isEmpty())
    {
        this->errorBox->setText("Please Fill all");
        this->errorBox->show();
        return;
    }
    string name,pass,email;int type=0;
    name=this->Name->text().toStdString();
    pass=this->Password->text().toStdString();
    if(this->studentBtn->isChecked())type=1;
    if(this->publisherBtn->isChecked())type=2;
    emit LogInWidgetData(name,pass,type);
}

void LogInWidget::error(string text)
{
    this->errorBox->setText(QString::fromStdString(text));
    this->errorBox->show();
}

void LogInWidget::buttonBack()
{
    emit setCurrentWidget(START_WIDGET);
}
