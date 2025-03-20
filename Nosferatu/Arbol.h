#ifndef TP3_NOSFERATU_ARBOL_H
#define TP3_NOSFERATU_ARBOL_H


#include "Nodo.h"

class Arbol {
private:
    // Atributos
    Nodo *raiz;

    // Metodos

    // PRE:
    // POST:Agrega un nuevo nodo al ABB actual. Si el ABB estaVacio
    // el nodo insertado será la raíz.
    Nodo *insertar(Nodo *nodo, int clave, Objeto *data, Nodo* padre);

    // PRE:Busca una clave dada en el ABB recursivamente
    // POST:devuelve el nodo
    Nodo *buscar(Nodo *nodo, int clave);

    // PRE:
    // POST:Busca el valor minimo de clave existente en el ABB.
    int obtenerMin(Nodo *nodo);

    // PRE:
    // POST:Encuentra el sucesor de una clave dada.
    int sucesor(Nodo *nodo);

    // PRE:
    // POST:Remueve la data correspondiente a una clave del ABB.
    Nodo *borrar(Nodo *nodo, int clave);

    // PRE:
    // POST:Borra todos los nodos del ABB.
    void borrarTodo(Nodo *nodo);

    void verificacionDeRaiz(Nodo* &nodoBorrar, Nodo* nodoActual);

public:

    Arbol();

    // PRE:
    // POST:Agrega un nuevo nodo al ABB actual. Si el ABB estaVacio
    // el nodo insertado será la raíz.
    bool insertar(int clave, Objeto *data);


    // PRE:Busca una clave dada en el ABB.
    // POST:Si la clave existe devuelve TRUE.
    bool buscar(int clave);

    // PRE:
    // POST:Busca la clave dada en el ABB y devuelve el dato.
    Objeto *getDato(int clave);

    // PRE:
    // POST:Encuentra el sucesor de una clave dada.
    int sucesor(int clave);

    // PRE:
    // POST:Remueve la data correspondiente a una clave del ABB.
    void borrar(int clave);

    // PRE:
    // POST:Borra todos los nodos del ABB.
    void eliminarTodo();

    //destructor
    ~Arbol();

};


#endif //TP3_NOSFERATU_ARBOL_H
