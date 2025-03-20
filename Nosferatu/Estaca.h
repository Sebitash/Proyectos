#ifndef TP3_NOSFERATU_ESTACA_H
#define TP3_NOSFERATU_ESTACA_H

#include "Elemento.h"

class Estaca : public Elemento {
public:
    //constructor
    Estaca(int id, int fila, int columna);

    //PRE:
    //POST: devuelve la cantidad del item
    int devolverCantidad();

    //PRE:
    //POST:imprime por pantalla que elemento es
    void mostrar() override;
};


#endif //TP3_NOSFERATU_ESTACA_H