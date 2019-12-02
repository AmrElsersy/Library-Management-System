#include "publisher.h"
#include "book.h"

Publisher::Publisher() : User()
{

}

Publisher::Publisher(string name, string password, string email) : User(name,email,password)
{

}

void Publisher::showInfo()
{
    cout <<"User's info : "<<endl;
    cout << "Name : " << this->Name << endl << "E-mail : " << Email << endl << "Cash Amount : "<< cash_amount << endl;
    cout << "myBooks:" << endl;
    for (int i =0 ; i < this->my_books_names.size() ; i++)
        cout << this->my_books_names[i] << " ";
    cout << endl;
}

void Publisher::addBook(Book *Published_Book)
{
    this->my_books.push_back(Published_Book);
}
void Publisher::RemoveBook(Book *Removed_Book)
{
    for(unsigned int i = 0; i < my_books.size(); i++)
    {
        if(Removed_Book == my_books[i])
            my_books.erase(my_books.begin()+i);
    }
}

void Publisher::addBook(string Published_Book)
{
    this->my_books_names.push_back(Published_Book);
}

void Publisher::RemoveBook(string Removed_Book)
{
    for(unsigned int i = 0; i < my_books_names.size(); i++)
    {
        if(Removed_Book == my_books_names[i])
            my_books_names.erase(my_books_names.begin()+i);
    }
}
Book Publisher::getMyBook(int i)
{
    return *(my_books[i]);
}
int Publisher::pubBooksNum()
{
    return my_books.size();
}

vector<string> Publisher::viewMyBooks()
{
    vector<string> s;
    for (int i =0 ; i < this->my_books_names.size() ; i++)
        s.push_back(this->my_books_names[i]);
    return s;
}
