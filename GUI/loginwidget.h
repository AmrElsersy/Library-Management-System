#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QRadioButton>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QCoreApplication>
#include <QIcon>
#include <iostream>
#include <QDebug>
#include "indexs.h"

using namespace std;

class LogInWidget : public QWidget
{
    Q_OBJECT
private:
    QGridLayout* main_grid;

    QWidget* widget;
    QGridLayout* grid;

    QLabel* image;
    QPixmap* pixMap;

    QPushButton* LogInBtn;
    QPushButton* BackBtn;
    QLineEdit* Name;            QLabel* nameLabel;
    QLineEdit* Password;        QLabel* passLabel;

    QRadioButton* publisherBtn;
    QRadioButton* studentBtn;

    QMessageBox* errorBox;

public:
    LogInWidget(QWidget* parent = nullptr);
    void Design();
    void outDesign();
    void Signals_Slots();

signals:
    void LogInWidgetData(string,string,int);
    void setCurrentWidget(int);

public slots:
    void LogInWidgetCheck();
    void error(string);
    void buttonBack();

};

#endif // LOGINWIDGET_H
