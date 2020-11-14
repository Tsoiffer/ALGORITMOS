#include <iostream>
#include <stdio.h>


using namespace std;

struct Alumno
{
    unsigned leg;
    char nom[21];
    unsigned nota;
};

struct Nodo
{
    Alumno info;
    Nodo*sig;
};

void listar(Nodo*lista);
void insertar(Nodo*&lista, Alumno alum);

int main()
{
    Nodo *listaK1030;
    listaK1030=NULL;
    Alumno a;
    cin>>a.leg;
    while(a.leg!=0)
    {
        cin>>a.nom;
        cin>>a.nota;
        insertar(listaK1030,a);
        cin>>a.leg;
    }
    listar(listaK1030);
}

void listar(Nodo*lista)
{
    Nodo*r;
    r=lista;
    while(r!=NULL)
    {
        cout<<r->info.leg<<r->info.nom<<r->info.nota<<endl;
        r=r->sig;
    }
}

void insertar(Nodo*&lista, Alumno alum)
{
    Nodo*p,*r,*ant;
    p=new Nodo;
    p->info=alum;
    r=lista;
    while(r!=NULL&&r->info.leg<alum.leg)
    {
        ant=r;
        r=r->sig;
    }
    p->sig=r;
    if(r!=lista)
        ant->sig=p;
    else
        lista=p;
}

Nodo* buscarSec(Nodo*lista,unsigned unLeg)
{
    Nodo*r=lista;
    while(r!=NULL && r->info.leg!=unLeg)
        r=r->sig;
    return r;
}

Nodo* buscarSecMejorada(Nodo*lista,unsigned unLeg)
{
    Nodo*r=lista;
    while(r!=NULL && r->info.leg<unLeg)
        r=r->sig;
    if(r==NULL || r->info.leg!=unLeg)
        return NULL;
    else
        return r;
}

Nodo* buscarInsertar(Nodo*&lista,Alumno al)
{
    Nodo*ant,*r=lista;
    while(r!=NULL && r->info.leg<al.leg)
    {
        ant=r;
        r=r->sig;
    }

    if(r==NULL || r->info.leg!=unLeg) //no est� en la lista
    {
        Nodo*p=new Nodo;
        p->info=al
        p->sig=r;
        if(r!=lista)
            ant->sig=p;
        else
            lista=p;
        return p;
    }
    else
        return r;
}

//bool eliminar(Nodo*&lista,unsigned unLeg)
void eliminar(Nodo*&lista,unsigned unLeg)
{
    Nodo*ant,*r=lista;
    while(r!=NULL && r->info.leg<unLeg)
    {
        ant=r;
        r=r->sig;
    }

    if(r!=NULL && r->info.leg==unLeg)//est�
    {
        if(r==lista)
            lista=r->sig;
        else
            ant->sig=r->sig;
        delete r;
        //return true;
    }
    //else
        //return false;
}

void mostrarAprobados(Nodo*lista)
{
    Nodo*r;
    r=lista;
    while(r!=NULL)
    {
        if(r->info.nota>=6)
            cout<<r->info.leg<<r->info.nom<<r->info.nota<<endl;
        r=r->sig;
    }
}

float promedioCurso(Nodo*lista)
{
    unsigned cont=0,suma=0;
    Nodo*r;
    r=lista;
    while(r!=NULL)
    {
        suma+=r->info.nota;
        cont++;
        r=r->sig;
    }
    if(cont>0)
        return (float)suma/cont;
    else
        return 0;
}










