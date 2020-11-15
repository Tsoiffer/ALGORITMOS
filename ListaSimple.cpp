//Funciones De Listas

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
Nodo* buscarSec(Nodo*lista,unsigned );
Nodo* buscarSecMejorada(Nodo*lista,unsigned );

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
//Muestra los Nodos de una lista.
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
//Inserta Nodo en lista.
void insertar(Nodo*&lista, Alumno alum)
{
    Nodo*p,*r,*ant;
    p=new Nodo;
    p->info=alum;//Asigna la info que traes del programa a la info del "nuevo" nodo.
    r=lista;
    while(r!=NULL&&r->info.leg<alum.leg) //Recorres la lista, la segunda condición sólo sirve si la lista está ordenada (hay que cambiarla dependiendo del problema).
    {
        ant=r;
        r=r->sig;
    }
    p->sig=r; //Salís por que r es NULL o por la condición que sea, entonces P es el último por lo que se le asgina el siguiente r (que es es Null); pero si r no es Null quiere decir que P se encuentra entre r y ant, entonces el p->sig es r
    if(r!=lista)
        ant->sig=p; //si r es distinto de lista, no es el primero o sea que P es el último o está en el medio por ende se le asigna a ant->sig =p.
    else
        lista=p; //r es igual a lista, o sea que la lista estaba vacía o sólo tenía uno.
}

Nodo* buscarSec(Nodo*lista,unsigned unLeg) //Buscar un nodo de forma secuencial, te devuelve la posición.
{
    Nodo*r=lista;
    while(r!=NULL && r->info.leg!=unLeg) //Esta condición sirve aunque no este ordenada la lista. 
        r=r->sig;
    return r;
}

Nodo* buscarSecMejorada(Nodo*lista,unsigned unLeg) //Busca pero necesita que la lista tenga un orden.
{
    Nodo*r=lista;
    while(r!=NULL && r->info.leg<unLeg)
        r=r->sig;
    if(r==NULL || r->info.leg!=unLeg)
        return NULL;
    else
        return r;
}

Nodo* buscarInsertar(Nodo*&lista,Alumno al) //Esta función tiene dos objetivos, te devuelve si ya existe un nodo con x información o te inserta un nuevo nodo donde debe hacerlo.
{
    Nodo*ant,*r=lista;
    while(r!=NULL && r->info.leg<al.leg) //La condición sirve si la lista tiene un orden, pero básicamente recorre la lista.
    {
        ant=r;
        r=r->sig;
    }

    if(r==NULL || r->info.leg!=al.leg) //no esta en la lista, ya sea porque la lista está vacía o si es que la lista no está vacía.
    {
        Nodo*p=new Nodo;
        p->info=al;
        p->sig=r; //Si r es Null quiere decir que P es el último elemento de la lista y si r no es Null quiere decir que P está antes que r y después que ant.
        if(r!=lista) //quiere decir que la lista no está vacía.
            ant->sig=p;
        else
            lista=p;//la lista está vacía o tiene un sólo elemento.
        return p;
    }
    else
        return r;
}

//bool eliminar(Nodo*&lista,unsigned unLeg)
void eliminar(Nodo*&lista,unsigned unLeg) //Elimina un Nodo con cierta información
{
    Nodo*ant,*r=lista;
    while(r!=NULL && r->info.leg<unLeg) //Recorres la lista, la segunda condición sólo sirve si está ordenada la lista.
    {
        ant=r;
        r=r->sig;
    }

    if(r!=NULL && r->info.leg==unLeg)//est�
    {
        if(r==lista)
            lista=r->sig; // Si el nodo que debes eliminar es el primero, directamente  a lista le asignas el siguiente de r.
        else
            ant->sig=r->sig; // Si no es el primer nodo, al anterior le asingas el siguiente de r.
        delete r;
        //return true;
    }
    //else
        //return false;
}

void mostrarAprobados(Nodo*lista) //Esta función permite mostrar nodos de la lista en particular según una condición dada.
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

float promedioCurso(Nodo*lista) //Esta función muestra el uso de un contador y un sumador aplicado a listas.
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
