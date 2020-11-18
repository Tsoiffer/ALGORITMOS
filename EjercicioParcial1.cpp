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










/*
#include <iostream>
#include <string.h>
using namespace std;

const int SECTORES = 15;
const int DIAS = 31;

struct Gasto{
	unsigned short nroSector, dia;
	char detalle[200];
	int importe;
};

struct Nodo{
	Gasto info;
	Nodo* sig;
};

void mostrarGastos(Nodo*[SECTORES][DIAS]);
void mostrarGastosSector(Nodo*[SECTORES][DIAS], unsigned short);
void mostrarGastosQuincena(Nodo*[SECTORES][DIAS]);
void mayorGasto(Nodo*[SECTORES][DIAS]);
void generarArchivo();
bool procesarGastos(Nodo*[SECTORES][DIAS]);
Nodo* insertarOrdenado(Nodo*&, Gasto);

int main(){
	Nodo* sectores[SECTORES][DIAS];
	
	// INICIALIZAMOS TODOS LOS PUNTEROS DE LA MATRIZ EN NULL
	for(int i = 0; i<SECTORES; i++){
		for(int j = 0; j<DIAS; j++){
			sectores[i][j] = NULL;
		}
	}
	
	if(procesarGastos(sectores)){	
		cout<<"Procediendo a mostrar los gastos de cada sector en sus dias..."<<endl<<endl;
		mostrarGastosSector(sectores, 1);
		cout<<endl;
		mostrarGastos(sectores);
		cout<<endl;
		mostrarGastosQuincena(sectores);
		cout<<endl;
		mayorGasto(sectores);
	}else{
		cout<<"No se pudo procesar los gastos"<<endl;
		generarArchivo();
	}
}

bool procesarGastos(Nodo* sectores[SECTORES][DIAS]){
	FILE* arch;
	if(arch = fopen("Gastos.dat", "rb+")){
		Gasto aux;
		fread(&aux, sizeof(aux), 1, arch);
		while(!feof(arch)){
			insertarOrdenado(sectores[aux.nroSector-1][aux.dia-1], aux);
			fread(&aux, sizeof(aux), 1, arch);
		}
		fclose(arch);
		return true;
	}
	return false;
}

// INSERTAR ORDENADO POR IMPORTE DESCENDENTE
Nodo* insertarOrdenado(Nodo*& l, Gasto info){
	Nodo* nuevo = new Nodo();
	strcpy(nuevo->info.detalle, info.detalle); // PARA COPIAR UN CHAR A OTRO
	nuevo->info.dia = info.dia;
	nuevo->info.importe = info.importe;
	nuevo->info.nroSector = info.nroSector;
	nuevo->sig = NULL;
	if (l==NULL || info.importe > l->info.importe ){
		nuevo->sig = l;
		l = nuevo;
	}else{
		Nodo* aux = l;
		while( aux->sig !=NULL && info.importe < aux->sig->info.importe) {
			aux = aux->sig;
		}
		nuevo -> sig = aux->sig,
		aux -> sig = nuevo;
	}
	return nuevo;
}

void mostrarGastos(Nodo* sectores[SECTORES][DIAS]){
	for(int i=0; i<SECTORES; i++){
		cout<<"Sector: "<<i+1<<endl;
		for(int j=0; j<DIAS; j++){
			cout<<"|\tDia: "<<j+1<<endl;
			Nodo* auxSector = sectores[i][j];
			if(auxSector != NULL){
				while(auxSector != NULL){
					cout<<"|\t|\t"<<auxSector->info.detalle<<" | "<<auxSector->info.importe<<endl;
					auxSector = auxSector->sig;
				}
			}else{
				cout<<"|\t|\tNo hay gastos"<<endl;
			}
		}
	}
}

void mostrarGastosSector(Nodo* sectores[SECTORES][DIAS], unsigned short nroSector){
	int total = 0;
	// nroSector - 1 dado que los sectores son del 1 al 15 y en la matriz del 0 al 14
	for(int i = 0; i < DIAS; i++){
		Nodo* auxSector = sectores[nroSector-1][i];
		while(auxSector != NULL){
			total+=auxSector->info.importe;
			auxSector = auxSector->sig;
		}
	}
	cout<<"Total del sector "<<nroSector<<": "<<total<<endl;
}

void mostrarGastosQuincena(Nodo* sectores[SECTORES][DIAS]){
	int total = 0;
	for(int i = 0; i < SECTORES; i++){
		int subTotal = 0;
		for(int j = 0; j < 15; j++){
			Nodo* auxSector = sectores[i][j];
			while(auxSector != NULL){
				subTotal += auxSector->info.importe;
				auxSector = auxSector->sig;
			}
		}
		cout<<"Total de la 1ra quincena del sector "<<i+1<<": "<<subTotal<<endl;
		total += subTotal;
	}
	cout<<"Total de la quicena: "<<total<<endl;
}

void mayorGasto(Nodo* sectores[SECTORES][DIAS]){
	Gasto aux;
	aux.importe = -999999;
	for(int i=0; i<SECTORES; i++){
		for(int j=0; j<DIAS; j++){
			Nodo* auxSector = sectores[i][j];
			while(auxSector != NULL){
				if(aux.importe < auxSector->info.importe){
					strcpy(aux.detalle, auxSector->info.detalle);
					aux.dia = auxSector->info.dia;
					aux.importe = auxSector->info.importe;
					aux.nroSector = auxSector->info.nroSector;
				}
				auxSector = auxSector->sig;
			}
		}
	}
	cout<<"Mayor gasto:"<<endl;
	cout<<"|\tNro. Sector: "<<aux.nroSector<<endl;
	cout<<"|\tDia: "<<aux.dia<<endl;
	cout<<"|\tDetalle: "<<aux.detalle<<endl;
	cout<<"|\tImporte: "<<aux.importe<<endl;
}

// SIRVE PARA GENERAR UN ARCHIVO EN CASO DE Q NO EXISTA
void generarArchivo(){
	FILE* arch = fopen("Gastos.dat", "wb+");
	Gasto aux;
	cin>>aux.importe;
	while(aux.importe!=0){
		cin>>aux.dia;
		cin>>aux.nroSector;
		cin>>aux.detalle;
		fwrite(&aux, sizeof(aux), 1, arch);
		cin>>aux.importe;
	}
	fclose(arch);
}
*/