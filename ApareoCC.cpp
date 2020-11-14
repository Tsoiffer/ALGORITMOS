#include <iostream>
#include <stdio.h>


//Apareo:Dadas la lista del primer parcial y la del segundo parcial mostrar situación
//CC: Dada una lista con alumnos repetidos mostrar alumno y promedio
/*
lista simple de alumnos, cada nodo tiene legajo nombre y nota.
La nota de todos es cero
otra lista con los alumnos que rindieron
completar la nota de la primera lista
*/

using namespace std;

struct Alumno
{
    unsigned leg;
    string nom;
    unsigned nota;
};

struct Nodo
{
    Alumno info;
    Nodo*sig;
};

string condicion(unsigned n1,unsigned n2)
{
    if(n1>7&&n2>7)
        return " Prom";
    else
    {
        if(n1>5&&n2>5)
            return " Final";
        else
            return " Recursa";
    }
}

void apareo(Nodo*lista1, Nodo*lista2)
{
    Nodo *r1,*r2;
    r1=lista1;
    r2=lista2;
    while(r1!=NULL && r2!=NULL)
    {
        if(r1->info.leg<r2->info.leg)
        {
            cout<<r1->info.leg<<condicion(r1->info.nota,0)<<endl;
            r1=r1->sig;
        }
        else
        {
            if(r1->info.leg==r2->info.leg)
            {
                cout<<r1->info.leg<<condicion(r1->info.nota,r2->info.nota)<<endl;
                r1=r1->sig;
                r2=r2->sig;
            }
            else
            {
                cout<<r2->info.leg<<condicion(0,r2->info.leg)<<endl;
                r2=r2->sig;
            }
        }
    }
    while(r1!=NULL)
    {
        cout<<r1->info.leg<<condicion(r1->info.nota,0)<<endl;
        r1=r1->sig;
    }
    while(r2!=NULL)
    {
        cout<<r2->info.leg<<condicion(0,r2->info.leg)<<endl;
        r2=r2->sig;
    }
}
void cc(Nodo*lista)
{
    Nodo*r=lista;
    while(r!=NULL)
    {
        unsigned legA=r->info.leg;

        unsigned s=0,c=0;
        do
        {
           s+=p->info.nota;
           c++;
           p=p->sig;
        }while(r!=NULL && r->info.leg==legA);
        cout<<legA<<s/c<<endl;

    }
}
void cc(Nodo*lista) //versión con 2 punteros
{
    Nodo*p=lista;
    Nodo*r=lista;
    while(r!=NULL)
    {
        unsigned s=0,c=0;
        do
        {
           s+=p->info.nota;
           c++;
           p=p->sig;
        }while(p!=NULL && p->info.leg==r->info.leg);
        cout<<r->info.leg<<s/c;
        r=p;
    }
}
