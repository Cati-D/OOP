#include <iostream>
#include <string.h>

using namespace std;

class Vector
{
    int n;
    int *a;
public:
    Vector();
    Vector(char *b);
    Vector(const Vector& ob);
    ~Vector();
    void alocate(int n);
    int getN() const
    {
        return n;
    }
    void setElem(int i, int val)
    {
        a[i] = val;
    }
    int getElem(int i) const
    {
        return a[i];
    }
    void setN(int x){n = x;}
    friend istream& operator>>(istream& in, Vector& ob);
    friend ostream& operator<<(ostream& out, Vector& ob);
    void operator=(const Vector& ob);
};

Vector::Vector()
{
    a = NULL;
    n = 0;
    cout<<"Constructor fara parametru Vector."<<endl;
}

Vector::Vector(char *b)
{
    n = strlen(b);
    a = new int[n];
    for(int i = 0; i < n; i++)
        a[i] = b[i]-'0';
    cout<<"Construsctor parametri Vector."<<endl;
}

Vector::Vector(const Vector& ob)
{
    this->n = ob.n;
    delete[] this->a;
    this->a = new int[ob.n];

    for (int i = 0; i < ob.n; i++)
        this->a[i] = ob.a[i];

    cout<<"Constructorul de copiere Vector."<<endl;
}
Vector::~Vector()
{
    delete[] this->a;
    cout<<"Destructor Vector."<<endl;
}

istream& operator>>(istream& in, Vector& ob)
{
    cout<<"Dati numarul pe care doriti sa il cititi: ";
    char s[12345];
    in>>s;
    ob.n = strlen(s);
    ob.a = new int[ob.n];
    for (int i = 0; i < strlen(s); i++)
    {
        int x;
        x = s[i]-'0';
        ob.a[i] = x;
    }
    return in;
}

ostream& operator<<(ostream& out, Vector& ob)
{
    for (int i = 0; i < ob.n; i++)
        out<<ob.a[i];
    cout<<endl;
    return out;
}
void Vector::operator=(const Vector& ob)
{
    delete[] a;
    a = new int[ob.n];
    for (int i = 0; i < ob.n; i++)
        this->a[i] = ob.a[i];
}

void Vector:: alocate(int n)
{
    if(n == 0)
        a = NULL;
    else
        a = new int[n];
}

class Nr_Natural_Mare
{
    int nr_cif;
    Vector V;
public:
    Nr_Natural_Mare();
    Nr_Natural_Mare(int nr);
    Nr_Natural_Mare(const Nr_Natural_Mare& ob);
    Nr_Natural_Mare(char *s);
    ~Nr_Natural_Mare();
    int get_nr() const{return nr_cif;}
    void set_nr(int w){nr_cif = w;}
    int get_elem(int i)const {return V.getElem(i);}
    void set_elem(int i, int val){V.setElem(i, val);};
    virtual void read(istream& in)
    {
        char s[122234];
        in>>s;
        V.alocate(strlen(s));
        nr_cif = strlen(s);
        for(int i = 0; i < nr_cif; i++)
        {
            int x;
            x = s[i]-'0';
            V.setElem(i, x);
        }
    }
    virtual void display(ostream& out)
    {
        for(int i = 0; i < nr_cif; i++)
            out<<V.getElem(i);
    }
    virtual void sumFib(){};
    void operator=(const Nr_Natural_Mare& ob);
    virtual void shiftR(){};
};

Nr_Natural_Mare::Nr_Natural_Mare(char *sir)
{
    nr_cif = strlen(sir);
    for (int i = 0; i < nr_cif; i++)
        V.setElem(i, sir[i]-'0');
}

Nr_Natural_Mare::Nr_Natural_Mare()
{
    nr_cif = 0;
    cout<<"Constructor Nr_Natural_Mare."<<endl;
}

Nr_Natural_Mare:: Nr_Natural_Mare(int nr)
{
    nr_cif = nr;
    V.alocate(nr);
    cout<<"Constructor de intializare cu parametrru Nr_Natual_Mare."<<endl;
}

Nr_Natural_Mare:: Nr_Natural_Mare(const Nr_Natural_Mare& ob)
{
    this->nr_cif = ob.nr_cif;
    for (int i = 0; i < ob.nr_cif; i++)
        this->V.setElem(i,ob.V.getElem(i));

    cout<<"Constructor de copiere Nr_Natural_Mare."<<endl;
}
Nr_Natural_Mare::~Nr_Natural_Mare()
{
    cout<<"Destructor Nr_Natural_Mare.";
}

istream& operator>>(istream& in, Nr_Natural_Mare& ob)
{
    ob.read(in);
    return in;
}

ostream& operator<<(ostream& out, Nr_Natural_Mare& ob)
{
    ob.display(out);
    return out;
}

void Nr_Natural_Mare:: operator=(const Nr_Natural_Mare& ob)
{
    this->nr_cif = ob.nr_cif;
    this->V = ob.V;
}

class Numar_Fibonacci_mare:public Nr_Natural_Mare
{
public:
    Numar_Fibonacci_mare(){cout<<"Constructor Numar_Fibonacci."<<endl;}
    Numar_Fibonacci_mare(int nr_cif1){cout<<"Constructor cu paramteru Numar_Fibonacci_Mare."<<endl;}
    Numar_Fibonacci_mare (const Numar_Fibonacci_mare &ob){cout<<"Constructor de copiere Numar_Fibonacci_Mare."<<endl;}
    ~Numar_Fibonacci_mare(){cout<<"Deconstructor Numar_Fibonacci_Mare."<<endl;}
    void read(istream &in)
    {
        cout<<"Introduceti numarul pe care doriti sa il cititi: ";
        this->Nr_Natural_Mare::read(in);
    }

    void display(ostream& out)
    {
        this->Nr_Natural_Mare::display(out);
    }
    void operator=(const Numar_Fibonacci_mare& ob);
    void sumFib();
    void shiftR();
    bool isEqual(Nr_Natural_Mare ob);
};

void Numar_Fibonacci_mare::operator=(const Numar_Fibonacci_mare& ob)
{
    /*set_nr(ob.get_nr());
    for (int i = 0; i < ob.get_nr(); i++)
        set_elem(i,ob.get_elem(i));*/
    Nr_Natural_Mare::operator=(ob);
}

void Numar_Fibonacci_mare::shiftR()
{
    for(int i = get_nr() - 1; i>1; i--)
        set_elem(i+1, get_elem(i));
}

bool Numar_Fibonacci_mare::isEqual(Nr_Natural_Mare ob)
{
    /*if(get_nr() != ob.get_nr())
        return 0;
    cout<<"nu";*/

    for(int i = 0; i < ob.get_nr(); i++)
        if(get_elem(i) != ob.get_elem(i))
            return 0;
    return 1;
}

void Numar_Fibonacci_mare::sumFib()
{
    Nr_Natural_Mare x(1), y(1), z(1);
    /*x.set_nr(1);
    y.set_nr(1);
    z.set_nr(1);*/
    x.set_elem(0, 1);
    y.set_elem(0, 1);
    //z.set_elem(0 ,1);
    cout<<x.get_elem(0)<<' '<<y.get_elem(0)<<' ';
    while(!isEqual(z))
    {
        int r = 0, s = 0;
        for(int i = z.get_nr() - 1; i >1; i--)
        {
            s = x.get_elem(i) + y.get_elem(i);
            r = s/10;
            z.set_elem(i, s%10);
            int bck = z.get_elem(i-1);
            z.set_elem(i-1, bck + r);
        }
        if(r)
        {
            z.shiftR();
            z.set_elem(1, r);
            int d = z.get_nr();
            z.set_nr(++d);
        }
        z.display(cout);
        x = y;
        y = z;
    }
}

int main()
{
    char d[]="123455678";
    Vector ob(d);
    Vector ob1(ob);
    Vector ob2;
    cin>>ob2;
    cout<<ob;
    cout<<ob1;

    int n;
    cout<<"Introduceti numarul de obiecte de tip Vector pe care doriti sa il citi: ";
    cin>>n;
    Vector obnew[n];

    for (int j = 0; j < n; j++)
        cin>>obnew[j];
    for (int j = 0; j < n; j++)
        cout<<obnew[j];

    int NNM;
    cout<<"Introduceti cate numere de tip Nr_Natural_Mare doriti sa cititi: ";
    cin>>NNM;

    cout<<"Introduceti numerele: ";
    Nr_Natural_Mare vpNM[NNM];
    for (int i = 0; i < NNM; i++)
           cin>>vpNM[i];
    cout<<"Numerele sunt: ";
    for( int i = 0; i < NNM; i++)
        cout<<vpNM[i]<<endl;

    int NFM;
    cout<<"Introduceti cate numere de tip Numar_Fibonacci_mare doriti sa cititi: ";
    cin>>NFM;
    Numar_Fibonacci_mare vpNFM[NFM];
    for (int i = 0; i < NFM; i++)
        cin>>vpNFM[i];
    cout<<"Numerele sunt: ";
    for (int i = 0; i < NFM; i++)
        cout<<vpNFM[i]<<endl;

    Numar_Fibonacci_mare obn;
    cin>>obn;
    //obn.sumFib();

    return 0;

}
