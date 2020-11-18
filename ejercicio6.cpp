/*6)	La ciudad de Buenos Aires requiere un estudio estadístico de infracciones realizadas por los vehículos en sus calles. Para ello cuenta con un archivo de infracciones, ordenado por fecha de la infracción creciente, con el siguiente diseño:
	Patente (7 caracteres)
	Fecha de Infracción (int, aammdd)
	Código de infracción (int, 1 a 100)

	Se desea obtener un listado ordenado por código de infracción decreciente con las 	patentes que cometieron más de una vez la misma infracción.
NOTA: vector de 100 listas de infracciones con una bandera cuando tiene mas de una infraccion

*/

#include <iostream>
#include <stdio.h>


using namespace std;


//archivo de infracciones (ordenado por fecha de la infraccion creciente)

struct datoArch
{
    char patente[8];
    int fecha;
    int codigoInf;
};

struct Nodo
{
    datoArch info;
    int contador;
    Nodo* sig;
};

void inicializarVector(Nodo* );
void leerarchivo(Nodo* );
void mostrarlista(Nodo* );
void buscarInsertar(Nodo* &, datoArch);

int main()
{
    Nodo* v[100];
    inicializarVector(v);
    leerarchivo(v);
    mostrarlista(v);
    
}

void inicializarVector(Nodo* v[])
{
    for (int i=0;i<100;i++)
    {
        v[i]=NULL;
    }
}
void leerarchivo (Nodo* v[])
{
    FILE* arch;
    datoArch recibidora; //recibe los datos leidos del archivo

    arch=fopen("Infracciones.dat","rb");
    if(arch!=NULL)
    {
        while(!feof(arch))
        {
            fread(&recibidora,sizeof(datoArch),1,arch);
            buscarInsertar(v[recibidora.codigoInf-1], recibidora);

        }
    }
}
void buscarInsertar(Nodo*&lista,datoArch recibidora) //Esta función tiene dos objetivos, te devuelve si ya existe un nodo con x información o te inserta un nuevo nodo donde debe hacerlo.
{
    Nodo*ant,*r=lista;
    while(r!=NULL && r->info.patente<recibidora.patente) //Se podria hacer con un distinto y no lo ordenariamos.
    {
        ant=r;
        r=r->sig;
    }

    if(r==NULL || r->info.patente>recibidora.patente) //no esta en la lista, ya sea porque la lista está vacía o si es que la lista no está vacía.
    {
        Nodo*p=new Nodo;
        p->info=recibidora;
        p->sig=r; //Si r es Null quiere decir que P es el último elemento de la lista y si r no es Null quiere decir que P está antes que r y después que ant.
        p->contador=0;//contador en 0 porque es el primer nodo existente pero despues en la condicion tiene que ser mayor a 0 y no a 1.
        if(r!=lista) //quiere decir que la lista no está vacía.
            ant->sig=p;
        else
            lista=p;//la lista está vacía o tiene un sólo elemento.
    }
    else// Este es el caso en el que se encuentra en la lista
        r->contador++;
}

void mostrarlista (Nodo* v[])
{   
    for (int i=99;i>=0;i--)
    {
        while (v[i]!=NULL)
        {
            if (v[i]->contador>0)
            {
                cout<<"La patente: "<<v[i]->info.patente<<" tiene "<<v[i]->contador<<" infracciones, del tipo "<<i+1<<endl;
            }
            v[i]=v[i]->sig;
        }
    }
}

