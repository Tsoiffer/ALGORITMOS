#include <iostream>
#include <stdio.h>


using namespace std;

struct Parcial
{
    unsigned leg;
    char nom[21];
    unsigned nota;
};

int busquedaSecuencial(FILE* arch,unsigned bus,Parcial &par);
int busquedaBinaria(FILE* arch,unsigned bus,Parcial &par);

int main()
{
    /*
    FILE *archivo=fopen("Notas.dat","rb");
    if(archivo!=NULL)
    {
        unsigned unLeg;
        Parcial parcial;
        cout<<"Consulta en archivo secuencial"<<endl;
        cout<<"legajo a buscar ";
        cin>>unLeg;
        int pos=busquedaSecuencial(archivo,unLeg,parcial);
        if(pos==-1)
            cout<<"No esta"<<endl;
        else
            cout<<parcial.nom<<parcial.nota<<endl;
        fclose(archivo);
    }
    */
    /*
    FILE *archivo=fopen("Notas.dat","r+b");
    if(archivo!=NULL)
    {
        unsigned unLeg,nuevaNota;
        Parcial parcial;
        cout<<"Modificacion en archivo secuencial"<<endl;
        cout<<"legajo a buscar ";
        cin>>unLeg;
        cout<<"nueva nota ";
        cin>>nuevaNota;
        int pos=busquedaSecuencial(archivo,unLeg,parcial);
        if(pos==-1)
            cout<<"No esta"<<endl;
        else
        {
            parcial.nota=nuevaNota;
            fseek(archivo,pos*sizeof(Parcial),SEEK_SET);
            fwrite(&parcial,sizeof(Parcial),1,archivo);
        }
        fclose(archivo);
    }
    */
    /*
    FILE *archivo=fopen("NotasOrd.dat","rb");
    if(archivo!=NULL)
    {
        unsigned unLeg;
        Parcial parcial;
        cout<<"Consulta en archivo ordenado"<<endl;
        cout<<"legajo a buscar ";
        cin>>unLeg;
        int pos=busquedaBinaria(archivo,unLeg,parcial);
        if(pos==-1)
            cout<<"No esta"<<endl;
        else
            cout<<parcial.nom<<parcial.nota<<endl;
        fclose(archivo);
    }
    */
    /*
    FILE *archivo=fopen("NotasOrd.dat","r+b");
    if(archivo!=NULL)
    {
        unsigned unLeg,nuevaNota;
        Parcial parcial;
        cout<<"Modificacion en archivo ordenado"<<endl;
        cout<<"legajo a buscar ";
        cin>>unLeg;
        cout<<"nueva nota ";
        cin>>nuevaNota;
        int pos=busquedaBinaria(archivo,unLeg,parcial);
        if(pos==-1)
            cout<<"No esta"<<endl;
        else
        {
            parcial.nota=nuevaNota;
            fseek(archivo,pos*sizeof(Parcial),SEEK_SET);
            fwrite(&parcial,sizeof(Parcial),1,archivo);
        }
        fclose(archivo);
    }
    */
    /*
    FILE *archivo=fopen("NotasAccD.dat","rb");
    if(archivo!=NULL)
    {
        unsigned unLeg;
        Parcial parcial;
        cout<<"Consulta en archivo de acceso directo"<<endl;
        cout<<"legajo a buscar ";
        cin>>unLeg;
        //fseek(archivo,(unLeg-1)*sizeof(Parcial),SEEK_SET);
        //fread(&parcial,sizeof(Parcial),1,archivo);
        //cout<<parcial.nom<<parcial.nota<<endl;
        fseek(archivo,(unLeg-1)*sizeof(Parcial),SEEK_SET);
        if(fread(&parcial,sizeof(Parcial),1,archivo)==0)
            cout<<"No esta"<<endl;
        else
            cout<<parcial.nom<<parcial.nota<<endl;
        fclose(archivo);
    }
    */

    FILE *archivo=fopen("NotasAccD.dat","r+b");
    if(archivo!=NULL)
    {
        unsigned unLeg,nuevaNota;
        Parcial parcial;
        cout<<"Modificacion en archivo con acceso directo"<<endl;
        cout<<"legajo a buscar ";
        cin>>unLeg;
        cout<<"nueva nota ";
        cin>>nuevaNota;
        fseek(archivo,(unLeg-1)*sizeof(Parcial),SEEK_SET);
        if(fread(&parcial,sizeof(Parcial),1,archivo)==0)
            cout<<"No esta"<<endl;
        else
        {
            parcial.nota=nuevaNota;
            fseek(archivo,(unLeg-1)*sizeof(Parcial),SEEK_SET);
            fwrite(&parcial,sizeof(Parcial),1,archivo);
        }
        fclose(archivo);
    }

    return 0;
}

int busquedaSecuencial(FILE* arch,unsigned bus,Parcial &par)
{
    unsigned i=0;
    fread(&par,sizeof(Parcial),1,arch);
    while(!feof(arch)&&par.leg!=bus)
    {
        fread(&par,sizeof(Parcial),1,arch);
        i++;
    }
    if(feof(arch))
        return -1;
    else
        return i;
}

int busquedaBinaria(FILE* arch,unsigned bus,Parcial &par)
{
    unsigned desde,hasta,medio,cantRegistros;
    int pos=-1;
    desde=0;
    fseek(arch,0,SEEK_END);
    cantRegistros=ftell(arch)/sizeof(Parcial);
    hasta=cantRegistros-1;
    //hasta=ftell(arch)/sizeof(Parcial)-1;
    while(pos==-1 && desde<=hasta)
    {
        medio=(desde+hasta)/2;
        fseek(arch,medio*sizeof(Parcial),SEEK_SET);
        fread(&par,sizeof(Parcial),1,arch);
        if(par.leg==bus)
            pos=medio;
        else
        {
            if(bus<par.leg)
                hasta=medio-1;
            else
                desde=medio+1;
        }
    }
    return pos;
}
