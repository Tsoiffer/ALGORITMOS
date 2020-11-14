#include <iostream>
#include <stdio.h>


using namespace std;

struct NodoCola
{
    int info;
    NodoCola*sig;
};

void encolar(NodoCola*&pri,NodoCola*&ult,int nro)
{
    NodoCola*p;
    p=new NodoCola;
    p->info=nro;
    p->sig=NULL;
    if(pri==NULL && ult==NULL)//se podría preguntar solo por uno de los dos
        pri=p;
    else
        ult->sig=p;
    ult=p;
}

void desencolar(NodoCola*&pri,NodoCola*&ult,int &nro)
{
   NodoCola*p=pri;
   nro=p->info;
   pri=p->sig;
   delete p;
   if(pri==NULL)
        ult=NULL;
}















