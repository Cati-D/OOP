#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <typeinfo>
#include <errno.h>
#include <stdexcept>
#include "myClass.h"

using namespace std;

quiz::quiz()
{
    setMark(0);
    setOralMark(0);
    setExtraPoints(0);
    setNameNull();
    numberItems = 0;
    qmark = 0;
    cout<<"Constructor fara parametri quiz."<<endl;
}

quiz::quiz(finalExam ob, int n, double n2)
{
    if (ob.getName() == NULL)
        throw runtime_error("Obiectul de tip exam nu are nume.");
    setName(ob.getName());
    setMark(ob.getMark());
    setOralMark(0);
    setExtraPoints(0);
    numberItems = n;
    qmark = n2;

    cout<<"Constructor parametrizat quiz."<<endl;
}

quiz::quiz(char *name1, double m1, double m2, double m3, int n, double n2):finalExam(name1, m1, m2, m3)
{
    if (!strlen(name1))
        throw runtime_error("Nu a fost introdus numele partialului.");
    numberItems = n;
    qmark = n2;

    cout<<"Constructor cu parametri quiz."<<endl;
}

quiz::~quiz()
{
    setMark(0);
    setNameNull();
    setOralMark(0);
    setExtraPoints(0);
    numberItems = 0;
    qmark = 0;
    cout<<"Destructor quiz."<<endl;
}

quiz::quiz(const quiz& ob)
{
    setNr(ob.getNr());
    setMark(ob.getMark());
    setOralMark(ob.getOralMark());
    setExtraPoints(ob.getExtraPoints());
    setNameNull();
    if (ob.getName() != NULL)
        setName(ob.getName());
    numberItems = ob.numberItems;
    qmark = ob.qmark;

    cout<<"Constructor de copiere quiz."<<endl;
}

void quiz::operator=(const quiz& ob)
{
    setNr(ob.getNr());
    setMark(ob.getMark());
    setNameNull();
    setName(ob.getName());
    setOralMark(ob.getOralMark());
    setExtraPoints(ob.getExtraPoints());
    numberItems = ob.numberItems;
    qmark = ob.qmark;
}

istream& operator>>(istream& in, quiz& ob)
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
    ob.setOralMark(n3);

    cout<<"Introduceti numarul de extrapuncte: ";
    double n4;
    in>>n4;
    if (n4 < 0)
        throw runtime_error("Extra-punctele nu pot fi negative.");
    ob.setExtraPoints(n4);

    cout<<"Introduceti numarul de itemi de tip grila: ";
    int n5;
    in>>n5;
    if (n5 < 1)
        throw runtime_error("Quiz-ul trebuie sa contina cel putin un item.");
    ob.numberItems = n5;

    cout<<"Introduceti nota obtinuta in urma quiz-ului(quiz-ul aduce maxim 0.1*numberItems puncte): ";
    double n6;
    in>>n6;
    if (n6 <0 || n6 > ob.numberItems*0.1)
        throw runtime_error("Quiz-ul aduce cel mult 0.1*numberItems puncte..");
    ob.qmark = n6;

    return in;
}

