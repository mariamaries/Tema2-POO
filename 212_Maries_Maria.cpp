#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

class Nod{
protected:
    int info;
    Nod* next;
public:
    friend class Nod_dublu;
    friend class Lista;
    Nod(int info = 0, Nod *next = NULL)
    {
        this->info = info;
        this->next = next;
    }
    Nod(const Nod& n)
    {
        this->info = n.info;
        this->next = n.next;
    }
    virtual ~Nod()
    {
        delete next;
    }

    virtual void citire (istream &in)
    {
        cout<<"Valoarea din nod: ";
        in>>info;
    }
    virtual void afisare (ostream &out)
    {
        out<<"Info: "<<this->info<<endl;
    }

    friend istream& operator>> (istream& in, Nod& n)
    {
        n.citire(in);
        return in;
    }
    friend ostream& operator<< (ostream& out, Nod& n)
    {
        n.afisare(out);
        return out;
    }

    Nod& operator= (const Nod& n)
    {
        this->info = n.info;
        this->next = n.next;
        return *this;
    }
};

class Nod_dublu : public Nod{
protected:
    Nod* ante;
public:
    friend class Lista;
    friend class Lista_Circulara;
    Nod_dublu(int info = 0, Nod *next = NULL, Nod *ante = NULL):Nod(info,next)
    {
        this->ante = ante;
    }
    Nod_dublu(const Nod_dublu& nd):Nod(nd)
    {
        this->ante = nd.ante;
    }
    ~Nod_dublu()
    {
        delete next;
        delete ante;
    }
    Nod_dublu* get_next()
    {
        return (Nod_dublu*)this->next;
    }
    Nod_dublu* get_info()
    {
        return (Nod_dublu*)this->info;
    }
    void citire(istream &in)
    {
        cout<<"Introduceti un nod dublu: "<<endl;
        Nod::citire(in);
    }
    void afisare(ostream &out)
    {
        cout<<"Nodul este: "<<endl;
        Nod::afisare(out);
    }
    friend istream& operator>>(istream& in, Nod_dublu& nd)
    {
        nd.citire(in);
        return in;
    }
    friend ostream& operator<<(ostream &out, Nod_dublu &nd)
    {
        nd.afisare(out);
        return out;
    }
    Nod_dublu* operator= (const Nod_dublu& nd)
    {
        Nod::operator=(nd);
        this->ante = nd.ante;
        return this;
    }
    friend istream& operator>>(istream& in, class Lista &l);
    friend ostream& operator<<(ostream& out, class Lista &l);
    friend istream& operator>>(istream& in, class Lista_Circulara &l);
    friend ostream& operator<<(ostream& out, class Lista_Circulara &l);
};

class Lista{
protected:
    Nod_dublu* root;
    Nod_dublu* tail;
public:
    friend class Nod_dublu;
    Lista(Nod_dublu* root = NULL, Nod_dublu* tail = NULL)
    {
        this->root = root;
        this->tail = tail;
    }
    Lista(const Lista &l)
    {
        if(l.root == NULL)
            this->root = NULL;
        else
        {
            root = new Nod_dublu(l.root->info,l.root->next,l.root->ante);
            Nod_dublu *current = root;
            Nod_dublu *t = l.root;
            while(t->next != NULL)
            {

                current->next = new Nod_dublu(*(Nod_dublu*)t->next);
                t = (Nod_dublu*)t->next;
                current = (Nod_dublu*)current->next;
            }
        }
    }
    ~Lista()
    {
        Nod_dublu *t;
        while(root!=NULL)
        {
            t = (Nod_dublu*)root->next;
            delete root;
            root = t;
        }
    }
    void push(Nod_dublu *nd)
    {
        Nod_dublu *p = new Nod_dublu;
        p = root;

        Nod_dublu *prev = p;
        if(root == NULL)
        {
            root = nd;
        }
        else
        {
            while((Nod_dublu*)p->next != NULL)
            {
                p = (Nod_dublu*)p->next;
            }
            p->next = nd;
            nd->ante = p;
        }
    }
    friend ostream& operator<<(ostream& out, Lista &l)
    {
        cout<<"Lista este: ";
        l.afisare();
    }
    friend istream& operator>>(istream& in, Lista& l)
    {
        for(;;)
        {
            Nod_dublu *t = new Nod_dublu;
            cin>>*t;
            int x = t->info;
            if(x == 0)
                break;
            l.push(t);
        }
        return in;
    }
    Lista& operator= (const Lista& l)
    {
        Nod_dublu:operator=(l);
        root = l.root;
        tail = l.tail;
    }
    virtual void afisare()
    {
        Nod_dublu *nd = new Nod_dublu;
        nd = root;
        while (nd != NULL)
        {
            cout << (Nod_dublu*)nd->info << " ";
            nd = (Nod_dublu*)nd->next;
        }
        cout <<endl;
    }
};

class Lista_Circulara : private Lista{
public:
    friend class Nod_dublu;
    Lista_Circulara(Nod_dublu* root = NULL, Nod_dublu* tail = NULL):Lista(root,tail)
    {}
    Lista_Circulara(const Lista_Circulara &l)
    {
        if(l.root == NULL)
            this->root = NULL;
        else
        {
            root = new Nod_dublu(l.root->info,(Nod_dublu*)l.root->next,(Nod_dublu*)l.root->ante);
            Nod_dublu *current = root;
            Nod_dublu *t = l.root;
            while((Nod_dublu*)t->next != (Nod_dublu*)root->next)
            {

                current->next = new Nod_dublu(*(Nod_dublu*)t->next);
                t = (Nod_dublu*)t->next;
                current = (Nod_dublu*)current->next;
            }
        }
    }
    ~Lista_Circulara()
    {
        Nod_dublu *t;
        while(root!=NULL)
        {
            t = (Nod_dublu*)root->next;
            delete root;
            root = t;
        }
    }
    void push(Nod_dublu *nd)
    {
        Nod_dublu *p = new Nod_dublu;
        p = root;
        if(root == NULL)
        {
            root = nd;
            root->next = root;
        }
        else
        {
            while((Nod_dublu*)p->next != root)
            {
                p = (Nod_dublu*)p->next;
            }
            p->next = nd;
            nd->next = root;
            nd->ante = p;
            root->ante = nd;
        }
    }

    void remove(int value)
    {
        Nod_dublu *p = new Nod_dublu;
        if (root == NULL) {
            return;
        }
        p = root;
        while(int((Nod_dublu*)p->info) != value) {
            p = (Nod_dublu*)p->next;
        }
        Nod_dublu *temp = (Nod_dublu*)p->ante;
        temp->next = (Nod_dublu*)p->next;
        ((Nod_dublu*)p->next)->ante = temp;
    }

    friend ostream& operator<<(ostream& out, Lista_Circulara &l)
    {
        cout<<"Lista circulara este: ";
        l.afisare();
    }
    friend istream& operator>>(istream& in, Lista_Circulara &l)
    {
        for(;;)
        {
            Nod_dublu *t = new Nod_dublu;
            cin>>*t;
            int x = t->info;
            if(x == 0)
                break;
            l.push(t);
        }
        return in;
    }
    Lista_Circulara& operator= (const Lista_Circulara& l)
    {
        Nod_dublu:operator=(l);
        root = l.root;
        tail = l.tail;
    }
    Nod_dublu* get_root()
    {
        return this->root;
    }
    virtual void afisare()
    {
        Nod_dublu *nd = new Nod_dublu;
        cout<<(Nod_dublu*)root->info<<" ";
        nd = (Nod_dublu*)root->next;
        while ((Nod_dublu*)nd != root)
        {
            cout <<(Nod_dublu*)nd->info<<" ";
            nd = (Nod_dublu*)nd->next;
        }
        cout <<endl;
    }
};


int main()
{
    int n,k;
    cout<<"Please insert the number of people around the table: "<<endl;
    cin>>n;
    cout<<"Please insert the counting number: "<<endl;
    cin>>k;

    Lista_Circulara *l = new Lista_Circulara();
    for(int i=1; i<=n;i++)
    {
        Nod_dublu *nd = new Nod_dublu(i);
        (*l).push(nd);
    }
    int count = 1;
    int size = n;

    Nod_dublu *p = (*l).get_root();
    Nod_dublu *temp = NULL;

    while(size!=1)
    {

        if(count == k)
        {
            temp = (*p).get_next();
            (*l).remove(int((*p).get_info()));
            count = 1;
            size -= 1;
            p = temp;
        }
        else
        {
            count++;
            p = (*p).get_next();
        }

    }
    cout<<"The safe spot is in the number: "<<endl;
    cout<<int((*p).get_info());

    return 0;
}

