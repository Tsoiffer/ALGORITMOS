#include <iostream>

using namespace std;

struct Libro
{
    unsigned codigo;
    string titulo;
};

struct Nodo
{
    Libro dato;
    Nodo *sig;
};

void apilar(Nodo*&pila,Libro lib)
{
    Nodo*p;
    p=new Nodo;
    p->dato=lib;
    p->sig=pila;
    pila=p;
}

void desapilar(Nodo*&pila,Libro &lib)
{
    Nodo*p;
    p=pila;
    lib=p->dato; //pila->dato
    pila=p->sig;
    delete p;
}

int main()
{
    Libro libro;
    Nodo*pilaLibros=NULL;
    for(int i=1;i<=3;i++)
    {
        cin>>libro.codigo;
        cin>>libro.titulo;
        apilar(pilaLibros,libro);
    }
    while(pilaLibros!=NULL)
    {
        desapilar(pilaLibros,libro);
        cout<<libro.codigo<<libro.titulo;
    }
    return 0;
}
