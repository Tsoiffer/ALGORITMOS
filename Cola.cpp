#include <iostream>
#include <stdio.h>


using namespace std;

struct NodoCola
{
    int info;
    NodoCola*sig;
};

void encolar(NodoCola*&pri,NodoCola*&ult,int nro)//Inicializarlos en el programa en NULL
{
    NodoCola*p;
    p=new NodoCola;
    p->info=nro;
    p->sig=NULL;
    if(pri==NULL && ult==NULL)//se podr�a preguntar solo por uno de los dos
        pri=p;
    else
        ult->sig=p;
    ult=p;
}

void desencolar(NodoCola*&pri,NodoCola*&ult,int &nro)
{
   NodoCola*p=pri;
   nro=p->info;//Le asignas lo que tiene la info del primer nodo a  la variable nro.
   pri=p->sig; //Al asignarle a pri el siguiente de p, p se pierde.
   delete p; //Eliminas P.
   if(pri==NULL)
        ult=NULL;
}















