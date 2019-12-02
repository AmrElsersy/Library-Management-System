#include "user.h"

User::User()
{

}

User::User(string name , string email , string password)
{
    Name  = name ;
    Email = email ;
    Password = password ;
}

void User::setName(string name)
{
    Name = name ;
}
void User::setEmail(string email)
{
    Email = email ;
}
void User::setPassword(string password)
{
    Password = password ;
}

void User::addCash(int cash)
{
    cash_amount += cash ;
}

void User::setCash(int cash)
{
    this->cash_amount = cash;
}
string User::getName()
{
    return this->Name ;
}
string User::getEmail()
{
    return this->Email ;
}
string User::getPassword()
{
    return Password ;
}

int User::getCash()
{
    return cash_amount  ;
}

void User::showInfo()
{
    cout <<"Your info : "<<endl;
    cout << "Name : " << Name << endl << "E-mail : " << Email << endl << "Cash Amount : "<< cash_amount << endl;
}
