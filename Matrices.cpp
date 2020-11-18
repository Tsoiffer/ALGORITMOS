#include <iostream>
using namespace std;


void inicFalso (bool m[][15],int cf, int cc)
{
    for (int j=0;j<cc;j++)
        for(int i=0;i<cf;i++)
            m[i][j]=false;
}

void cargarPorColum (int matriz [][3], int cf, int cc)
{
    for (int c=0; c<cc; c++)
    {
        for (int f=0;f<cf;f++)
            cin>>matriz[f][c];
    }
}

void mostrarPorFila (int m[][3],int cf,int cc)
{
    for(int i=0;i<cf;i++)
    {
        for(int j=0;j<cc;j++)
        cout<<m[i][j]<<"  "<<endl;
    }
}

void sumarValoresFila (int m[][3],int cf, int cc, int vcf[])
{
    for (int j=0;j<cc;j++)
    {
        for (int i=0;i<cf;i++)
            vcf[i]+=m[i][j];
    }
}
