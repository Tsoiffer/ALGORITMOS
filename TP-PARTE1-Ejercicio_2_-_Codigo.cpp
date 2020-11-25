#include <iostream>
#include <stdio.h>

using namespace std;

struct Negocio
{
	int rub;
	string nom;
	int zona;
};

void ordenar(Negocio v[4][60],int x,int y);
void MostrarSiHayRubroEnZona (int a, int indiceRubro);


int main()
{

    Negocio neg[4][60];
    int cont[4][6];
    int rubro;
    int zon;
    int i=0;
    int j=0;
    int x,y;

    for(j=0;j<4;j++)
    {
        for(i=0;i<6;i++)
            {
            cont[j][i]=0;
            }
    }

    FILE*archH = fopen("Heladerias.dat","wb");
    FILE*archP = fopen("Pizzeria.dat", "wb");
    FILE*archB = fopen("Bebidas.dat", "wb");
    FILE*archC = fopen("Parrilla.dat", "wb");

    if( archH==NULL || archP==NULL || archB==NULL || archC==NULL )
        cout<<"ERROR"<<endl;
	else
	{
        cout<<"Ingrese el numero correspondiente al rubro de su negocio,"<<endl<<
        "0 para heladeria"<<endl<<
        "1 para pizzeria"<<endl<<
        "2 para bebidas "<<endl<<
        "3 para parrilla"<<endl<<
        "(Ingrese -1 para           finalizar el programa):"<<endl;
        cin>>rubro;

        while (rubro != -1)
        {
            if(rubro<4 && rubro>-1 )
            {
                j= cont[rubro][0]+cont[rubro][1]+cont[rubro][2]+cont[rubro][3]+cont[rubro][4]+cont[rubro][5];

                cout<<"Ingrese la zona en la que trabaja (1-6): "<<endl;
                cin>>zon;
                while((zon<1)||(zon>6))
                {
                    cout<<zon<<" no es una zona valida."<<endl<<"Ingrese otra zona que se encuentre entre 1 y 6:"<<endl;
                    cin>>zon;
                }
                if(cont[rubro][zon-1]==10)
                {
                    cout<< "No se puede ingresar mas negocios de este rubro a la zona "<<zon<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
                }
                else
                {
                    neg[rubro][j].zona = zon;
                    cont[rubro][zon-1]=cont[rubro][zon-1]+1;
                    neg[rubro][j].rub=rubro;
                    cout<<"Ingrese el nombre del negocio:"<<endl;
                    cin>>neg[rubro][j].nom;
                }
            }
            else
            {
                cout<< "favor verificar el rubro"<<endl;
            }

            cout<<endl<<endl<<"Ingrese el numero correspondiente al rubro de su negocio,"<<endl<<
            "0 para heladeria"<<endl<<
            "1 para pizzeria"<<endl<<
            "2 para bebidas "<<endl<<
            "3 para parrilla"<<endl<<
            "(Ingrese -1 para finalizar el programa):"<<endl;
            cin>>rubro;
        }

        for (i=1; i<=6;i++)
        {
            if (cont[0][i-1]!=0 && cont[1][i-1]!=0 && cont[2][i-1]!=0 && cont[3][i-1]!=0)
                cout<<"Hay comercios para todos los rubros en la zona  "<<i<<endl;
            else
                cout<<" No hay comercios para todos los rubros en la zona  "<<i<<endl;
        }

        int a[4];
        for(x=0;x<4;x++)
        {
            a[x]=cont[x][0]+cont[x][1]+cont[x][2]+cont[x][3]+cont[x][4]+cont[x][5];
            MostrarSiHayRubroEnZona (a[x],x);
        }

        for(x=0;x<4;x++)
        {
            y=a[x];
            ordenar(neg, x , y);
        }

        fwrite(neg[0],a[0]*sizeof(Negocio),1,archH);
        fwrite(neg[1],a[1]*sizeof(Negocio),1,archP);
        fwrite(neg[2],a[2]*sizeof(Negocio),1,archB);
        fwrite(neg[3],a[3]*sizeof(Negocio),1,archC);

    }
    fclose(archH);
    fclose(archP);
    fclose(archB);
    fclose(archC);

}


void ordenar(Negocio v[4][60],int x,int y)
{
    int i=0,j;
    Negocio aux;
    bool cambio;
    do
    {
        cambio=false;
        for(j=0;j<y-1-i;j++)
        {
            if(v[x][j].nom>v[x][j+1].nom)
            {
                aux=v[x][j];
                v[x][j]=v[x][j+1];
                v[x][j+1]=aux;
                cambio=true;
            }
        }
        i++;
    }while(i<y && cambio);
}


void MostrarSiHayRubroEnZona (int a, int indiceRubro)
{   string rubro;
    switch (indiceRubro)
    {
        case 0:
            rubro= "heladerias";
            break;
        case 1:
            rubro= "pizzerias";
            break;
        case 2:
            rubro= "bebidas";
            break;
        case 3:
            rubro= "parrillas";
            break;
    }
    if (a)
        cout<<"El rubro de "<<rubro<<" tiene negocios en al menos una zona"<<endl;
    else
        cout<<"El rubro de "<<rubro<<" no tiene negocios en ninguna zona"<<endl;

}