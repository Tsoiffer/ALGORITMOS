#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;



struct Pedidos
{
char domicilio[25];
unsigned zona;
char comercio[25];
unsigned rubro;
unsigned importe;
};
struct RecorrerArchivoRepartidores
{
	int dni;
	char nom [25];
	int zona;
};
struct Negocio
{
	int rub;
	char nom[25];
	int zona;
};
struct NodoPedidos
{
    Pedidos info;
    NodoPedidos*sig;

};
struct Repartidor
{
	char nom [25];
	int zona;
	NodoPedidos*listaPed;
};
struct NodoRepartidor
{
    Repartidor info;
    NodoRepartidor*sig;
};
struct NodoARBOL
{

   char nom [25];
   unsigned cantvent;
    NodoARBOL*izq;
    NodoARBOL*der;
};



void armarVectorDePedidos(NodoPedidos* v[6], NodoARBOL*&);
void inicVectorDePedidos(NodoPedidos* v[6]);
void insertar(NodoPedidos*&,Pedidos );
void buscarInsertar(NodoARBOL*& , Negocio);
void  armarListaDeRepartidores(NodoRepartidor*&, NodoPedidos*v[6]);
void mostrarArbol(NodoARBOL*);
void buscarInsertarOrdenadoRepartidores(NodoRepartidor*&,Repartidor,int, NodoPedidos*&);
void insertarPedidoEnRepartidor(NodoRepartidor*&, NodoPedidos*&);
void mostrarCuantosPedidosLevantados(int);
void mostrarListaDeRepartidores(NodoRepartidor*);


int main()
{
    NodoPedidos*v[6];
    NodoARBOL*Arbol = NULL;
    NodoRepartidor*repartidores=NULL;

    inicVectorDePedidos(v);

    int bandera=0;
    while(bandera !=4)
    {
        cout<<"Ingrese un numero dependiendo lo que quiere realizar"<<endl<<
        "-1 Hacer un pedido"<<endl<<
        "-2 Asignar pedidos a un repartidor"<<endl<<
        "-3 Mostrar repartidores que hicieron entregas "<<endl<<
        "-4 Mostrar la cantidad de venta de los locales y salir"<<endl<<endl;
        cin>>bandera;

    if(bandera==1)
        armarVectorDePedidos(v,Arbol);
    if(bandera==2)
        armarListaDeRepartidores(repartidores,v);
    if(bandera==3)
        mostrarListaDeRepartidores(repartidores);
    if(bandera==4)
       mostrarArbol(Arbol);
    }
return 0;
}

void inicVectorDePedidos(NodoPedidos*v[])
{
    for (int i=0;i<=5;i++)
    {
        v[i]=NULL;
    }
}

void armarVectorDePedidos(NodoPedidos*v[],NodoARBOL*&Arbol)
{

    Pedidos pedido;
    Negocio recorrer;
    cout<<"Ingrese su domicilio: "<<endl;
    cin>>pedido.domicilio;
    cout<<"Ingrese su zona: "<<endl;
    cin>>pedido.zona;
    while((pedido.zona<1)||(pedido.zona>6))
    {
        cout<<pedido.zona<<" no es una zona valida."<<endl<<"Ingrese otra zona que se encuentre entre 1 y 6:"<<endl;
        cin>>pedido.zona;
    }

    cout<<"Ingrese el numero correspondiente al rubro de su negocio:"<<endl<<
    "0 para heladeria"<<endl<<
    "1 para pizzeria"<<endl<<
    "2 para bebidas "<<endl<<
    "3 para parrilla"<<endl;
    cin>>pedido.rubro;
    while((pedido.rubro<0)||(pedido.rubro>3))
    {
        cout<<pedido.rubro<<" no corresponde a ningun rubro."<<endl<<"vuelva a ingresarlo:"<<endl;
        cin>>pedido.rubro;
    }
    cout<<"Ingrese el nombre del comercio en el cual quiere pedir: "<<endl;
    cin>>pedido.comercio;
    cout<<"Ingrese el importe de su pedido:"<<endl;
    cin>>pedido.importe;

    FILE*arch;

    if(pedido.rubro==0)
        arch = fopen("Heladerias.dat","rb");
    if(pedido.rubro==1)
        arch = fopen("Pizzeria.dat", "rb");
    if(pedido.rubro==2)
        arch = fopen("Bebidas.dat", "rb");
    if(pedido.rubro==3)
        arch = fopen("Parrilla.dat", "rb");

    int bandera=0;
    if(arch!=NULL)
    {
        fread(&recorrer,sizeof(Negocio),1,arch);
        while(!feof(arch) && bandera!=1)
        {
            int i=strcmp(recorrer.nom,pedido.comercio);
            if(recorrer.zona==pedido.zona && i==0)
            {
                cout<<"Estamos tomando el pedido......"<<endl<<endl;
                insertar(v[pedido.zona-1],pedido);
                buscarInsertar(Arbol, recorrer);
                cout<<"Se tomo su pedido correctamente"<<endl<<endl;
                bandera=1;
            }
            fread(&recorrer,sizeof(Negocio),1,arch);
        }

    }
    if(bandera==0)
    cout<<"No fue tomado su pedido, favor verificar nombre y zona del negocio ingesado."<<endl<<endl;
    fclose(arch);
}

void insertar(NodoPedidos*&listapedidos,Pedidos pedido )
{

    NodoPedidos*p,*r;
    p=new NodoPedidos;
    p->info=pedido;
    r=listapedidos;
    if(r==NULL)
    {
        listapedidos=p;
    }
    else
    {
        while(r->sig!=NULL)
        {
            r=r->sig;
        }
        r->sig=p;
    }
    p->sig=NULL;
}

void buscarInsertar(NodoARBOL*& raiz , Negocio dato)
{

    NodoARBOL*ant,*p;
    p=raiz;
    int i=-1;
    while(p!=NULL && i!=0 )
    {
        i=strcmp(p->nom,dato.nom);
        if (i>0)
        {
            ant=p;
            p=p->izq;
        }
        else
        {
            if (i<0)
            {
                ant=p;
                p=p->der;
            }
        }
    }
    if (i==0)
        p->cantvent++;
    if (p==NULL)
    {
        NodoARBOL*n=new NodoARBOL;
        strcpy(n->nom,dato.nom);
        n->cantvent=1;
        n->der=NULL;
        n->izq=NULL;
        if(raiz==NULL)
            raiz=n;
        else
        {
            int j=strcmp(dato.nom,ant->nom);
            if (j<0)
                ant->izq=n;
            else
                ant->der=n;
        }
    }
}

void armarListaDeRepartidores(NodoRepartidor*& listaRepartidores, NodoPedidos*v[])
{
    Repartidor repartidor;
    RecorrerArchivoRepartidores recorrer;
    int cantpedidos;
    cout<<"Ingrese el nombre del repartidor: "<<endl;
    cin>>repartidor.nom;
    cout<<"Ingrese la zona del repartidor: "<<endl;
	cin>>repartidor.zona;
    while((repartidor.zona<1)||(repartidor.zona>6))
    {
        cout<<repartidor.zona<<" no es una zona valida."<<endl<<"Ingrese otra zona que se encuentre entre 1 y 6:"<<endl;
        cin>>repartidor.zona;
    }
    cout<<"Ingrese la cantidad de pedidos que retirara el repartidor: "<<endl;
    cin>>cantpedidos;
    FILE*arch=fopen("Repartidores.dat","rb");
    int bandera=0;
    if(arch!=NULL)
    {
        fread(&recorrer,sizeof(RecorrerArchivoRepartidores),1,arch);
        while(!feof(arch) && bandera!=1)
        {
            int i=strcmp(recorrer.nom,repartidor.nom);
            if(recorrer.zona==repartidor.zona && i==0)
            {
                buscarInsertarOrdenadoRepartidores(listaRepartidores,repartidor,cantpedidos,v[repartidor.zona-1]);
                cout<<"Se asigno repartidor al pedido."<<endl;
                bandera=1;
            }
            fread(&recorrer,sizeof(RecorrerArchivoRepartidores),1,arch);
        }
    }
    if(bandera==0)
        cout<<repartidor.nom<< " No es un repartidor valido"<<endl<<endl;
    fclose(arch);
}

void buscarInsertarOrdenadoRepartidores(NodoRepartidor*& listaRepartidores,Repartidor repartidor,int cantpedidos, NodoPedidos*&  listaPedidos)
{
    NodoRepartidor*ant,*p=listaRepartidores;
    while(p!=NULL && 0>strcmp (p->info.nom,repartidor.nom))
    {
        ant=p;
        p=p->sig;
    }
    if(p!=NULL && strcmp (p->info.nom,repartidor.nom)==0)
    {
        while( listaPedidos!=NULL && cantpedidos>0)
        {
            insertarPedidoEnRepartidor(p,listaPedidos);
            cantpedidos=cantpedidos-1;
        }
        mostrarCuantosPedidosLevantados(cantpedidos);
    }
    else
    {
        NodoRepartidor*n=new NodoRepartidor;
        strcpy(n-> info.nom,repartidor.nom);
        n->info.zona = repartidor.zona;
        n->info.listaPed = NULL;
        n->sig=p;
        if(p!=listaRepartidores)
        {
            ant->sig=n;
            while( listaPedidos!=NULL && cantpedidos>0)
            {
                insertarPedidoEnRepartidor(n,listaPedidos);
                cantpedidos=cantpedidos-1;
            }
            mostrarCuantosPedidosLevantados(cantpedidos);
        }
        else
        {
            listaRepartidores=n;
            while( listaPedidos!=NULL && cantpedidos>0)
            {
                insertarPedidoEnRepartidor(n,listaPedidos);
                cantpedidos=cantpedidos-1;
            }
            mostrarCuantosPedidosLevantados(cantpedidos);
        }
    }
}

void insertarPedidoEnRepartidor(NodoRepartidor*& repartidor,NodoPedidos*& listapedidos)
{
    NodoPedidos* auxiliar=listapedidos;
    listapedidos=listapedidos->sig;
    auxiliar->sig=NULL;
    NodoPedidos*ant,*p=repartidor->info.listaPed;
    while(p!=NULL && p->info.importe>auxiliar->info.importe)
    {
        ant=p;
        p=p->sig;
    }
    auxiliar->sig=p;
    if(p!=repartidor->info.listaPed)
    {
        ant->sig=auxiliar;
    }
    else
    {
        repartidor->info.listaPed=auxiliar;
    }
}

void mostrarCuantosPedidosLevantados(int cantpedidos)
{
    if(cantpedidos==0)
        cout<< "Se pudieron levantar todos los pedidos"<<endl<<endl;
	else
        cout<< "Quedaron "<<cantpedidos<<" sin poder levantarse dado que no había pedidos disponibles. "<<endl<<endl;
}

void mostrarListaDeRepartidores(NodoRepartidor* repartidor)
{
    NodoRepartidor* recorrerrepartidores=repartidor;
    NodoPedidos* recorrerpedidos;
    int contador;
    while(recorrerrepartidores!=NULL)
    {
        contador=1;
        recorrerpedidos=recorrerrepartidores->info.listaPed;
        cout<< "El repartidor "<< recorrerrepartidores->info.nom<< " entrego los siguientes pedidos: "<<endl;
        while (recorrerpedidos!=NULL)
        {
            cout<< "-Pedido "<<contador<< ":  domicilio "<<recorrerpedidos->info.domicilio
            <<", zona "<<recorrerpedidos->info.zona <<", comercio "<<recorrerpedidos->info.comercio
            <<", rubro "<<recorrerpedidos->info.rubro <<",  importe "<<recorrerpedidos->info.importe
            <<". "<<endl;
            recorrerpedidos=recorrerpedidos->sig;
        contador++;
        }
        recorrerrepartidores=recorrerrepartidores->sig;
    }
}

void mostrarArbol(NodoARBOL*raiz)
{
    if(raiz!=NULL)
    {
        mostrarArbol(raiz->izq);
        cout<< "El local: "<<raiz->nom<< " realizo " <<raiz->cantvent<< " ventas"<<endl;
        mostrarArbol(raiz->der);
    }
}
