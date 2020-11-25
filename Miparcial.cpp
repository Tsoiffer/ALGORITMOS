#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cstring>
using namespace std;

struct DatoArchivo
{
    unsigned legajo;
    char apeYNom[31];
    unsigned codBeca;
    float ingresoProm;
};
struct DatoSub
{
    unsigned legajo;
    char apeYNom[31];
    float ingresoProm;
};
struct NodoSub
{
    DatoSub dato;
    NodoSub*sig;
};
struct DatoLista
{
    unsigned codBeca;
    char descripcion[41];
    unsigned cantBenef;
    NodoSub*listaInscriptos;
};
struct Nodo
{
    DatoLista dato;
    Nodo *sig;
};

void ingresarBecas(Nodo*&);
void organizarInscriptos (FILE*,Nodo*&);
//Funciones extra que desarrollé:
void buscarInsertarOrdenado(Nodo*&,DatoArchivo);
void insertarOrdenado(Nodo*& ,DatoArchivo);

void mostrarBecaMayor(Nodo*);
void mostrarBecasVacias(Nodo*);
void mostrarListado(Nodo*);

int main()
{
    Nodo*estructura;
    FILE*archivo=fopen("Inscriptos.dat","rb");
    if(archivo!=NULL)
    {
        ingresarBecas(estructura);
        organizarInscriptos(archivo,estructura);
        mostrarBecaMayor(estructura);
        mostrarBecasVacias(estructura);
        mostrarListado(estructura);

        fclose(archivo);
    }

    return 0;
}
void organizarInscriptos(FILE* arch,Nodo*& lista)
{
    DatoArchivo lectoraDeArchivo; //Defino una variable de tipo del archivo (DatoArch) para poder leer el archivo.
    while(!feof(arch))
        {
            fread(&lectoraDeArchivo,sizeof(DatoArchivo),1,arch); //Leo el archivo
            buscarInsertarOrdenado(lista,lectoraDeArchivo);
        }
}



void buscarInsertarOrdenado(Nodo*& lista,DatoArchivo lectoraDeArchivo) //Busca el lugar donde debe insertar al solicitante de las becas.
{
    Nodo*ant,*r=lista;
    while(r!=NULL && r->dato.codBeca != lectoraDeArchivo.codBeca) //Comparo si el codigo de la beca coincide con el que trae el dato del archivo.
    {
        ant=r;
        r=r->sig;
    }
    if(r!=NULL && r->dato.codBeca==lectoraDeArchivo.codBeca)
        {
            insertarOrdenado(r,lectoraDeArchivo);
        }
    else //Este es el caso en el que nunca coincidió ningún codigo, entonces "r" es NULL y por ende se muestra por pantalla que no se encontró
    {
        cout<<"No se encontró ninguna beca coincidente con la que quiere recibir esta persona"<<endl;
    }
}
void insertarOrdenado(Nodo*& lista,DatoArchivo lectoraDeArchivo) //Esta función arma las sublistas y las ordena.
{
    NodoSub *ant,*r=lista->dato.listaInscriptos; //Creamos ant y r de tipo NodoSub para recorrer la sublista e insertar donde se deba a los que aspiran a una beca dada.
    while(r!=NULL && r->dato.ingresoProm <= lectoraDeArchivo.ingresoProm) //Básicamente, avanzamos en la sublista si el ingreso promedio es menor o igual. (La ordenamos de menor a mayor por ingreso promedio)
    {
        ant=r;
        r=r->sig;
    }
                                //En caso que sean iguales, tiene prioridad el que aparezca primero en el archivo.
                                //Ahora no importa si se salio por mayor o por r=NULL, se hace lo mismo
        NodoSub*p=new NodoSub;
        p->dato.legajo=lectoraDeArchivo.legajo;
        strcpy(p->dato.apeYNom,lectoraDeArchivo.apeYNom); //Copia lo que dice en lectoraDeArchivo.apeYNom en p->dato.apeYNom
        p->dato.ingresoProm=lectoraDeArchivo.ingresoProm;
        p->sig=r; //Si r es Null quiere decir que P es el último elemento de la sublista y si r no es Null quiere decir que P está antes que r y después que ant.
        if(r!=lista->dato.listaInscriptos) //quiere decir que la sublista no está vacía y que se avanzó.
            ant->sig=p;
        else
            lista->dato.listaInscriptos=p;


}
