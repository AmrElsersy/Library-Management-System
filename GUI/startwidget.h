#ifndef STARTWIDGET_H
#define STARTWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QImage>
#include <QGridLayout>
#include <QCoreApplication>
#include <QLabel>
#include <QPixmap>
#include <QHBoxLayout>
#include <QSpacerItem>
#include "indexs.h"
#include <QToolBar>
#include <QToolButton>

class StartWidget : public QLabel
{
    Q_OBJECT
private:
    QGridLayout* grid;
    QIcon loginBtn , signupBtn;
    QString loginString , signupString;
    QPixmap* pixMap;
    QToolBar* toolBar;
public:
    StartWidget(QWidget *parent = nullptr);
    void initButtons();
    void Signals_Slots();

signals:
    void setCurrentWidget(int);

public slots:
    void ButtonClicked(QAction* action);
};

#endif // STARTWIDGET_H
