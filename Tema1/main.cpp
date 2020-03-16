#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
ifstream f("arbore.in");
class arbore;
class nod
{
    //fiecare variabila este caracterizata de cate un nod fiu, unde fiu este fiul cel mai din stanga si de un nod frate, unde frate este urmatorul frate de la stanga la dreapta
    int son, bro;
public:
    friend class arbore;
    friend istream& operator>>(istream &in, nod &ob);
    friend ostream& operator<<(ostream &out, nod &ob);
    friend istream& operator>>(istream &in, arbore &ob);
};

class arbore
{
    nod *arr_node; //vector in  care fiecare element este caracterizat de un camp fiu si de un camp frate
    int root; //radacina arborelui
    int nr_elem;
    vector <int> graph[10003];
    int *coada;
public:
    arbore ();
    ~arbore();
    int elem();
    int rad();
    arbore operator=(arbore ob);
    arbore operator+(arbore ob);
    friend istream& operator>>(istream &in, nod &ob);
    friend ostream& operator<<(ostream &out, nod &ob);
    vector <int> transf();
    void DFS(int nod, int* viz);
    void BFS(int s, int* viz);
    void leaves();
    int high();
    void display();
    friend istream& operator>>(istream &in, arbore &ob);
    //arbore (const arbore& ob);
};

istream& operator>>(istream &in, nod &ob)
{
    in>>ob.son;
    in>>ob.bro;
    return in;
}

ostream& operator<<(ostream &out, nod &ob)
{
    out<<ob.son;
    out<<' ';
    out<<ob.bro;
    return out;
}

istream& operator>>(istream &in, arbore &ob)
{
    in>>ob.nr_elem;
    in>>ob.root;

    for(int i = 1; i <= ob.elem(); i++)
        in>>ob.arr_node[i];

    return in;
}

arbore:: arbore ()
{
     this->arr_node = new nod[this->nr_elem];
     this->coada = new int[this->nr_elem];
}

arbore:: ~arbore()
{
    delete[] this->arr_node;
    delete[] this->coada;
    cout<<"Eliberez memoria"<<endl;
}

vector <int> arbore:: transf()
{
    //transform arborele primit prin vectorii primiti intr-un vector de liste de adiacenta
    for(int i = 1; i <= this->nr_elem; i++)
        if(this->arr_node[i].son != -1)
        {
            this->graph[i].push_back(this->arr_node[i].son);
            this->graph[this->arr_node[i].son].push_back(i);
        }

    for(int i=1; i<= this->nr_elem; i++)
    {
        int w = this->arr_node[i].son;
        while(w != -1)
        {
            this->graph[i].push_back(w);
            this->graph[w].push_back(i);
            w = this->arr_node[w].bro;

        }
    }

    return *this->graph;
}

/*arbore:: arbore(const arbore& ob)
{
    delete[] this;
    this->nr_elem = ob.nr_elem;

    this->root = ob.root;

    for(int i = 1; i <= ob.nr_elem; i++)
    {
        this->coada[i] = ob.coada[i];
        this->arr_node[i].son = ob.arr_node[i].son;
        this->arr_node[i].bro = ob.arr_node[i].bro;
    }
} */

arbore arbore:: operator=(arbore ob)
{
    this->nr_elem = ob.nr_elem;
    this->root = ob.root;

    for(int i = 1; i <= ob.nr_elem; i++)
    {
        this->coada[i] = ob.coada[i];
        this->arr_node[i].son = ob.arr_node[i].son;
        this->arr_node[i].bro = ob.arr_node[i].bro;
    }

    return *this;
}

arbore arbore:: operator+(arbore ob)
{
    int ultim = this->graph[this->root][this->graph[this->root].size() - 1];  //retin fiul cel mai din dreapta al radacinii
    this->arr_node[ultim].bro = ob.root; //marchez faptul ca fiul extrem stang al radacinii are un nou frate

    int nrElemThis = this->nr_elem;
    for(int i = 1; i <= ob.nr_elem; i++)
    {
        this->arr_node[nrElemThis + i].son = ob.arr_node[i].son;   //adau in continuarea arborelui curent al doiela arbore
        this->arr_node[nrElemThis + i].bro = ob.arr_node[i].bro;
    }
    //this->nr_elem = this->nr_elem + ob.nr_elem;  //maresc numerul de elemente din arborele curent
    return *this;
}

void arbore:: DFS(int nod, int* viz)
{
    viz[nod]= 1;
    int lim= this->graph[nod].size();
    for(int i= 0; i< lim; i++)
    {
        int vecin = this->graph[nod][i];
        if(!viz[vecin])
        {
            cout<<vecin<<' ';
            DFS(vecin, viz);
        }
    }
}

int arbore:: elem()
{
    return this->nr_elem;  //returnez nr de elemente pentru a putea avea acces dupa la el in main
}

int arbore:: rad()
{
    return this->root;   //returnez radacina pentru a o putea accesa in main
}

void arbore:: BFS(int s, int *viz)
{
    viz[s] = 1;
    cout<<this->root<<' ';
    coada[1] = s;
    int left, right;
    left = right = 1;
    while (left <= right)
    {
        int index = this->coada[left];
        int lim = this->graph[index].size();
        for (int i = 0; i < lim; i++)
        {
            int vecin = this->graph[index][i];
            if (!viz[vecin])
            {
                cout<<vecin<<' ';
                viz[vecin] = 1;
                this->coada[++right] = vecin;
            }
        }
        left++;
    }
}

void arbore:: leaves()
{
    for(int i = 1; i<= this->nr_elem; i++)
        if(this->arr_node[i].son == -1)   //orice nod care nu are fii este frunza, asa ca o afisez
            cout<<i<<' ';
}

int arbore:: high()
{
    int dad[this->nr_elem]; //construiesc un vector de tati
    dad[root] = 0;    //initializez pozitia radacinii cu 0 pentru ca nu are tata
    int vizita[this->nr_elem];
    for(int i = 0; i <= this->nr_elem; i++)
        vizita[i] = 0;
    vizita[this->root] = 1; //marchez radacina ca fiind vizitata
    for(int i = 1; i <= this->nr_elem; i++)
    {
        int lim = this->graph[i].size();
        for(int j = 0; j < lim; j++)
        {
            int x = this->graph[i][j];
            if(!vizita[x])   //daca nodul x este vizitat in lista de adiacenta inseamna ca este tatal nodului curent
            {
                dad[x] = i;
                vizita[x] = 1;
            }
        }
    }

    int dist[this->nr_elem];
    for(int i = 1; i <= this->nr_elem; i++)
        dist[i] = 0;
    for(int i = 2; i <= this->nr_elem; i++)
        dist[i] =  dist[dad[i]] + 1;   //fiecare nod are inaltimea tatalui sau +1

    int maxim = 0;
    for(int i = 1; i <= this->nr_elem; i++)
        if(dist[i] > maxim)
            maxim = dist[i];

    return maxim;

}

void arbore:: display()
{
    for(int i = 1; i <= this->nr_elem; i++)
    {
        cout<<this->arr_node[i];
        cout<<endl;
    }
}

int main()
{
    arbore tree;
    int* viz;
    viz = new int[tree.elem()];
    f>>tree;

    tree.transf();

    cout<<"1.Parcurgerea DFS: ";
    int n = tree.elem();
    cout<<tree.rad()<<' ';
    for(int i = 1; i <= n; i++)
        viz[i] = 0;
    for(int i = 1; i <= n; i++)
        if(!viz[i])
            tree.DFS(i, viz);
    cout<<endl;

    cout<<"2.Parcurgerea BFS: ";
    for(int i = 1; i <= n; i++)
        viz[i] = 0;
    tree.BFS(1, viz);
    cout<<endl;

    cout<<"3.Inaltimea arborelui: ";
    int hg;
    hg = tree.high();
    cout<<hg<<endl;

    cout<<"4.Lista de frunze: ";
    tree.leaves();
    cout<<endl;

    cout<<"5.Adunarea a doi arbori: "<<endl;
    arbore tree2;
    tree = tree + tree2;
    tree.display();

    delete[] viz;

    return 0;
}
