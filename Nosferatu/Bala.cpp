#include "Bala.h"
#include <iostream>
#include "Constantes.h"

Bala::Bala(int id, int fila, int columna, int cantidad) : Elemento(id, fila, columna) {
    this->nombreMapa = LETRA_BALA;
    this->cantidad = cantidad;
};

int Bala::devolverCantidad() {
    return cantidad;
}

void Bala::mostrar() {
    std::cout << "\n Soy BALA" << std::endl;
    std::cout << "\n Cantidad: " << cantidad << std::endl;
}
