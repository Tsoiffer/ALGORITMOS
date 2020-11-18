//Funciones de Vectores
#include <iostream>
#include<stdio.h>
#include <string.h>
using namespace std;

struct Parcial
{
    char nombre[21];
    int nota;
    
};
struct Producto
{
    int codigo;
    string descripcion;
    
};


void inicVector (int v [], int n);
void ingresarDatos (int v[], unsigned t);
int sumarDatos (int v[], int n);
int mostrarValorMayor (int v[], int t);
void mostrarPosicionDeUnValor (int v[],int t, int x);
int mostrarValorMaximoConSuPosicion (int v[], int t, int vp[], int & j);
void mostrarTodosLosValores (int v[], unsigned t);
int busquedaSecuencialA (int v[], unsigned t, int bus);
int busquedaSecuencialB (int v[], unsigned t, int bus);
int busquedaBinaria (int v[], unsigned t, int bus);
void burbujeoConDoWhile (int v[], unsigned t);
void burbujeoConDosCiclosFor (int v[], unsigned t);
void apareo (Parcial vp1[],int t1, Parcial vp2[], int t2);
void corteDeControl(Parcial vMuchos[],int tM,Parcial vUno[],int &j);
void mostrarDatosDeUnVectorDeStructs (Producto p[],int ce);
void ordenardatosvectordestruct(Producto v[],unsigned );
void pasarVectorAArchivo(Parcial V[], int tamanio);
void pasarVectorALista();



















void inicVector (int v[],int n)
{
    for(int i=0;i<n;i++)
        v[i]=0;

}
void ingresarDatos (int v [], unsigned t)
{
    for(unsigned i=0;i<t;i++)
        cin>>v[i];

}
int sumarDatos (int v[], int n)
{
    int sum=0;
    for (int i=0;i<n;i++)
    {
        sum=sum+ v[i];
    }
    return sum;
}
int mostrarValorMayor (int v[], int t)
{
    int m=0;
    for (int i=0;i<t;i++)
    {
        if (v[i]!=0 && v[i]>m)
        {
            m=v[i];
        }
    }
    return m;
}
void mostrarPosicionDeUnValor (int v[],int t, int x)
{
    for (int i=0; i<t;i++)
    {
        if (v[i]!=0 && v[i]==x)
        {
            cout<<i<<endl;
        }
    }
}
int mostrarValorMaximoConSuPosicion (int v [], int t, int vp[], int&j)
{
    int m=0;
    for (int i=0; i<t; i++)
    {
        if (v[i]!=0 && v[i]>m)
        {
            m=v[i];
            j=0;
            vp[j]=i;
            j++;
        }
        else
        {
            if (m==v[i])
            {
                vp[j]=i;
                j++;

            }
        }
        
    }
    return m;
}
void mostrarTodosLosValores (int v[], unsigned t)
{
    for (unsigned i;i<t;t++)
    {
        cout<<v[i]<<" "<<endl;
    }
}
int busquedaSecuencialA (int v[], unsigned t, int bus)
{
    unsigned i=0;
    while(i<t && v[i]!=bus)
        i++;
    if(i==t)
        return -1;
    else
        return i;

}
int busquedaSecuencialB (int v[], unsigned t, int bus)
{
    unsigned i=0;
    int pos=-1;
    while (i<t && pos==-1)
    {
        if (v[i]==bus)
        {
            pos=i;
        }
        i++;
    }
    return pos;
}

int busquedaBinaria (int v[], unsigned t, int bus)
{
    int pos=-1;
    unsigned desde=0, hasta=t-1,medio;
    while (desde<=medio && pos==-1)
    {
        medio=(desde+hasta)/2;
        if (v[medio]==bus)
        {
            pos=medio;
        }
        else
        {
            if(bus<v[medio])
                hasta=medio-1;
            else
            {
                desde=medio+1;
            }
            
        }
        
    }
    return pos;
}
void burbujeoConDoWhile (int v[], unsigned t)
{
    unsigned i=0,j;
    int aux;
    bool cambio;
    do
    {
        cambio=false;
        for (j=0;j<t-1-i;j++)
        {
            if (v[j]>v[j+1])
            {
                aux=v[j];
                v[j]=v[j+1];
                v[j+1]=aux;
                cambio=true;
            }
        }
        i++;
    } while (i<t && cambio);
    
}
void burbujeoConDosCiclosFor (int v[], unsigned t)
{
    int i, j, aux;
    for (i=0; i<t-1;i++) //Este ciclo permite realizar el ordenamiento de abajo "n" veces.
    {
        for (j=0;j<t-1-i;j++) //Este ciclo deja en la última posición al más grande o al más chico
        {
            if (v[j]>v[j+1])
            {
                aux=v[j];
                v[j]=v[j+1];
                v[j+1]=aux;
            }
        }
    }
}
void apareo (Parcial vp1[],int t1, Parcial vp2[], int t2)
{
    int i=0,j=0;
    while (i<t1 && j<t2)
    {   
        if (strcmp(vp1[i].nombre,vp2[j].nombre)==0)
        {
            if (vp1[i].nota>=8 && vp2[j].nota >=8)
                {cout<<vp1[i].nombre<<"promociona"<<endl;}
            else
            {
                if (vp1[i].nota>=6 && vp2[j].nota>=6)
                {
                    cout<<vp1[i].nombre<<"rinde final"<<endl;  
                }
                else
                    cout<<vp1[i].nombre<<"recursa"<<endl;
            
            }
            i++;
            j++;
        }
        else
        {
            if (strcmp(vp1[i].nombre,vp2[j].nombre)<0)
            {
                cout<<vp1[i].nombre<<"recursa"<<endl;
                i++;
            }
            else
            {
                cout<<vp2[j].nombre<<"recursa"<<endl;
                j++;
            }


        }
        
        
            
            
    }
    for(int k=i;k<t1;k++)
        cout<<vp1[k].nombre<<" Recursa"<<endl;
    for(int k=j;k<t2;k++)
        cout<<vp2[k].nombre<<" Recursa"<<endl;

}

//CORTE DE CONTROL

void CORTEDECONTROL(Parcial vectorviejo[],int tM,Parcial vectornuevo[],int &j) //Tiene que tener un orden
{
    int i=0,suma,cont;
    j=0;
    //string nom;
    while(i<tM)
    {
        strcpy(vectornuevo[j].nombre,vectorviejo[i].nombre); //Están creando un nuevo vector donde sólo aparezcan 1 vez los datos.
        suma=0;
        cont=0;
        do
        {
            suma+=vectorviejo[i].nota;
            cont++;
            i++;
        }while(i<tM && strcmp(vectorviejo[i].nombre,vectornuevo[j].nombre)==0);
        //vUno[j].nombre=nom;
        vectornuevo[j].nota=suma/cont;
        j++;
    }
}

void mostrarDatosDeUnVectorDeStructs (Producto p[],int ce)
{
    for(int i=0;i<ce;i++)
        cout<<p[i].codigo<<p[i].descripcion<<endl;
}


//ORDENAR DATOS VECTOR DE STRUCT
struct Producto
{
    int codigo;
    string descripcion;
    
};

void ordenardatosvectordestruct(Producto v[],unsigned );

void ordenardatosvectordestruct(Producto v[],unsigned t)
{
    unsigned i=0,j;
    Producto aux;
    bool cambio;
    do
    {
        cambio=false;
        for(j=0;j<t-1-i;j++)
        {
            if(v[j].codigo>v[j+1].codigo)
            {
                aux=v[j];
                v[j]=v[j+1];
                v[j+1]=aux;
                cambio=true;
            }
        }
        i++;
    }while(i<t && cambio);
}



//AGREGAR DATOS A ARCHIVO BINARIO


void pasarVectorAArchivo(Parcial V[], int tamanio)
{
    FILE *aParcial=fopen("Parcial1.dat","ab");//con "ab" se posiciona al final del archivo
    if(aParcial!=NULL)
    {

        for (int i=0;i<tamanio; i++)
        {
            fwrite(&V[i],sizeof(Parcial),1,aParcial);

        }
        fclose(aParcial);
    }
}

struct NODO
{
    Parcial info;
    NODO*sig;
};

void buscarinsertarordenado(Parcial, NODO *&);

//Suponemos que el vector ya existe, está lleno, ordenado y que los datos no se repiten. (Ordenar y hacer un corte de Control antes)
void pasarVectorALista(Parcial v[], int tamanio, NODO*& lista)
{
    for (int i = 0; i < tamanio; i++)
    {
        buscarinsertarordenado(v[i], lista); //No desarrollamos la funcion, ver en el apartado listas.cpp y cambiar lo que haga falta.
    }
}