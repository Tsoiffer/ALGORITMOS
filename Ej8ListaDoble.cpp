#include <iostream>
#include <stdio.h>

struct Nodo
{
    int dato;
    Nodo*sig;
    Nodo*ant;
};

using namespace std;

int main()
{
    return 0;
}

void ej8(Nodo*&l1,Nodo*&l2,int n)
{
    int cont=0;
    Nodo*p;
    while(l2!=NULL && cont<n)
    {
        p=l2;
        l2=l2->ant;
        delete p;
        cont++;
    }
    if(l2!=NULL)
        l2->sig=NULL;
    else
        l1=NULL;
}

void insertar(Nodo*&lis1,Nodo*&lis2, int nro)
{
    Nodo*p,*r;
    p=new Nodo;
    p->dato=nro;
    if(lis1==NULL && lis2==NULL) //p no va a tener ni sucesor ni antecesor (agrega a lista vac�a)
    {
        p->sig=p->ant=NULL;
        lis1=lis2=p;
    }
    else
    {
        r=lis1;
        while(r!=NULL&&r->dato<nro)
            r=r->sig;
        p->sig=r;
        if(r==lis1) //p va a tener sucesor y no antecesor
        {
            p->ant=NULL;
            //p->sig=r;
            r->ant=p;
            lis1=p;
        }
        else
        {
            if(r==NULL) //p va a tener antecesor y no sucesor
            {
                p->ant=lis2;
                //p->sig=r;
                lis2->sig=p;
                lis2=p;
            }
            else
            {   //p va a tener sucesor y antecesor
                p->ant=r->ant;
                //p->sig=r;
                r->ant->sig=p;
                r->ant=p;
            }
        }

}
















