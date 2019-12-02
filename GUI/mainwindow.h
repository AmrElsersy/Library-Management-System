#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "indexs.h"
#include <QMainWindow>
#include "controller.h"
#include "librarian.h"
#include "studentwidget.h"
#include "startwidget.h"
#include "signupwidget.h"
#include "publisherwidget.h"
#include <QStackedWidget>
#include "loginwidget.h"
#include "bookwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QStackedWidget* stackWidget;
    Controller* controller;
    Librarian* librarian;
    StudentWidget* studentWidget;
    StartWidget * startWidget;
    SignUp* signUpWidget;
    LogInWidget* logInWidget;
    PublisherWidget* publisherWidget;
    BookWidget* bookWidget;
public:
    MainWindow(QWidget *parent = nullptr);
    void Design();
    void Signals_Slots();

public slots:
    void changeCurrentWidget(int);

};

#endif // MAINWINDOW_H
