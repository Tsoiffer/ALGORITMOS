//Funciones de Archivos
#include <iostream>
#include<stdio.h>
#include <string.h>
using namespace std;

/*MODO APERTURA ARCHIVO BINARIOS

rb=lectura, punt al ppio
wb=escritura, punt al ppio
ab=añadir, punt al final
r+b=Lect/Escr, punt al ppio
w+b=Lect/Escr, punto al ppio
a+b=Lect/Añad, punt al final
*/

/*FUNCIONES ARCHIVO BINARIOS
FILE *f
fopen
fclose
fflush (Vacía contenido)
SEEK_CUR (Lugar actual)
SEEK_END (Desde el final)
SEEK_SET (Desde el inicio)
int ftell (f) Valor actual del indicador
int fseek (f, cant, desde) Define indicador de posición a partir de una posicion
*/

struct Parcial
{
    unsigned dni;
    char nom[21];
    unsigned nota;
    unsigned leg;
};

//GENERAR, ABRIR Y CARGAR DATOS EN  ARCHIVO BINARIO

int main()
{
    FILE*archParcial;
    char nomArchivo[21];
    cout<<"Ingrese Nombre Archivo (.dat)";
    cin>>nomArchivo;
    archParcial=fopen(nomArchivo,"wb");
    if(archParcial==NULL)
        cout<<"ERROR"<<endl;
    else
    {
        Parcial p;
        cout<<"DNI ";
        cin>>p.dni;
        while(p.dni!=0)
        {
            cout<<"Nombre ";
            cin>>p.nom;
            cout<<"Nota ";
            cin>>p.nota;
            fwrite(&p,sizeof(Parcial),1,archParcial);
            cout<<"DNI ";
            cin>>p.dni;
        }
        fclose(archParcial);
    }
    return 0;
}

//AGREGAR DATOS A ARCHIVO BINARIO


int main()
{
    FILE *aParcial=fopen("Parcial1.dat","ab");
    if(aParcial!=NULL)
    {
        Parcial p;
        cout<<"DNI ";
        cin>>p.dni;
        while(p.dni!=0)
        {
            cout<<"Nombre ";
            cin>>p.nom;
            cout<<"Nota ";
            cin>>p.nota;
            fwrite(&p,sizeof(Parcial),1,aParcial);
            cout<<"DNI ";
            cin>>p.dni;
        }
        fclose(aParcial);
    }
}

//MOSTRAR DATOS DE ARCHIVO

int main()
{
    FILE *arch;
    char nomArchivo[21];
    cout<<"Nombre Archivo (.dat) ";
    cin>>nomArchivo;
    arch=fopen(nomArchivo,"rb");
    if(arch==NULL)
        cout<<"ERROR"<<endl;
    else
    {
        Parcial par;
        fread(&par,sizeof(Parcial),1,arch);
        while (!feof(arch))
        {
            cout<<par.dni<<"  "<<par.nom<<"  "<<par.nota<<endl;
            fread(&par,sizeof(Parcial),1,arch);
        }
        fclose(arch);
    }
    return 0;
}

//CORTE DE CONTROL



void corteControl(FILE*a,FILE*af)
{
    Parcial p,pf;
    unsigned dniA,sum,cont,prom;
    char nomA[21];
    fread(&p,sizeof(Parcial),1,a);
    while(!feof(a))
    {
        pf.dni=p.dni;
        strcpy(pf.nom,p.nom);
        sum=0;
        cont=0;
        do
        {
        sum+=p.nota;
        cont++;
        fread(&p,sizeof(Parcial),1,a);
        }
        while(!feof(a)&&p.dni==pf.dni);
        pf.nota=sum/cont;
        fwrite(&pf,sizeof(Parcial),1,af);
    }
}

//APAREO

//estructuras
string condicion(int , int );
void apareo(FILE*,FILE*);

void apareo(FILE*ap1,FILE*ap2)
{
    Parcial p1,p2;
    fread(&p1,sizeof(Parcial),1,ap1);
    fread(&p2,sizeof(Parcial),1,ap2);
    while(!feof(ap1)&&!feof(ap2))
    {
        if(p1.dni<p2.dni)
        {
            cout<<p1.dni<<condicion(p1.nota,0)<<endl;
            fread(&p1,sizeof(Parcial),1,ap1);
        }
        else
        {
            if(p1.dni==p2.dni)
            {
                cout<<p1.dni<<condicion(p1.nota,p2.nota)<<endl;
                fread(&p1,sizeof(Parcial),1,ap1);
                fread(&p2,sizeof(Parcial),1,ap2);
            }
            else
            {
                cout<<p2.dni<<condicion(0,p2.nota)<<endl;
                fread(&p2,sizeof(Parcial),1,ap2);
            }
        }
    }
    while(!feof(ap1))
    {
        cout<<p1.dni<<condicion(p1.nota,0)<<endl;
        fread(&p1,sizeof(Parcial),1,ap1);
    }
    while(!feof(ap2))
    {
        cout<<p2.dni<<condicion(0,p2.nota)<<endl;
        fread(&p2,sizeof(Parcial),1,ap2);
    }
}

string condicion(int par1, int par2)
{
    if(par1>5 && par2>5)
        return "aprobo";
    else
    {
        return "des aprobo";
    }
}


//BUSQUEDA SECUENCIAL

int busquedaSecuencial(FILE*,unsigned ,Parcial &);

int busquedaSecuencial(FILE*arch,unsigned unLeg,Parcial &parc)
{
    int i=0;
    fread(&parc,sizeof(Parcial),1,arch);
    while(!feof(arch)&&parc.leg!=unLeg)
    {
        fread(&parc,sizeof(Parcial),1,arch);
        i++;
    }

    if(feof(arch))
        return -1;
    else
        return i;
}


//BUSQUEDA BINARIA

int busquedaBinaria(FILE*,unsigned ,Parcial &);

int busquedaBinaria(FILE*arch,unsigned unLeg,Parcial &parc)
{
    unsigned desde, hasta, medio;
    desde=0;
    fseek(arch,0,SEEK_END);
    //cantidad de registros (Parciales)=ftell(arch)/sizeof(Parcial)
    hasta=(ftell(arch)/sizeof(Parcial))-1;
    int pos=-1;
    while(pos==-1 && desde<=hasta)
    {
        medio=(hasta+desde)/2;
        fseek(arch,medio*sizeof(Parcial),SEEK_SET);
        fread(&parc,sizeof(Parcial),1,arch);
        if(parc.leg==unLeg)
            pos=medio;
        else
        {
            if(unLeg<parc.leg)
                hasta=medio-1;
            else
                desde=medio+1;
        }
    }
    return pos;
}

//ORDENAR el vector para enviar el archivo 

void ordenar(Parcial v[],unsigned );

void ordenar(Parcial v[],unsigned t)
{
    unsigned i=0,j;
    Parcial aux;
    bool cambio;
    do
    {
        cambio=false;
        for(j=0;j<t-1-i;j++)
        {
            if(v[j].dni>v[j+1].dni)
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
