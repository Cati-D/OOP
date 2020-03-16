#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <typeinfo>
#include <errno.h>
#include <stdexcept>
#include "myClass.h"

using namespace std;

ostream& operator<<(ostream& out, exam& ob)
{
    ob.display(out);
    return out;
}

int main()
{
    //citirea, memorarea si afisarea a n obiecte de tip exam
    int nE;
    cout<<"Introduceti numarul de obiecte de tip exam pe care doriti sa il cititi: ";
    cin>>nE;
    int newnE = nE;
    exam ve[nE];
    for (int i = 0; i < nE; i++)
    {
        cout<<"******Introduceti datele pentru obiectul de tip exam:"<<endl;
        try
        {
            exam a;
            cin>>a;
            ve[i] = a;
        }
        catch (runtime_error e)
        {
            newnE--;
            cout<<"A aparut urmatoarea exceptie: "<<e.what()<<endl;
        }
        catch (...)
        {
            cout<<"Tratare eroare necunoascuta"<<endl;
        }
    }
    for (int i = 0; i < newnE; i++)
        cout<<ve[i];//se afiseaza in ordinea introducerii, doar ca numerele examenlor sunt inversate

    //citirea memorarea si afisarea a n obiecte de tip partial
   int nP;
   cout<<"Introduceti numarul de obiecte de tip partial pe care doriti sa il cititi: ";
   cin>>nP;
   int newnP = nP;
   partial vp[nP];
   for (int i = 0; i < nP; i++)
    {
        cout<<"******Introduceti datele pentru obiectul de tip partial:"<<endl;
        try
        {
            partial a;
            cin>>a;
            vp[i] = a;
        }
        catch (runtime_error e)
        {
            newnP--;
            cout<<"A aparut urmatoarea exceptie: "<<e.what()<<endl;
        }
        catch (...)
        {
            cout<<"Tratare eroare necunoascuta"<<endl;
        }
    }
    for (int i = 0; i < newnP; i++)
        cout<<vp[i];//se afiseaza in ordinea introducerii, doar ca numerele examenlor sunt inversate

    //citirea, memorarea si afisarea a n obiecte de tip finalExam
    int nFE;
    cout<<"Introduceti numarul de obiecte de tip finalExam pe care doriti sa il cititi: ";
    cin>>nFE;
    int newnFE = nFE;
    finalExam vfe[nFE];
    for (int i = 0; i < nFE; i++)
    {
        cout<<"******Introduceti datele pentru obiectul de tip partial:"<<endl;
        try
        {
            finalExam a;
            cin>>a;
            vfe[i] = a;
        }
        catch (runtime_error e)
        {
            newnFE--;
            cout<<"A aparut urmatoarea exceptie: "<<e.what()<<endl;
        }
        catch (...)
        {
            cout<<"Tratare eroare necunoascuta"<<endl;
        }
    }
    for (int i = 0; i < newnFE; i++)
        cout<<vfe[i];

     //citirea, memorarea si afisarea a n obiecte de tip quiz
    int nQ;
    cout<<"Introduceti numarul de obiecte de tip quiz pe care doriti sa il cititi: ";
    cin>>nQ;
    int newnQ = nQ;
    quiz vq[nQ];
    for (int i = 0; i < nQ; i++)
    {
        cout<<"******Introduceti datele pentru obiectul de tip partial:"<<endl;
        try
        {
            quiz a;
            cin>>a;
            vq[i] = a;
        }
        catch (runtime_error e)
        {
            newnQ--;
            cout<<"A aparut urmatoarea exceptie: "<<e.what()<<endl;
        }
        catch (...)
        {
            cout<<"Tratare eroare necunoascuta"<<endl;
        }
    }
    for (int i = 0; i < newnQ; i++)
        cout<<vq[i];



    individualCatalog<int> a, b(a), c;
    //cin>>a; //am probleme la schimbarea elementelor din clasa de baza exam in derivate(dynamic_cast)

    return 0;
}
