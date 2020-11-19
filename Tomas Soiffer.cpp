#include <iostream>
#include <stdio.h>

using namespace std;

struct DatoArchivo
{
    unsigned mesVto;
    unsigned cuil;
    unsigned codImp;
    float importe;
};
struct DatoSub
{
    unsigned codImp;
    float importe;
};
struct NodoSub
{
    DatoSub dato;
    NodoSub*sig;
};
struct DatoLista
{
    unsigned cuil;
    NodoSub*listaPagos;
};
struct Nodo
{
    DatoLista dato;
    Nodo *sig;
};

void generarEstructura(FILE*,Nodo*&);
void pagoMayor(Nodo*);
void informarContriPoco(Nodo*);
void informarImpuestoCod(Nodo*,int);
void eliminarContribuyentes(Nodo*&);

//en esta funcion se recorres la sublista de un contribuyente y se suman los importes del contribuyente, devulve la sumatoria de los importes
int sumarimp(NodoSub*);//se utiliza en el caso 2

int main()
{
    Nodo*estructura;
    FILE*archivo=fopen("Impuestos2019.dat","rb");
    if(archivo!=NULL)
    {
        generarEstructura(archivo,estructura);
        pagoMayor(estructura);
        informarContriPoco(estructura);
        cout<<"Ingresar en codigo de impuesto para saber cantidad de contribuyentes que lo abonaron"<<endl;
        int codigo;
        cin>>codigo;
        informarImpuestoCod(estructura,codigo);
        //me imagine 2 posibles casos y desarrolle ambos
        eliminarContribuyentes(estructura);

        fclose(archivo);
    }


    return 0;
}

//Cree ambas funciones para dos casos distintos
//Caso 1
//En este doy por entendido que en el momento que se genero la estructura en caso de que un contribuyente no pagara osea que su importe es "0" no se le creara un nodo en la sublista y quedara apunta a NULL(dato.listaPagos==NULL)
void eliminarContribuyentes(Nodo*& lista)
{
    Nodo *r=lista;
    Nodo *ant=NULL, *aux=NULL;
    while (r!=NULL) //En este while se recorre toda la lista de contibuyentes 
    {
        //doy por entendido que en el momento que se genero la estructura en caso de que un contribuyente no pagara osea que su importe es "0" no se le creara un nodo en la sublista y quedara apunta a NULL(dato.listaPagos==NULL)
        if(r->dato.listaPagos==NULL)
        {
            aux=r;
            r=r->sig;
            delete aux;
            if(ant!=NULL) //aca pergunta si es distinto al primer contibuyente que se encuentra en la lista
            {
                ant->sig=r;            
            }
            else //esta es el caso en que se elimine el primer contribuyente se la lista
            {
                lista=r;
            }
        }
        else//es es el caso en que no se tiene que eliminar al contribuyente
        {
            ant=r;
            r=r->sig;
        }
    }
    return ;
}

//Caso 2
//En esta cosa me imagino que se creo el sub nodo pero con el importe en "0" entonces recorro toda la sublista y sumo los importes, si la suma de todos los importes es 0 elimino el nodo del contribuyente
/*
void eliminarContribuyentes(Nodo*& lista)
{
    Nodo *r=lista;
    Nodo *ant=NULL, *aux=NULL;
    int sumatoriadeimportes=0;
    while (r!=NULL) //En este while se recorre toda la lista de contibuyentes 
    {
        sumatoriadeimportes=sumarimp(r->dato.listaPagos);//
        if(sumatoriadeimportes==0)
        {
            aux=r;
            r=r->sig;
            delete aux;
            if(ant!=NULL) //aca pergunta si es distinto al primer contibuyente que se encuentra en la lista
            {
                ant->sig=r;            
            }
            else //esta es el caso en que se elimine el primer contribuyente se la lista
            {
                lista=r;
            }
        }
        else//es es el caso en que no se tiene que eliminar al contribuyente
        {
            ant=r;
            r=r->sig;
        }
    }
    return ;
}

//en esta funcion se recorres la sublista de un contribuyente y se suman los importes del contribuyente, devulve la sumatoria de los importes 
int sumarimp(NodoSub*lista)
{
    int suma=0;
    NodoSub* r;
    while(r!=NULL)
    {
        suma=suma+r->dato.importe;
        r=r->sig;
    }
    return suma;
}
*/