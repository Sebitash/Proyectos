//
// Created by daniela on 12/7/21.
//

#ifndef TP3_NOSFERATU_NODO_H
#define TP3_NOSFERATU_NODO_H

#include "Objeto.h"

class Nodo {
private:
    //atributos
    int clave;
    Objeto *data;
    Nodo *izquierdo; //Hijo izquierdo.
    Nodo *derecho; //Hijo derecho.
    Nodo *padre;

public:
    //constructor
    Nodo(int clave, Objeto *data);

    //PRE:
    //POST: devuelve el valor del nodo
    Objeto *getData();

    //PRE:
    //POST:Setea el puntero objeto de un nodo
    void setData(Objeto* data);

    //PRE:
    //POST:devuelve la clave del nodo
    int getClave();

    //PRE:
    //POST: setea la clave del nodo
    void setClave(int nuevaClave);

    //PRE: recibe el nodo derecho y el nodo padre
    //POST: setea su hijo derecho
    void setDerecho(Nodo *derecho, Nodo *padre);

    //PRE: recibe el nodo izquierdo y el nodo padre
    //POST: setea su hijo izquierdo
    void setIzquierdo(Nodo *izquierdo, Nodo *padre);

    //PRE: recibe el nodo izquierdo
    //POST: setea su hijo izquierdo
    void setIzquierdo(Nodo *izquierdo);

    //PRE: recibe el nodo derecho
    //POST: setea su hijo derecho
    void setDerecho(Nodo *derecho);

    //PRE:
    //POST:setea al nodo padre
    void setPadre(Nodo *padre);

    //PRE:
    //POST:devuelve su hijo derecho
    Nodo *getDerecho();

    //PRE:
    //POST:devuelve su hijo izquierdo
    Nodo *getIzquierdo();

    //PRE:
    //POST:devuelve a su padre
    Nodo *getPadre();

    //PRE:
    //POST:devuelve true si es hoja
    bool esHoja();

    //PRE:
    //POST:devuelve true tiene solo hijo derecho
    bool tieneSoloHijoDerecho();

    //PRE:
    //POST:devuelve true tiene solo hijo izquierdo
    bool tieneSoloHijoIzquierdo();

    //destructor
    virtual ~Nodo();

};

#endif //TP3_NOSFERATU_NODO_H
