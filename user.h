#ifndef PERSON_H
#define PERSON_H
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class User
{
protected:
    string Name;
    string Email;
    string Password;
    int cash_amount=0;
public:
    User(string name , string email , string password);
    User();
    // ========== Setters ==========
    void setName(string name);
    void setEmail(string email);
    void setPassword(string password);
    void addCash(int cash);
    void setCash(int cash);
    // ========== Getters ==========
    string getName();
    string getEmail();
    string getPassword();
    int   getCash();
    // =============================
    void showInfo();
    bool operator == (User&); // in searching compare name(or id) and passwords

};

#endif // PERSON_H
