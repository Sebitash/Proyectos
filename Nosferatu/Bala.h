#ifndef TP3_NOSFERATU_BALA_H
#define TP3_NOSFERATU_BALA_H

#include "Elemento.h"


class Bala : public Elemento {
private:
    //ATRIBUTOS
    int cantidad;
public:
    //CONSTRUCTOR
    Bala(int id, int fila, int columna, int cantidad);

    //PRE:
    //POST: devuelve la cantidad del item
    int devolverCantidad();

    //PRE
    //POST: imprime por pantalla un mensaje de que elemento es y su cantidad
    void mostrar();
};


#endif //TP3_NOSFERATU_BALA_H
