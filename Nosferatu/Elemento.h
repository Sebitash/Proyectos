#ifndef TP3_NOSFERATU_ELEMENTO_H
#define TP3_NOSFERATU_ELEMENTO_H

#include "Objeto.h"

class Elemento : public Objeto {
private:
    //atributos
    static int cantidadElementos;
public:
    //constructor
    Elemento(int id, int fila, int columna);

    //PRE:
    //POST:devuelve la cantidad de elemento que hay en el mapa
    static int devolverCantidadElementos();

    //PRE:
    //POST: devuelve la cantidad del item
    virtual int devolverCantidad() = 0;

    //PRE:
    //POST: devuelve true si el caracter pasado por parametro es de un item
    static bool esItem(char nombreMapa);

    //PRE:
    //POST: devuelve true si el caracter pasado por parametro es de una agua bendita
    static bool esAguaBendita(char nombreMapa);

    //PRE:
    //POST: devuelve true si el caracter pasado por parametro es de una bala
    static bool esBala(char nombreMapa);

    //PRE:
    //POST: devuelve true si el caracter pasado por parametro es de una cruz
    static bool esCruz(char nombreMapa);

    //PRE:
    //POST: devuelve true si el caracter pasado por parametro es de una escopeta
    static bool esEscopeta(char nombreMapa);

    //PRE:
    //POST: devuelve true si el caracter pasado por parametro es de una estaca
    static bool esEstaca(char nombreMapa);

    //destructor
    ~Elemento();
};

#endif //TP3_NOSFERATU_ELEMENTO_H
