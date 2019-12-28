#include "loginwidget.h"

LogInWidget::LogInWidget(QWidget* parent): QWidget(parent)
{
    this->main_grid = new QGridLayout;
    this->widget = new QWidget;

    this->image = new QLabel;
    this->pixMap =new QPixmap(QCoreApplication::applicationDirPath()+"/../../Library-Management-System/icons/laptop.jpg");
    this->image->setPixmap(pixMap->scaled(this->image->width()/2,this->image->height()/2,Qt::KeepAspectRatio) );
    this->image->setScaledContents(true);

    this->grid = new QGridLayout;
    this->LogInBtn = new QPushButton("Log In");
    this->LogInBtn->setStyleSheet("background: #00BFFF; border-radius: 10px; padding: 10px 0px; color: white; ");
    this->LogInBtn->setCursor(Qt::PointingHandCursor);

    this->BackBtn = new QPushButton("Back");
    this->BackBtn->setStyleSheet("background: #00BFFF; border-radius: 10px; padding: 10px 0px; color: white; ");
    this->BackBtn->setCursor(Qt::PointingHandCursor);

    this->Name = new QLineEdit;
    this->Name->setStyleSheet("QLineEdit{ background-color:white;border: 2px solid #00BFFF;border-radius: 5px;}");
    this->Password = new QLineEdit;
    this->Password->setStyleSheet("QLineEdit{ background-color:white;border: 2px solid #00BFFF;border-radius: 5px;}");

    this->nameLabel = new QLabel("Name");   this->nameLabel->setStyleSheet("color:black;");
    this->passLabel = new QLabel("Password"); this->passLabel->setStyleSheet("color:black;");

    this->publisherBtn = new QRadioButton("Publisher");
    this->studentBtn = new QRadioButton("Student");
    this->studentBtn->setChecked(true);

    this->errorBox = new QMessageBox();
    this->errorBox->setWindowIcon(QIcon(QCoreApplication::applicationDirPath()+"/../../Library-Management-System/icons/error.png"));

    this->Design();
    this->outDesign();
    this->Signals_Slots();
}

void LogInWidget::Design()
{
    this->widget->setStyleSheet("background-color:white;");
    this->grid->addWidget(this->image,0,0,-1,1);

    QGridLayout* tempGrid = new QGridLayout;
    tempGrid->addWidget(this->nameLabel,0,0);
    tempGrid->addWidget(this->Name,0,1,1,-1);
    tempGrid->addWidget(this->passLabel,1,0);
    tempGrid->addWidget(this->Password,1,1,1,-1);

    tempGrid->addWidget(this->publisherBtn,2,0);
    tempGrid->addWidget(this->studentBtn,2,1);

    QHBoxLayout* verticalLayout = new QHBoxLayout;
    verticalLayout->addWidget(this->LogInBtn);
    verticalLayout->addWidget(this->BackBtn);
    tempGrid->addLayout(verticalLayout,3,0,1,-1);

    this->grid->addLayout(tempGrid,0,1,-1,2);
    this->widget->setMinimumWidth(700);
    this->widget->setMinimumHeight(400);

    this->widget->setLayout(this->grid);
}

void LogInWidget::outDesign()
{
    QWidget *w1 = new QWidget; QWidget *w2 = new QWidget;
    this->main_grid->addWidget(w1,0,0,1,3);
    this->main_grid->addWidget(w2,2,0,1,3);

    this->main_grid->addWidget(this->widget,1,1);
    this->setLayout(this->main_grid);
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
