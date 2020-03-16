#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <typeinfo>
#include <errno.h>
#include <stdexcept>
#include "myClass.h"

using namespace std;

finalExam::finalExam()
{
    setMark(0);
    setNameNull();
    extraPoints = 0;
    cout<<"Constructor fara parametru finalExam."<<endl;
}

finalExam::finalExam(partial ob, double m)
{
    if (ob.getName() == NULL)
        throw runtime_error("Obiectul de tip exam nu are nume.");
    setName(ob.getName());
    setMark(ob.getMark());
    setOralMark(ob.getOralMark());
    extraPoints = m;

    cout<<"Constructor parametrizat finalExam."<<endl;
}

finalExam::finalExam(char *name1, double m1, double m2, double m3):partial(name1, m1, m2)
{
    if (!strlen(name1))
        throw runtime_error("Nu a fost introdus numele partialului.");
    extraPoints = m3;

    cout<<"Constructor cu parametri finalExam."<<endl;
}

finalExam::~finalExam()
{
    setMark(0);
    setOralMark(0);
    setNameNull();
    extraPoints = 0;
    cout<<"Destructor finalExam."<<endl;
}

finalExam::finalExam(const finalExam& ob)
{
    setNr(ob.getNr());
    setOralMark(ob.getOralMark());
    setMark(ob.getMark());
    setNameNull();
    if (ob.getName() != NULL)
        setName(ob.getName());
    extraPoints = ob.extraPoints;
    cout<<"Constructor de copiere finalExam."<<endl;
}

void finalExam:: operator=(const finalExam& ob)
{
    setNr(ob.getNr());
    setOralMark(ob.getOralMark());
    setMark(ob.getMark());
    setNameNull();
    setName(ob.getName());
    extraPoints = ob.extraPoints;
}

istream& operator>>(istream&in, finalExam& ob)
{
    cout<<"Introduceti numele examenului: ";
    char n1[100];
    in>>n1;
    if (!strlen(n1))
        throw runtime_error("Nu a fost introdus un nume.");
    ob.setName(n1);

    cout<<"Introduceti nota luata la examenul scris: ";
    double n2;
    in>>n2;
    if (n2 < 0)
        throw runtime_error("Nota examenului scris nu poate avea valori negative.");
    if (n2 > 10)
        throw runtime_error("Nota examenului scris nu poate fi mai mare decat 10.");
    ob.setMark(n2);

    cout<<"Introduceti nota luata la examenul oral: ";
    double n3;
    in>>n3;
    if (n3 < 0)
        throw runtime_error("Nota examenului oral nu poate avea valori negative.");
    if (n3 > 10)
        throw runtime_error("Nota examenului oral nu poate fi mai mare decat 10.");
    ob.setOralMark(n3);

    cout<<"Introduceti numarul de extrapuncte: ";
    double n4;
    in>>n4;
    if (n4 < 0)
        throw runtime_error("Extra-punctele nu pot fi negative.");
    ob.extraPoints = n4;

    return in;
}
