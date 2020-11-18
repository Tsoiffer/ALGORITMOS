/* Ejercicio 1 (ítems 0, 1, 2, 3 y 4)

Se quiere almacenar en memoria los gastos efectuados por cada uno de los 15 sectores  de una empresa en un mes determinado para realizar un análisis estádístico.
 Para ello se implementará una matriz de listas, donde las filas representan los sectores y las columnas los días y cada elemento es la lista con cada gasto de ese sector en ese día.
Los datos para armar la estructura se encuentran en el archivo de datos binario  “Gastos.dat”, donde cada registro representa un gasto efectuado y tiene:
-	 Número de sector (de 1 a 15)
-	Día del mes (de 1 a 31)
-	Detalle
-	Importe gastado.
El archivo no está ordenado y puede tener varios gastos realizados por un mismo sector.

0)	Función armarEstructura debe generar la estructura en memoria con los datos del archivo, tener en cuenta que la estructura hay que utilizarla en las otras funciones. Desarrollar todas las funciones utilizadas.

1)	Función mostrarGastos debe mostrar por pantalla el siguiente listado:
		Sector 1
			Día 1
				…..  (detalle e importe de cada gasto)
				…..
			Día 2	
				…..
		Sector 2
			…..
Detalle e importe de cada gasto (ordenado de mayor a menor por importe) agrupado por sector y por día. 
Desarrollar todas las funciones utilizadas.

2)	Función mostrarGastosSector debe mostrar número de sector y sus gastos totales acumulados en el mes.

3)	Función mostrarGastos1Quincena debe mostrar los datos acumulados en la primera quincena (del día 1 al día 14 incluidos)

4)	Función mayorGasto debe mostrar qué sector y qué día se realizó el mayor gasto (suponer único)
*/
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cstring>
using namespace std;

struct datoArch
{
    int sector;
    int dia;
    int importe;
    char detalle [15];
};
struct Nodo
{
    datoArch info;
    Nodo* sig;
};

//Punto 0
void inicMatriz(Nodo* v[][31]);
void leerarchivo(Nodo* v[][31]);
void insertarordenado1(Nodo & ,datoArch);
void mostrarEnPantalla(Nodo* v[][31]);
void ordenarListas (Nodo* &);
void ordenarListaExistente(Nodo* &,Nodo* &);
void mostrarGastosSector(Nodo* v[][31]);
void mostrarGastosQuincena(Nodo* v[][31]);
void mayorGasto(Nodo* v[][31]);

int main()
{
    Nodo* v[15][31];
    //PUNTO 0
    inicMatriz (v);
    leerarchivo(v);
    /* Nosotros hicmos en el punto 0 la carga de datos ordenada para facilitar el punto 1, pero vamos a realizar el punto 1 como si no estuviera ordenada*/
    //PUNTO 1
    mostrarEnPantalla(v);
    //Punto 2
    mostrarGastosSector(v);
    //Punto 3
    mostrarGastosQuincena(v);
    //Punto 4
    mayorGasto(v);
}

//PUNTO 0

void inicMatriz (Nodo* v[15][31]) //Llenas filas para completar las columnas
{
    for (int i=0;i<15;i++)
        {
            for (int j=0;j<31;j++)
            {
                v[i][j]=NULL;  
            }
        }
}
void leerarchivo(Nodo* v[15][31])
{
    FILE*arch;
    datoArch recibidora;
    arch=fopen("Gastos.dat","rb");
    if(arch!=NULL)
    {
        while (!feof(arch))
        {
            fread (&recibidora,sizeof(datoArch),1,arch);
            insertarordenado1(v[recibidora.sector-1][recibidora.dia],recibidora);
        }

    }
}
void insertarordenado1(Nodo* & lista,datoArch recibidora) //Esto si bien no lo pide en el punto 0, sirve para que ya las listas estén ordenadas.
{
    Nodo*ant,*r=lista;
    while(r!=NULL && r->info.importe > recibidora.importe) //La condición sirve si la lista tiene un orden, pero básicamente recorre la lista.
    {
        ant=r;
        r=r->sig;
    }

        Nodo*p=new Nodo;
        p->info=recibidora;
        p->sig=r; //Si r es Null quiere decir que P es el último elemento de la lista y si r no es Null quiere decir que P está antes que r y después que ant.
        if(r!=lista) //quiere decir que la lista no está vacía.
            ant->sig=p;
        else
            lista=p;//la lista está vacía o tiene un sólo elemento.
        
    
}

//PUNTO 1
void mostrarEnPantalla(Nodo* v[15][31])
{
    for (int i=0;i<15;i++)
        {
            cout<<"El sector: "<<i+1<<endl; 
            for (int j=0;j<31;j++)
            {
                cout<<"\tEl dia: "<<j+1<<endl;    //el \t es para tabear al coutear las cosas.
                ordenarListas(v[i][j]);
                Nodo* r=v[i][j];
                while (r!=NULL)
                {
                    cout<<"\t\tel importe es: "<<r->info.importe<<"y el detalle es: "<<r->info.detalle<<endl;
                }
            }
        }
}
void ordenarListas(Nodo*& lista)
 // Acá creamos un nodo Aux para guardar la info que había en el primer nodo de Lista Y creamos un nuevo nodo "listaGastosNueva" que sirvió para ir creando otra lista con los Nodos de la lista que ya se había creado. Después ya en esa nueva lista la vas buscando insertar
{
    Nodo *aux=NULL, *listaGastosNueva=NULL;
    while (lista!=NULL)
    {
        aux=lista;
        lista=lista->sig;
        ordenarListaExistente(aux,listaGastosNueva);
    }
    lista=listaGastosNueva;
    
}    

void ordenarListaExistente(Nodo * & aux,Nodo *& lista)
{
    Nodo *ant, *r= lista;
    while(r!=NULL && aux->info.importe > r->info.importe)
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

//PUNTO 2
void mostrarGastosSector(Nodo* v[15][31])
{
    int gastos;
    for (int i=0;i<15;i++)
        {
            gastos=0;
            for (int j=0;j<31;j++)
            {
                Nodo* r=v[i][j];
                while (r!=NULL)
                {
                    gastos=gastos+r->info.importe;
                }
            }
            cout<<"El importe total del mes para el sector "<<i+1<<" fue : "<<gastos<<endl;
        }
}
//Punto 3
void mostrarGastos1Quincena (Nodo* v[15][31]) //Esta funcion muestra el gasto total de todas los sectores en los primeros 14 dias del mes.
{
    int gastos=0;
    for (int i=0;i<15;i++)
        {
            for (int j=0;j<14;j++)
            {
                Nodo* r=v[i][j];
                while (r!=NULL)
                {
                    gastos=gastos+r->info.importe;
                }
            }
        }
    cout<<"El importe total de todos los sectores en la 1° quincena fue: "<<gastos<<endl;
}

//Punto 4
void mayorGasto(Nodo* v[][31])
{
    int gastos;
    int sector;
    int dia;
    for (int i=0;i<15;i++)
        {
            gastos=0;
            for (int j=0;j<31;j++)
            {
                Nodo* r=v[i][j];
                while (r!=NULL)
                {
                    if (r->info.importe>gastos); //Guardas una variable el mayor importe y lo comparas contra el importe de la lista, si es mayor guardas el nuevo importe y encima guardas el sector y el dia.
                    {
                        gastos=r->info.importe;
                        dia=j+1;
                        sector=i+1;
                    }
                }
            }
        }
        cout<<"El sector "<<sector<<" tuvo el mayor gasto: "<<gastos<<" el dia "<<dia<<endl;
}

/*
No visibles

‘\n’ = salto de linea
‘\t’ = una tabulacion de 4 espacios
‘\b’ = borra un caracter hacia atras
‘\0’ = final de una cadena de caracteres
Visibles

‘\%’ = un porcentaje
‘\’’ = una comilla simple
‘\”’ = una comilla double
Asta el propio caracter se escapa asi mismo

‘\\’
*/


