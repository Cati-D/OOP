#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <typeinfo>
#include <errno.h>
#include <stdexcept>
#include "myClass.h"

using namespace std;

partial::partial()
{
    oralMark = 0;
    setNameNull();
    setMark(0);
    cout<<"Constriuctor fara parametru partial."<<endl;

}

partial::partial(exam ob, double m)
{
    if (ob.getName() == NULL)
        throw runtime_error("Obiectul de tip exam nu are nume.");
    setName(ob.getName());
    setMark(ob.getMark());
    oralMark = m;

    cout<<"Constructor cu parametri partial."<<endl;
}

partial::partial(char *name1, double m1, double m2):exam(name1, m1)
{
    if (!strlen(name1))
        throw runtime_error("Nu a fost introdus numele partialului.");
    oralMark = m2;

    cout<<"Constructor cu parametri partial."<<endl;
}

partial::~partial()
{
    setNameNull();
    setMark(0);
    oralMark = 0;
    cout<<"Destructor partial."<<endl;
}

partial::partial(const partial& ob)
{
    setNameNull();
    if (ob.getName() != NULL)
        setName(ob.getName());
    setNr(ob.getNr());
    setMark(ob.getMark());
    oralMark = ob.oralMark;
    cout<<"Constructor de copiere partial."<<endl;

}

void partial:: operator=(const partial& ob)
{
    setNr(ob.getNr());
    setNameNull();
    setName(ob.getName());
    setMark(ob.getMark());
    oralMark = ob.oralMark;
}

istream& operator>>(istream& in, partial& ob)
{

    cout<<"Introduceti numele examenului: ";
    char n1[100];
    in>>n1;
    if (!strlen(n1))
        throw runtime_error("Nu a fost introdus un nume.");
    ob.setName(n1);

    cout<<"Introduceti nota luata la examen: ";
    double n2;
    in>>n2;
    if (n2 < 0)
        throw runtime_error("Nota examenului nu poate avea valori negative.");
    if (n2 > 10)
        throw runtime_error("Nota examenului nu poate fi mai mare decat 10.");
    ob.setMark(n2);

    cout<<"Introduceti nota luata la examenul oral: ";
    double n3;
    in>>n3;
    if (n3 < 0)
        throw runtime_error("Nota examenului oral nu poate avea valori negative.");
    if (n3 > 10)
        throw runtime_error("Nota examenului oral nu poate fi mai mare decat 10.");
    ob.oralMark = n3;

    return in;
}
