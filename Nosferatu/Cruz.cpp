#include "Cruz.h"
#include "Constantes.h"
#include <iostream>

Cruz::Cruz(int id, int fila, int columna) : Elemento(id, fila, columna) {
    this->nombreMapa = LETRA_CRUZ;
}

int Cruz::devolverCantidad() {
    return 1;
}

void Cruz::mostrar() {
    std::cout << "\nSoy Cruz" << std::endl;
}