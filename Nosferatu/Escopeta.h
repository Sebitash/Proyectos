#ifndef TP3_NOSFERATU_ESCOPETA_H
#define TP3_NOSFERATU_ESCOPETA_H

#include "Elemento.h"

class Escopeta : public Elemento {
public:
    // Al ser una constante estatica tiene que ser publica
    static const int cantidadMinimaBalas = 2;

    //constructor
    Escopeta(int id, int fila, int columna);

    //PRE:
    //POST: devuelve la cantidad del item
    int devolverCantidad();

    //PRE:
    //POST:muestra por pantalla que elemento es
    void mostrar() override;
};


#endif //TP3_NOSFERATU_ESCOPETA_H

