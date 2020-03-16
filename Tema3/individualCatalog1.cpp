/*template<class Ttype>
int individualCatalog<Ttype>::registrationNumber = 0;

template <class Ttype>
individualCatalog<Ttype>::~individualCatalog<Ttype>()
{
    Ttype mAvg = 0;
    for (int i = 0; i < numberExams; i++)
        delete[] v[i];
    delete[] v;
    registrationNumber--;  //decrementez variabila statica la fiecare apel al destructorului
    numberExams = 0;

    cout<<"Destructor individualCatalog."<<endl;
}

//constructor de copiere
template <class Ttype>
individualCatalog<Ttype>::individualCatalog(const individualCatalog<Ttype>& ob)
{
    mAvg = ob->mAvg;
    //setRegistrationNumber(ob->registrationNumber);

    registrationNumber++;
    numberExams = ob->numberExams;
    for (int i = 0; i < numberExams; i++)
        delete[] v[i];
    delete[]v;
    if (ob->v != NULL)
        for (int i = 0; i < numberExams; i++)
        {
            switch (typeid(ob->v[i]))
            {
            case typeid(partial):
                v[i] = new partial();
                v[i](ob->v[i]);
                break;
            case typeid(finalExam):
                v[i] = new finalExam();
                v[i](ob->v[i]);
                break;
            case typeid(quiz):
                v[i] = new quiz();
                v[i](ob->v[i]);
                break;
            default:
                v[i] = new exam();
                v[i](ob->v[i]);
            }

        }

    cout<<"Constructor de copiere individualCatalog."<<endl;
}



template <class Ttype>
void individualCatalog<Ttype>::operator=(const individualCatalog<Ttype>& ob)
{
    mAvg = ob->mAvg;
    registrationNumber = ob->registrationNumber;
    numberExams = ob->numberExams;
    if (v != NULL)
        for (int i = 0; i < numberExams; i++)
            v[i](ob->v[i]);
} */
/*
template<class Ttype>
void individualCatalog::operator+=() (Ttype ob)
{

}


//arunc o exceptie pentru chestionarul de marire al notei
//intreb utilizatorul cate note examene sa aiba catalogul

template <class Ttype>  //specializare care sa returneze unsigned??
unsigned avg(individualCatalog<Ttype> ob)
{
    if (ob->v[i].oralMark >= 5)
    {
        cout<<"Doriti sa va mariti nota?(DA/NU): ";
        char r[2];
        cin>>r;
        try{throw r;}
        catch(char* x)
        {
            if (!strcmp(r, "DA"))

        }
    }
}



*/
