//Funciones de Vectores
#include <iostream>
using namespace std;

void inicVector (int v [], int n);
void ingresarDatos (int v[], unsigned t);
int sumarDatos (int v[], int n);
int mostrarValorMayor (int v[], int t);
void mostrarPosicionDeUnValor (int v[],int t, int x);



















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
    
}