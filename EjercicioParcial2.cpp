/* Ejercicio 2 (ítems 5, 6, 7, 8 y 9)

Una entidad bancaria ofrece diferentes tipos de créditos (personal, hipotecario, etc.).
Se quiere hacer un programa para administrar la asignación de los mismos a las personas que los requieran y mostrar datos estadísticos.
Los créditos se asignan según los ingresos que han declarado, teniendo prioridad aquellos que tengan el mayor ingreso promedio.
Se utilizará una lista de créditos con sublista de inscriptos al crédito.
Se cuenta con el archivo de datos (binario) “Inscriptos.dat” con un registro por cada persona que se ha inscripto para solicitar un crédito, con el siguiente diseño de registro:
	Dni
	Apellido y nombre
	Código del crédito que solicita
	Ingreso Promedio

5) Función ingresarCreditos
El usuario del programa deberá ingresar los diferentes créditos que ofrece la entidad (código y descripción del crédito) y la cantidad de personas máxima a los que se les otorgará el mismo (cupo).
Con estos datos deberá preparar la estructura para almacenar, luego, los inscriptos. 
El ingreso de datos finaliza con código de crédito cero. Tener en cuenta que la estructura hay que utilizarla en las otras funciones
Desarrollar todas las funciones utilizadas.

6) Función organizarInscriptos
Procesar los datos del archivo, almacenándolos convenientemente en la estructura de datos para realizar la asignación de los créditos. Tener en cuenta que la estructura hay que utilizarla en las otras funciones.
Desarrollar todas las funciones utilizadas.

7) Función mostrarCreditoMayor
Informar código y descripción de crédito en el que hubo la mayor cantidad de inscriptos (suponer único)
Desarrollar todas las funciones utilizadas.

8) Función mostrarCreditosVacios
Informar código y descripción de crédito, ordenado por código de crédito de aquellos en los que no hubo inscriptos.
Desarrollar todas las funciones utilizadas.

9) Función mostrarListado de inscriptos asignados
Mostrar por cada crédito, ordenado por código: dni, apellido y nombre de cada persona a la que se le ha otorgado el crédito.
Se le otorga el crédito a la cantidad de personas que se inscribieron para ese crédito o la cantidad máxima posible, según criterio de asignación. 
Ejemplo: si el crédito tiene un cupo de 10 personas y se inscribieron 8 se le otorgará a los 8, si el crédito tiene un cupo de 10 y se inscribieron 15, se le otorgará a los 10 de mayor sueldo, o sea hay que mostrar, los 10 de mayor sueldo.
Desarrollar todas las funciones utilizadas.

*/
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cstring>
using namespace std;


struct datoArch 
{
    int dni;
    char apellidoYnombre [20];
    int codigo;
    int ingreso;
};

struct Nodosub
{
    datoArch info;
    Nodosub* sig;
};
struct infoNodo
{
    int codigo;
    char descripcion[10];
    int cupo;

};

struct Nodo
{
    infoNodo info;
    Nodosub * subnodo;
    Nodo* sig;
};
//Punto 5
void ingresarCreditos(Nodo*&);
void insertarordenado(Nodo*&,infoNodo);
//Punto 6
void organizarInscriptos(Nodo*&);
void buscarInsertarOrdenado(Nodo*&,datoArch);
void insertarOrdenado2(Nodo*&, datoArch);
//Punto 7
void mostrarCreditoMayor(Nodo*);
//Punto 8
void mostrarCreditosVacios(Nodo*);
void ordenarListaExistente(Nodo * & ,Nodo *& );
//Punto 9
void mostrarListado(Nodo*&);
//void ordenarListaExistente(Nodo * & ,Nodo *& ); Esta es igual a la del punto 8, hacen lo mismo y se les pasa los mismos parámetros.
void ordenarSubListaExistente(Nodosub * & ,Nodosub *& );

void mostrarRecibidoresDeCredito(Nodosub *, int);

int main()
{
    Nodo* lista=NULL;
    //Punto 5
    ingresarCreditos(lista);
    //Punto 6
    organizarInscriptos(lista);
    //Punto 7
    mostrarCreditoMayor(lista);
    //Punto 8
    mostrarCreditosVacios(lista);
    //Punto 9
    mostrarListado(lista);
}

//PUNTO 5
void ingresarCreditos(Nodo*&lista)// se ingresa ordenados
{
    infoNodo teclado;
    cout<<"Ingresar codigo o 0 para salir."<<endl;
    cin>>teclado.codigo;
    while (teclado.codigo!=0)
    {
        cout<<"Descripcion"<<endl;
        cin>>teclado.descripcion;
        cout<<"cupo maximo de personas que reciben el credito"<<endl;
        cin>>teclado.cupo;
        insertarordenado(lista,teclado);
        cout<<"Ingresar codigo (0 para salir)"<<endl;
        cin>>teclado.codigo;
    }


}
void insertarordenado (Nodo* & lista, infoNodo teclado)
{
    Nodo*ant,*r=lista;
    while(r!=NULL && r->info.codigo<teclado.codigo) //La condición sirve si la lista tiene un orden, pero básicamente recorre la lista.
    {
        ant=r;
        r=r->sig;
    }
    if(r!=NULL && r->info.codigo==teclado.codigo)
        {
            cout<<"Ya existe un credito con este codigo"<<endl;
        }
    else
    {
        Nodo*p=new Nodo;
        p->info=teclado;
        p->subnodo=NULL; //Poner en NULL porque es el subNodo y como estas armando al lista todavía no apunta a nada.
        p->sig=r; //Si r es Null quiere decir que P es el último elemento de la lista y si r no es Null quiere decir que P está antes que r y después que ant.
        if(r!=lista) //quiere decir que la lista no está vacía.
            ant->sig=p;
        else
            lista=p;//la lista está vacía o tiene un sólo elemento.
    }
}

//Punto 6

void organizarInscriptos(Nodo*& lista)
{   
    datoArch recibidora;
    FILE * arch=fopen("Inscriptos.dat","rb");
    if (arch!=NULL)
    {
        while(!feof(arch))
        {
            fread(&recibidora,sizeof(datoArch),1,arch);
            buscarInsertarOrdenado(lista,recibidora);
        }
    }
    
}

void buscarInsertarOrdenado(Nodo*& lista,datoArch recibidora) //Busca el lugar donde debe insertar al aspirante al credito y si no existe lo expresa.
{  
    Nodo*ant,*r=lista;
    while(r!=NULL && r->info.codigo != recibidora.codigo)
    {
        ant=r;
        r=r->sig;
    }
    if(r!=NULL && r->info.codigo==recibidora.codigo)
        {
            insertarOrdenado2(r,recibidora);
        }
    else
    {
        cout<<"No se encontró ningún crédito coincidente con el que quiere recibir esta persona"<<endl;
    }
}
void insertarOrdenado2(Nodo*& lista,datoArch recibidora) //Esta función arma las sublistas y las ordena.
{
    Nodosub *ant,*r=lista->subnodo;
    while(r!=NULL && r->info.ingreso >= recibidora.ingreso) //La condición sirve si la lista tiene un orden, pero básicamente recorre la lista.
    {
        ant=r;
        r=r->sig;
    }
                                //En caso que sean iguales, tiene prioridad el que aparezca primero en el archivo.
        Nodosub*p=new Nodosub;
        p->info=recibidora;
        p->sig=r; //Si r es Null quiere decir que P es el último elemento de la lista y si r no es Null quiere decir que P está antes que r y después que ant.
        if(r!=lista->subnodo) //quiere decir que la lista no está vacía.
            ant->sig=p;
        else
            lista->subnodo=p;//la lista está vacía o tiene un sólo elemento.
        
    
}

//Punto 7
//Este punto se puede hacer de dos formas, 1) Pones un contador en los Nodos y sumas 1 cada vez que ingresas un aspirante a un credito, despues recorres la lista y te fijas el mayor contador.2) Recorres lista y sublista y vas contando a manopla.


void mostrarCreditoMayor(Nodo* lista)
{
    int contadormayor=0;
    int contador;
    int codigomayor;
    char descripcionmayor[10];
    Nodo* r=lista;
    Nodosub* rs;
    while(r!=NULL) //con este while recorres la lista
    {
        rs=r->subnodo;
        contador=0;
        while (rs!=NULL) //recorres la sublista
        {
            contador++;
            rs=rs->sig;
        }
        if(contador>contadormayor) //Te fijas si la cantidad de inscriptos es mayor que el mayor registrado, si es mayor te guardas el codigo de inscripcion y la descripcion, si no, no haces nada.
        {
            contadormayor=contador;
            codigomayor=r->info.codigo;
            strcpy(descripcionmayor,r->info.descripcion);
        }
        r=r->sig;
    }
    cout<<"El credito con mayor inscriptos es: "<<codigomayor<<" cuya descripcion es: "<<descripcionmayor<<"que tiene "<<contadormayor<<" inscriptos"<<endl;
}


//Punto 8

void mostrarCreditosVacios(Nodo* lista)
{
    Nodo *r=lista;
    Nodo *aux=NULL, *listaCreditosNueva=NULL;

    while (r!=NULL)
    {
        aux=lista;
        lista=lista->sig;
        ordenarListaExistente(aux,listaCreditosNueva);
    }
    lista=listaCreditosNueva;
    r=lista;
    while (r!=NULL)
    {
        if(r->subnodo==NULL)
        {
            cout<<"En el credito de codigo: "<<r->info.codigo<<" de descripcion "<<r->info.descripcion<<"no tuvo inscriptos"<<endl;
        }
        r=r->sig;
    }
    
}    

void ordenarListaExistente(Nodo * & aux,Nodo *& lista)
{
    Nodo *ant, *r= lista;
    while(r!=NULL && aux->info.codigo < r->info.codigo) //ordenado de mayor a menor por codigo
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

//Punto 9

void mostrarListado(Nodo*& lista)
{
    Nodo *r=lista;
    Nodo *aux=NULL, *listaCreditosNueva=NULL;
    Nodosub *auxsub=NULL, *listaAspiranteNueva=NULL,*rs;

    while (r!=NULL) //Ordenas la Lista de Créditos 
    {
        aux=lista;
        lista=lista->sig;
        ordenarListaExistente(aux,listaCreditosNueva);
    }
    lista=listaCreditosNueva;
    r=lista;
    while (r!=NULL)
    {
        rs=r->subnodo;
        while (rs!=NULL)
        {
        auxsub=rs;
        rs=rs->sig;
        ordenarSubListaExistente(auxsub,listaAspiranteNueva);
        }
        cout<<"Las personas a las que se les otorgara el credito "<<r->info.descripcion<<" de codigo: "<<r->info.codigo<<" son: "<<endl;
        mostrarRecibidoresDeCredito(listaAspiranteNueva,r->info.cupo);
        r=r->sig;
    }
}
/*void ordenarListaExistente(Nodo * & aux,Nodo *& lista)
{
    Nodo *ant, *r= lista;
    while(r!=NULL && aux->info.codigo < r->info.codigo) //ordenado de mayor a menor por codigo
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
*/
void ordenarSubListaExistente(Nodosub * & aux,Nodosub *& lista )
{
    Nodosub *ant, *r= lista;
    while(r!=NULL && aux->info.ingreso < r->info.ingreso) //ordenado de mayor a menor por ingreso
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

void mostrarRecibidoresDeCredito(Nodosub* lista,int cupo)
{
    Nodosub * r=lista;
    int i=0; 
    while (r != NULL && i<=cupo)
    {
        cout<<"\tNombre: "<<r->info.apellidoYnombre<<" dni: "<<r->info.dni<<endl;
        i++;
        r=r->sig;
    }
}


/*9) Función mostrarListado de inscriptos asignados
Mostrar por cada crédito, ordenado por código: dni, apellido y nombre de cada persona a la que se le ha otorgado el crédito.
Se le otorga el crédito a la cantidad de personas que se inscribieron para ese crédito o la cantidad máxima posible, según criterio de asignación. 
Ejemplo: si el crédito tiene un cupo de 10 personas y se inscribieron 8 se le otorgará a los 8, si el crédito tiene un cupo de 10 y se inscribieron 15, se le otorgará a los 10 de mayor sueldo, o sea hay que mostrar, los 10 de mayor sueldo.
Desarrollar todas las funciones utilizadas.*/