#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <typeinfo>
#include <errno.h>
#include <stdexcept>
#include "myClass.h"

using namespace std;

int exam::nr = 0;

exam::exam()
{
    nr++;
    mark = 0;
    name = NULL;
    cout<<"Constructor fara parametru exam."<<endl;
}

exam::exam( char* name1, double m)
{

    if (!strlen(name1))
        throw runtime_error("Nu a fost introdus numele examenului.");
    name = new char[strlen(name1)];
    strcpy(name, name1);

    if (m < 0)
        throw runtime_error("Nota introdusa are valoare negativa.");
    mark = m;

    cout<<"Consructor parametri exam."<<endl;
}

exam::~exam()
{
    --nr; //nu se decrementeaza la afisare
    //delete[] name;  //nu merge daca eliberez aici
    mark = 0;
    cout<<"Destructor exam."<<endl;
}

exam::exam(const exam& ob)
{
    this->nr = ob.nr + 1;
    this->mark = ob.mark;
    delete[] this->name;
    if (ob.name == NULL)
        this->name = NULL;
    else
    {
        this->name = new char[strlen(ob.name) + 1];
        strcpy(this->name, ob.name);
    }
    cout<<"Constructor de copiere exam."<<endl;
}

void exam:: operator=(const exam& ob)
{
    this->nr = ob.nr;
    this->mark = ob.mark;
    delete[] this->name;
    this->name = new char[strlen(ob.name)];
    strcpy(this->name, ob.name);
}


istream& operator>>(istream& in, exam& ob)
{
    cout<<"Introduceti numele examenului: ";
    char s[100];
    in>>s;
    if (!strlen(s))
        throw runtime_error("Nu a fost introdus un nume.");
    ob.name = new char[strlen(s + 1)];
    strcpy(ob.name, s);

    cout<<"Introduceti nota examenului: ";
    double n2;
    in>>n2;
    if (n2 < 0)
        throw runtime_error("Nota examenului nu poate avea valori negative.");
    if (n2 > 10.0)
        throw runtime_error("Nota examenului nu poate fi mai mare decat 10.");
    ob.mark = n2;

    return in;
}

