#include <iostream>
#include <stdio.h>


using namespace std;

struct Nodo
{
    int dato;
    Nodo*sig;
};


int cantNodos(Nodo*listaC);
void agregar(Nodo*&listaC, int nro);
void insertar(Nodo*&listaC, int nro);


int main()
{
    Nodo*lis=NULL;
    int num;
    cin>>num;
    while(num!=0)
    {
        //agregar(lis,num);
        insertar(lis,num);
        cin>>num;
    }
    cout<<endl<<cantNodos(lis)<<endl;
    return 0;
}

int cantNodos(Nodo*listaC)
{
    if(listaC==NULL)
        return 0;
    else
    {
        int cont=0;
        Nodo*p=listaC->sig;
        do
        {
            cout<<p->dato;
            cont++;
            p=p->sig;
        }while(p!=listaC->sig);
        return cont;
    }


}

void agregar(Nodo*&listaC, int nro)
{
    //agrega un nodo a la lista circular sin orden
    Nodo*n=new Nodo;
    n->dato=nro;
    if(listaC!=NULL)
    {
        n->sig=listaC->sig;
        listaC->sig=n;
    }
    else
    {
        n->sig=n;
        listaC=n;
    }
}

void insertar(Nodo*&listaC, int nro)
{
    //agrega un nodo a la lista circular ordenada
    Nodo*n=new Nodo;
    n->dato=nro;
    if(listaC==NULL)
    {
        n->sig=n;
        listaC=n;
    }
    else
    {
        Nodo*p=listaC->sig,*ant=listaC;
        if(p->dato<nro)
        {
            do
            {
                ant=p;
                p=p->sig;
            }while(p!=listaC->sig && p->dato<nro);

        }
        n->sig=p;
        ant->sig=n;
        if(n->dato>listaC->dato)
            listaC=n;
    }
}


