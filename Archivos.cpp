//Funciones de Archivos
#include <iostream>
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
