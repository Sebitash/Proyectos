#include "Escopeta.h"
#include "Constantes.h"
#include <iostream>

Escopeta::Escopeta(int id, int fila, int columna) : Elemento(id, fila, columna) {
    this->nombreMapa = LETRA_ESCOPETA;
}

int Escopeta::devolverCantidad() {
    return 1;
}

void Escopeta::mostrar() {
    std::cout << "\n Soy Escopeta" << endl;
}