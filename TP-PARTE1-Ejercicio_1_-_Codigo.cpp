#include <iostream>
#include <stdio.h>

using namespace std;

struct Repartidor
{
	int dni;
	char nom[25];
	int zona;	
};

int main() 
{
	Repartidor rep;
	int cant[6]={0}; //Inicializaron el vector
	int i=0;
	
	FILE*arch = fopen("Repartidores.dat","wb");
	if(arch==NULL)
		cout<<"ERROR"<<endl;
	else
	{
		cout<<"Ingrese dni del repartidor (Ingrese 0 para finalizar el programa):"<<endl;
        cin>>rep.dni;
        
        while(rep.dni!=0)
        {
            cout<<"Ingrese el nombre del repartidor:"<<endl;
            cin>>rep.nom;
            
            cout<<"Ingrese la zona en la que trabaja (1-6): "<<endl;
			cin>>rep.zona;
			while((rep.zona<1)||(rep.zona>6))
			{
				cout<<rep.zona<<" no es una zona valida."<<endl<<"Ingrese una zona entre 1 y 6:"<<endl;
				cin>>rep.zona;
			}
			
			cant[rep.zona-1]++;
			
            fwrite(&rep,sizeof(Repartidor),1,arch);
            
            cout<<"Ingrese dni del repartidor (Ingrese 0 para finalizar el programa):"<<endl;
            cin>>rep.dni;
        }
        fclose(arch);
	}
	
	for(i=0;i<6;i++)
	{
		if(cant[i]!=0)
			cout<<"Hay "<<cant[i]<<" repartidores en la zona "<<i+1<<"."<<endl;
		else
			cout<<"No hay ningun repartidor en la zona "<<i+1<<"."<<endl;
	}
	
	return 0;
	
}
