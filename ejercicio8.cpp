/*8)	Una biblioteca necesita un programa que efectúe las altas en el archivo maestro de libros. Para ello cuenta con:
a)	LIBROS.dat, archivo maestro de libros ordenado por código de libro, con 	un registro por cada libro, con el siguiente diseño:
	Código de libro (int)
	Título del libro (30 caracteres)
	Apellido del autor (15 caracteres)
	Nacionalidad (int)
	Cantidad de ejemplares 

b)	 NOVEDADES.dat, archivo con los libros a dar de alta  sin ningún orden, con el mismo diseño del archivo maestro.

	Se pide realizar la metodología necesaria para que el programa:
1)	Genere un nuevo archivo LIBROSACT.dat, con el mismo diseño y orden que el 	maestro y con las altas incorporadas. 
Nota: hacer una lista ordenada con el archivo de novedades y después aparearlo con el archivo de libros;
	2) Emitir el siguiente listado, agrupado por nacionalidad y ordenado ascendente por cantidad total de autores:
NOTA: Lista de nacionalidades con sub lista de autores;
              		Nacionalidad...................................   Cantidad Total de autores: 999
			Apellido del Autor             Cantidad total de títulos  
			……......................	                    99
*/
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cstring>
using namespace std;

struct datlibro
{
    int codlib;
    char titulo[31];
    char apellido[16];
    int nac;
    int cant;
};

struct infoAut
{
    char apellido[16];
    int cantTit;
    infoAut* sig;
};

struct NodoNac //Lista de nacionalidades con sub lista de autores
{
    int nac;
    int cant;
    infoAut* subnodo; //infoAut es lo que permite crear una sub lista
    NodoNac* sig;
};
struct NodoLibrosAct
{
    datlibro info;
    NodoLibrosAct* sig;
};

void leernovedades(NodoLibrosAct *&,NodoNac *&);
void leerlibros(NodoLibrosAct *&,NodoNac *&);
void crearlibrosact(NodoLibrosAct *);
void ordenarlistanac(NodoNac *&);
void buscarinsertarordenado(datlibro, NodoLibrosAct *&);
void buscarinsertarnac(datlibro, NodoNac *&);
void buscarinsertaraut (datlibro, NodoNac *&);
void insertarordenado (NodoNac *&,NodoNac *&);


int main() 
{
NodoLibrosAct *listaLibAct=NULL;
NodoNac *listaNac=NULL;


leernovedades(listaLibAct,listaNac);
leerlibros(listaLibAct,listaNac);
crearlibrosact(listaLibAct);
ordenarlistanac(listaNac);
while(listaNac!=NULL)
{
    cout<<"La Nacionalidad:    "<<listaNac->nac<<" tiene un total de "<<listaNac->cant<<"autores"<<endl;
    while (listaNac->subnodo!=NULL)
    {
        cout<<"El autor"<<listaNac->subnodo->apellido<<"tiene un total de "<<listaNac->subnodo->cantTit<<endl;
        listaNac->subnodo=listaNac->subnodo->sig;
    }
    listaNac=listaNac->sig;
}
}


void leernovedades(NodoLibrosAct *& listaLibAct,NodoNac *&listaNac)
{   datlibro recorrer;
    FILE* arch=fopen("NOVEDADES.dat","rb");
    while (!feof(arch))
    {
        fread(&recorrer,sizeof(datlibro),1,arch);
        buscarinsertarordenado(recorrer, listaLibAct);
        buscarinsertarnac(recorrer, listaNac);

    }
    fclose(arch);
}


void leerlibros(NodoLibrosAct *& listaLibAct,NodoNac *& listaNac)
{   datlibro recorrer;
    FILE* arch=fopen("LIBROS.dat","rb");
        while (!feof(arch))
    {
        fread(&recorrer,sizeof(datlibro),1,arch);
        buscarinsertarordenado(recorrer, listaLibAct);
        buscarinsertarnac(recorrer, listaNac);

    }
    fclose(arch);
    
    
}
void crearlibrosact(NodoLibrosAct *listaLibAct)
{

    FILE* arch=fopen("LIBROSACT.dat","wb");
    while (listaLibAct != NULL)
    {
        fwrite(&listaLibAct->info,sizeof(datlibro),1,arch);
        listaLibAct=listaLibAct->sig;
    }
    fclose(arch);
}

void ordenarlistanac(NodoNac *&listaNac) // Acá creamos un nodo Aux para guardar la info que había en el primer nodo de Lista Nac Y creamos un nuevo nodo "listaNacOrden" que sirvió para ir creando otra lista con los Nodos de la lista que ya se había creado. Después ya en esa nueva lista la vas buscando insertar
{
    NodoNac *aux=NULL, *listaNacOrden=NULL;
    while (listaNac!=NULL)
    {
        aux=listaNac;
        listaNac=listaNac->sig;
        insertarordenado(aux,listaNacOrden);
    }
    listaNac=listaNacOrden;
}

void buscarinsertarordenado(datlibro recorrer, NodoLibrosAct*& listaLibAct)
{  NodoLibrosAct*ant,*r=listaLibAct;
    while(r!=NULL && r->info.codlib > recorrer.codlib)
    {
        ant=r;
        r=r->sig;
    }
    if(r!=NULL && r->info.codlib==recorrer.codlib)
        {
            r->info.cant+=recorrer.cant;
        }
    else
    {
        NodoLibrosAct*p=new NodoLibrosAct;
        p->info=recorrer;
        p->sig=r;
        if(r!=listaLibAct)
            ant->sig=p;
        else
            listaLibAct=p;
    }
}
    

void buscarinsertarnac(datlibro recorrer, NodoNac *&listaNac)
{
    NodoNac*ant,*r=listaNac;
    while(r!=NULL && r->nac != recorrer.nac)
    {
        ant=r;
        r=r->sig;
    }
    if(r!=NULL && r->nac==recorrer.nac)
        {
            buscarinsertaraut(recorrer,r);
            r->cant++;
        }
    else
    {
        NodoNac*p=new NodoNac;
        p->cant=0;
        p->nac=recorrer.nac;
        p->sig=r;
        p->subnodo=NULL;
        if(r!=listaNac)
            ant->sig=p;
        else
            listaNac=p;
    }
}

void buscarinsertaraut(datlibro recorrer, NodoNac *&listaNac)
{
    infoAut*  ant, *r= listaNac -> subnodo;
    while(r != NULL && (strcmp(r->apellido,recorrer.apellido) != 0))
    {
        ant=r;
        r=r->sig;
    }
    if (r != NULL && strcmp(r->apellido,recorrer.apellido)==0)
    {
        r->cantTit+=recorrer.cant;
    }
    else
    {
        infoAut *p=new infoAut;
        p->cantTit=recorrer.cant;
        strcpy (r->apellido, recorrer.apellido);
        p->sig=r;
        if(r!=listaNac->subnodo)
            ant->sig=p;
        else
            listaNac->subnodo=p;
    }
    
}
void insertarordenado(NodoNac * & aux,NodoNac *& listaNacOrden)
{
    NodoNac *ant, *r= listaNacOrden;
    while(r!=NULL && aux->cant < r->cant)
    {
        ant=r;
        r=r->sig;
    }
    if(r==NULL)
    {
        ant->sig=aux;
        aux->sig=NULL;
    }
    else
    {
        ant->sig=aux;
        aux->sig=r;
    }
}