#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H
#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>
#include <QPixmap>
#include <string>
#include <iostream>
#include <QCoreApplication>
using namespace std;
class imageWidget : public QWidget
{
    Q_OBJECT
private:
    QLabel* label;
    QPixmap* pixMap;
    QLabel* Name;
    QVBoxLayout* layout;
public:
    imageWidget(string name , string imagePath);
protected:
    void mousePressEvent(QMouseEvent *event) ;
signals:
    void bookClicked(string name);
};

#endif // IMAGEWIDGET_H
