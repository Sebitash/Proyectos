#include "Estaca.h"
#include "Constantes.h"
#include <iostream>

Estaca::Estaca(int id, int fila, int columna) : Elemento(id, fila, columna) {
    this->nombreMapa = LETRA_ESTACA;
}

int Estaca::devolverCantidad() {
    return 1;
}

void Estaca::mostrar() {
    std::cout << "\n Soy Estaca" << std::endl;
}
