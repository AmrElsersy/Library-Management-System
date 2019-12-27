#include "startwidget.h"
StartWidget::StartWidget(QWidget *parent) : QLabel(parent)
{
    this->grid = new QGridLayout();

    this->pixMap =new QPixmap(QCoreApplication::applicationDirPath()+"/../../Library-Management-System/background/blur5.jpg");
    this->setPixmap(pixMap->scaled(this->width(),this->height(),Qt::KeepAspectRatio) );
    this->setScaledContents(true);

    this->initButtons();

    this->grid->addWidget(this->toolBar,0,0,Qt::AlignCenter);
    this->setLayout(this->grid);
    this->setMinimumSize(MIN_SIZE);

    this->Signals_Slots();

}

void StartWidget::initButtons()
{
    this->toolBar =new QToolBar("");
    this->toolBar->setCursor(Qt::PointingHandCursor);
    this->loginBtn= QIcon(QCoreApplication::applicationDirPath()+"/../../Library-Management-System/icons/login6.png");
    this->signupBtn = QIcon (QCoreApplication::applicationDirPath()+"/../../Library-Management-System/icons/signup.png");    
    this->loginString  = "Login";
    this->signupString = "Sign Up";
    this->toolBar->addAction(this->loginBtn,this->loginString);
    this->toolBar->addAction(this->signupBtn,this->signupString);
    this->toolBar->setIconSize(QSize(200,200));
    this->toolBar->setOrientation(Qt::Horizontal);
    this->toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    this->toolBar->setStyleSheet("QToolButton:hover{padding: 15px;}"
                                 "QToolButton:select{padding: 15px;}"
                                 "QToolButton{color:white; font-weight: bold; margin:10px;"
                                 " padding: 30px; border-radius: 50; font-size: 30px;}");
}

void StartWidget::Signals_Slots()
{
    connect(this->toolBar,SIGNAL(actionTriggered(QAction*)),this,SLOT(ButtonClicked(QAction*)));
}

void StartWidget::ButtonClicked(QAction *action)
{
    if (action->text() == this->loginString )
        emit setCurrentWidget(LOGIN_WIDGET);
    else if (action->text() == this->signupString)
        emit setCurrentWidget(SIGNUP_WIDGET);
}
