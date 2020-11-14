struct Nodo
{
    int dato;
    Nodo*sig;
};

void ReemplazarValorPila(Nodo *&pila, int valx, int valy)
{
    Nodo *pilaAux=NULL;
    int nro;
    while(pila!=NULL)
    {
        desapilar(pila,nro);
        if(nro==valy)
            apilar(pilaAux,valx);
        else
            apilar(pilaAux,nro);
    }
    while(pilaAux!=NULL)
    {
        desapilar(pilaAux,nro);
        apilar(pila,nro);
    }
}
