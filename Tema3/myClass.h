#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <typeinfo>
#include <errno.h>
#include <stdexcept>
#ifndef MYCLASS_H_INCLUDED
#define MYCLASS_H_INCLUDED

using namespace std;

class exam
{
    static int nr;
    char* name;
    double mark;
public:
    exam();
    exam(char* name1, double m);
    ~exam();
    int getNr()const{return nr;}
    void setNrm(){nr--;}
    void setNr(int val){nr = val;}
    void setNrp(){nr++;}
    char* getName()const{return name;}
    void setName(char* name1)
    {
        delete[] name;
        name = new char[strlen(name1)];
        strcpy(name, name1);
    }
    void setNameNull(){name = NULL;}
    double getMark()const{return mark;}
    void setMark(double val){mark = val;}
    exam(const exam& ob);
    friend istream& operator>>(istream& in, exam& ob);
    void operator=(const exam& ob);
    virtual void display(ostream& out)
    {
        out<<"Numar examen: ";
        out<<nr<<".";
        nr--;
        out<<"Nume materie: ";
        out<<name<<", ";
        out<<"Nota obtinuta la examen este: ";
        out<<mark<<endl;
    }
};


class partial:public exam
{
    double oralMark;
public:
    partial();
    partial(exam ob, double m);
    partial(char *name1, double m1, double m2);
    ~partial();
    partial(const partial& ob);
    void setOralMark(double val){oralMark = val;}
    double getOralMark()const {return oralMark;}
    friend istream& operator>>(istream& in, partial& ob);
    void operator=(const partial& ob);
    void display(ostream& out)
    {
        this->exam::display(out);
        out<<"Nota obtinuta la examenul oral este: ";
        out<<oralMark<<endl;
    }

};

class finalExam:public partial
{
    double extraPoints;
public:
    finalExam();
    finalExam(partial ob, double m);
    finalExam(char* name1, double m1, double m2, double m3);
    ~finalExam();
    finalExam(const finalExam& ob);
    void setExtraPoints(double val){extraPoints = val;}
    double getExtraPoints()const {return extraPoints;}
    friend istream& operator>>(istream& in, finalExam& ob);
    void operator=(const finalExam& ob);
    void display(ostream& out)
    {
        this->partial::display(out);
        if (getOralMark() < 5)
        {
            out<<"Reintroduceti o nota mai mare egala cu 5 pentru ca partialul sa fie luat: ";
            double newom;
            cin>>newom;
            setOralMark(newom);
        }
        if (getOralMark() < 5)
            out<<"##########Examenul a fost picat.#########"<<endl;
        else
        {
            out<<"Noua nota luata la partial este: "<<getOralMark()<<endl;
            out<<"Numarul de extra-puncte este(nu poate fi mai mare de 2p): ";
            double newex  = extraPoints;
            if (extraPoints >= 2)
                newex = 2;
            out<<newex<<endl;
            out<<"Nota finala este deci: ";
            double n = static_cast<double>((getMark() + getOralMark())/2 + newex);
            if (n >= 10.0)
                cout<<10<<endl;
            else cout<<n<<endl;
       }

    }

};

class quiz:public finalExam
{
    int numberItems;
    double qmark;
public:
    quiz();
    quiz(finalExam ob, int n, double n2);
    quiz(char* name1, double m1, double m2, double m3, int n, double n2);
    ~quiz();
    void setNumberItems(int val){numberItems = val;}
    int getNumberItems()const {return numberItems;}
    double getQmark()const {return qmark;}
    quiz(const quiz& ob);
    friend istream& operator>>(istream& in, quiz& ob);
    void display(ostream& out)
    {
        this->finalExam::display(out);
        out<<"Numarul de itemi pe care il contine quiz-ul este: ";
        out<<numberItems<<endl;
        out<<"la noua nota finala se mai adauga: ";
        out<<qmark;
        out<<" puncte"<<endl;
    }
    void operator=(const quiz& ob);
};

template <class Ttype> class individualCatalog
{
    char pr[10];
    static int registrationNumber;
    Ttype mAvg;
    int numberExams;
    exam **v; //vector de pointeri la obiecte de tip examen, intreb daca vreau ca datele sa fie de tipul derivatelor
public:
    individualCatalog():numberExams(0){cout<<"Constructor fara parametri individualCatalog."<<endl;}
    individualCatalog(Ttype x):mAvg(x)
    {
        pr = NULL;
        numberExams = 0;
        v = NULL;
        registrationNumber++;
        cout<<"Constructor parametri individualCatalog."<<endl;
    }
    individualCatalog(Ttype x, int n):numberExams(n),mAvg(x)
    {
        pr = NULL;
        v = NULL;
        registrationNumber++;
        cout<<"Constructor parametri individualCatalog."<<endl;
    }
    ~individualCatalog();
    individualCatalog(const individualCatalog& ob);
    static void setRegistrationNumber(){registrationNumber++;}
    int getRegistrationNumber(){return registrationNumber;}
    void operator=(const individualCatalog& ob);
    void calc_Avg(individualCatalog& ob);
    friend ostream& operator<<(ostream& out, const individualCatalog<Ttype>& ob)
    {
        for (int i = 0; i < ob.numberExams; i++)
            {
                out<<ob.registrationNumber<<'.';
                out<<ob.v[i];
                ob.calc_Avg(ob);
                out<<"Media este: "<<ob.mAvg;
            }
        return out;

    }
    void setNumberExams(int val){numberExams = val;}
    int getNumberExams()const {return numberExams;}

    template<class U>
    friend istream& operator>>(istream& in, individualCatalog<U>& ob);
    void operator+=(const individualCatalog& ob);
    unsigned calc_Avg_examFin(individualCatalog& ob);
};


template<class Ttype>
int individualCatalog<Ttype>::registrationNumber = 0;

template <class Ttype>
individualCatalog<Ttype>::~individualCatalog<Ttype>()
{
    Ttype mAvg = 0;
    for (int i = 0; i < numberExams; i++)
        delete[] v[i];
    registrationNumber--;  //decrementez variabila statica la fiecare apel al destructorului
    numberExams = 0;

    cout<<"Destructor individualCatalog."<<endl;
}

template<class U>
istream& operator>>(istream& in, individualCatalog<U>& ob)
{
    cout<<"Introduceti numarul de examene: ";
    int n1;
    in>>n1;
    if (n1 < 1)
        throw runtime_error("Trebuie sa existe minim un examen.");
    ob.numberExams = n1;

    cout<<"Introduceti examenele: ";
    for (int i = 0; i < ob.numberExams; i++)
    {
        cout<<"Ce fel de examen doriti sa introduceti?(1-partial/2-finalExam/3-quiz): ";
        int n2;
        in>>n2;
        switch(n2)
        {
        case 1:
            {
            partial *p1 = dynamic_cast<partial*>(ob.v[i]);
            if (p1 == 0)
                throw runtime_error("Null pointer la type-cast.");
            in>>*ob.v[i];
            }
            break;
        case 2:
            {
                finalExam *fe = dynamic_cast<finalExam*>(ob.v[i]);
                if (fe == 0)
                    throw runtime_error("Null pointer la type-cast.");
                in>>*ob.v[i];
            }
            break;
        case 3:
            {
                quiz *q = dynamic_cast<quiz*>(ob.v[i]);;
                if (q == 0)
                    throw runtime_error("Null pointer la type_cast.");
                in>>*ob.v[i];
            }
            break;
        default:
            cout<<"Nu ati introdus un tip de examen valid."<<endl;
        }
    }

    return in;
}

//constructor de copiere
template <class Ttype>
individualCatalog<Ttype>::individualCatalog(const individualCatalog<Ttype>& ob)
{
    strcpy(pr, ob.pr);
    mAvg = ob.mAvg;
    setRegistrationNumber();

    registrationNumber++;
    numberExams = ob.numberExams;
    for (int i = 0; i < numberExams; i++)
        delete[] v[i];
    if (*ob.v != NULL)
        for (int i = 0; i < numberExams; i++)
        {
            if (typeid(ob.v[i]) == typeid(partial))
            {
                v[i] = new partial;
                v[i] = ob.v[i];
            }
            if (typeid(ob.v[i]) == typeid(finalExam))
            {
                v[i] = new finalExam;
                v[i] = ob.v[i];
            }
            if (typeid(ob.v[i]) == typeid(quiz))
            {
                v[i] = new quiz;
                v[i] = ob.v[i];
            }
            if (typeid(ob.v[i]) == typeid(exam))
            {
                v[i] = new exam;
                v[i] = ob.v[i];
            }

        }

    cout<<"Constructor de copiere individualCatalog."<<endl;
}

template <class Ttype>
void individualCatalog<Ttype>::operator=(const individualCatalog<Ttype>& ob)
{
    strcpy(pr, ob.pr);
    mAvg = ob.mAvg;
    setRegistrationNumber();

    registrationNumber++;
    numberExams = ob.numberExams;
    for (int i = 0; i < numberExams; i++)
        delete[] v[i];
     if (*ob.v != NULL)
        for (int i = 0; i < numberExams; i++)
        {
            if (typeid(ob.v[i]) == typeid(partial))
            {
                v[i] = new partial;
                v[i] = ob.v[i];
            }
            if (typeid(ob.v[i]) == typeid(finalExam))
            {
                v[i] = new finalExam;
                v[i] = ob.v[i];
            }
            if (typeid(ob.v[i]) == typeid(quiz))
            {
                v[i] = new quiz;
                v[i] = ob.v[i];
            }
            if (typeid(ob.v[i]) == typeid(exam))
            {
                v[i] = new exam;
                v[i] = ob.v[i];
            }

        }
}

template<class Ttype>
void individualCatalog<Ttype>::operator+=(const individualCatalog<Ttype>& ob)
{
    cout<<"Inserez fisa de observatie(Specific daca examenul a fost sau nu promovat.): ";
    if (*ob.v != NULL)
        for (int i = 0; i < numberExams; i++)
        {
            if (ob.v[i].getMark() < 5)
                strcpy(pr, "Picat");
            else
            {
                 if (typeid(ob.v[i]) != typeid(exam))
                   {
                       if (ob.v[i].getOralMark() >= 5)
                            strcpy(pr, "Promovat");
                        else strcpy(pr, "Picat");
                   }
                 else strcpy(pr, "Promovat");
            }
        }
}

template <class Ttype>  //specializare care sa returneze unsigned??
unsigned individualCatalog<Ttype>::calc_Avg_examFin(individualCatalog<Ttype>& ob)
{
    int nr = 0;
    double s = 0;
    for (int i = 0; i < ob.numberExams; i++)
    {
        if (ob.v[i].oralMark >= 5)
            if (typeid(ob.v[i]) == typeid(finalExam) || typeid(ob.v[i]) == typeid(quiz))
                {
                    s+= (ob.v[i].getMark() + ob.v[i].getOralMark())/2 + ob.v[i].getExtraPoints();
                    nr++;
                }
    }
    unsigned d = static_cast<unsigned>(s/nr);

    return d;
}

template<class Ttype>
void individualCatalog<Ttype>::calc_Avg(individualCatalog<Ttype>& ob)
{
    double s = 0;
    int nr = 0;
    for (int i = 0; i < ob.numberExams; i++)
    {
        if (ob.v[i].oralMark >= 5)
        {
            s= 0;
            nr++;
            s+= ob.v[i].getMark();
            if (typeid(ob.v[i]) == typeid(partial))
            {
                s+= ob.v[i].getOralMark();
                s/=2;
            }
            if (typeid(ob.v[i]) == typeid(finalExam))
            {
                s+= ob.v[i].getOralMark();
                s/=2;
                s+= ob.v[i].getExtraPoints();
            }
            if (typeid(ob.v[i]) == typeid(quiz))
            {
                s+= ob.v[i].getOralMark();
                s/=2;
                s+= ob.v[i].getExtraPoints();
                s+=ob.v[i].getQmark();
            }
            ob.mAvg = ob.mAvg + s;
        }
        ob.mAvg = ob.mAvg + s;
    }
    if (nr < ob.numberExams)
        ob.mAvg = 0;
    else
        ob.mAvg = ob.mAvg / ob.numberExams;

}




#endif // MYCLASS_H_INCLUDED
