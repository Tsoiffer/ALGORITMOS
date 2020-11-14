//hago una pruba
#include <iostream>
#include <stdio.h>
using namespace std;
//1234
struct DatoArchPlato
{
    int codPlato; 
	char descripcion[41];
	float precio;
};
struct Fecha
{
    int dia;
    int mes;
    int anio;
};
struct DatoArchFac
{
    Fecha fecha;
    int nroFactura;
    int  mesa;
    int mozo;
    float importe;
};
struct DatoLista
{
    int codPlato;
    int cant;
};
struct Nodo
{
    DatoLista info;
    Nodo* sig;
};

void inicPunt(Nodo* v[48]);
void inicFloat(float v[10]);
void ingresarFecha(Fecha);
void procesar(FILE*,Nodo* v[48],float m[10],Fecha,int &);
bool hayAdicPendientes(Nodo* v[48]);
void mostrarComMozos(float v[10]);
Nodo* buscar (Nodo* &, int);
Nodo* buscarInsertar(Nodo* & ,DatoLista );
int mostrarFact (Fecha, int , int, FILE*, Nodo*, int);
int main()
{
    FILE*arch=fopen("Platos.dat","rb");
    if(arch!=NULL)
    {
        float comMozos[10];
        Nodo*mesas[48];
        inicPunt(mesas); //en NULL
        inicFloat(comMozos); //en 0
        Fecha fecha;
        ingresarFecha(fecha);
        int nroFac;
        cout<<"nro fac inicial "<<endl;
        cin>>nroFac;
        procesar(arch,mesas,comMozos,fecha,nroFac);
        cout<<"nuevo nro de fac inicial "<<nroFac<<endl;
        if(hayAdicPendientes(mesas))
            cout<<"hay adiciones pendientes"<<endl;
        mostrarComMozos(comMozos); //muestra la comisi�n a cobrar por cada mozo
        fclose(arch);
    }
    return 0;
}

void inicPunt(Nodo* mesas[])
{
 for(int i=0;i<48;i++)
 {
     mesas[i]=NULL;
 }
}
void inicFloat(float mozos[])
{
    for (int i = 0; i < 10; i++)
    {
        mozos[i]=0;
    }
}
void ingresarFecha(Fecha fecha)
{
    cout<<"Ingrese numero de dia"<<endl;
    cin>>fecha.dia;
    cout<<"ingrese el numero del mes"<<endl;
    cin>>fecha.mes;
    cout<<"ingese el año"<<endl;
    cin>>fecha.anio;
}
void procesar(FILE*aPlatos,Nodo*mesas[],float comMozos[],Fecha fecha,int & nroFac)
{
    int nroMesa, codigo, cantPedi;
	char codOp;
	Nodo*p;
	DatoLista dl;
	cout<<"nro mesa ";
	cin>>nroMesa;
	while(nroMesa!=0)
    {
        cout<<"cod operacion ";
        cin>>codOp;
        switch(codOp)
        {
            case 'A':
                cout<<"Codigo plato a entregar ";
                cin>>codigo;
                cout<<"cantidad a entregar ";
                cin>>cantPedi;
                dl.codPlato = codigo;
                dl.cant=0;
                p=buscarInsertar(mesas[nroMesa-1],dl);
                p->info.cant+=cantPedi;
                break;
            case 'B':
                cout<<"Codigo plato a devolver ";
                cin>>codigo;
                cout<<"cantidad a devolver ";
                cin>>cantPedi;
                p=buscar(mesas[nroMesa-1],codigo);
                if(p!=NULL && p->info.cant>=cantPedi)
                    p->info.cant-=cantPedi;
            break;
            case 'F':
                cout<<"nro de mozo ";
                cin>>codigo;
                int impFac=mostrarFact(fecha,nroFac,codigo,aPlatos,mesas[nroMesa-1],nroMesa);
                comMozos[codigo-1]+=impFac*0.01;
                nroFac++;
            break;
        }
        cout<<"nro mesa ";
        cin>>nroMesa;
    }
}
Nodo* buscar(Nodo* & mesa ,int codigo)
{   
    Nodo* r=mesa;
    while(r!=NULL && r->info.codPlato != codigo)
    {
        r=r->sig;
    }
        return r;
}
Nodo* buscarInsertar(Nodo* & mesa,DatoLista dl)
{ 
    Nodo*ant,*r=mesa;
    while(r!=NULL && r->info.codPlato != dl.codPlato)
    {
        ant=r;
        r=r->sig;
    }

    if(r==NULL)
    {
        Nodo*p=new Nodo;
        p->info=dl;
        p->sig=r;
        if(r!=mesa)
            ant->sig=p;
        else
            mesa=p;
        return p;
    }
    else
        return r;
}
int mostrarFact(Fecha f,int nroFac,int mozo,FILE*aPlatos,Nodo*lista, int norM)
{
    cout<<"Fecha"<<f.dia<<f.mes<<f.anio<<" Nro Factura "<<nroFac<<endl;
    cout<<"Cant      Descripcion            Precio Unitario          Importe"<<endl;
    Nodo*aux;
    float imp,impTotal=0;
    DatoArchPlato plato;
    DatoArchFac fac;
    FILE*aFac=fopen("Facturacion.dat","ab");
    while(lista!=NULL)
    {
        if(lista->info.cant>0)
        {
            fseek(aPlatos,(lista->info.codPlato-1)*sizeof(DatoArchPlato),SEEK_SET);
            fread(&plato,sizeof(DatoArchPlato),1,aPlatos);
            imp=lista->info.cant*plato.precio;
            cout<<lista->info.cant<<plato.descripcion<<plato.precio<<imp<<endl;
            impTotal+=imp;
        }
        aux=lista;
        lista=lista->sig;
        delete aux;
    }

    cout<<"mozo "<<mozo<<" total "<<impTotal<<endl;
    fac.fecha=f;
    fac.importe=impTotal;
    fac.mesa=norM;
    fac.nroFactura=nroFac;
    fac.mozo=mozo;
    fwrite(&fac,sizeof(DatoArchFac),1,aFac);
    fclose(aFac);
    return impTotal;
}
void mostrarComMozos(float comMozos[10])
{

for (int i=0; i<10; i++)
  cout<<"la comision del mozo es: "<<comMozos[i]<<endl;
      
}
bool hayAdicPendientes(Nodo* v[])
{
    int i=0;
    while(i<48 && v[i]==NULL)
        i++;
    if(i<48)
        return true;
    else
        return false;
}
