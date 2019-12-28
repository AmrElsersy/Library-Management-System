#include "imagewidget.h"

imageWidget::imageWidget(string name , string imagePath) : QWidget()
{
    this->layout = new QVBoxLayout();
    this->label = new QLabel;
    this->Name = new QLabel(QString::fromStdString(name));

    if(imagePath != "")
        this->pixMap =new QPixmap(QCoreApplication::applicationDirPath() + QString::fromStdString(imagePath));
    else
        this->pixMap = new QPixmap(QCoreApplication::applicationDirPath() + "/../../Library-Management-System/icons/book1.png");
    this->label->setPixmap(pixMap->scaled(this->width(),this->height(),Qt::KeepAspectRatio) );
    this->label->setScaledContents(true);


    this->layout->addWidget(label);
    this->layout->addWidget(Name,0,Qt::AlignCenter);
    this->setLayout(this->layout);
}

void imageWidget::mousePressEvent(QMouseEvent *event)
{
    cout  << this->Name->text().toStdString() << " widget ray2 is clicked " << endl;
    emit bookClicked(this->Name->text().toStdString());
}
