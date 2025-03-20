#ifndef TP3_NOSFERATU_CRUZ_H
#define TP3_NOSFERATU_CRUZ_H

#include "Elemento.h"

class Cruz : public Elemento {
public:
    //constructor
    Cruz(int id, int fila, int columna);

    //PRE:
    //POST: devuelve la cantidad del item
    int devolverCantidad();

    //PRE:
    //POST: imprime por pantalla que elemento es
    void mostrar();
};

#endif //TP3_NOSFERATU_CRUZ_H
