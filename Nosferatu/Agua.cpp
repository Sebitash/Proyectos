#include "Agua.h"
#include "Constantes.h"
#include <iostream>


Agua::Agua(int id, int fila, int columna, int cantidad) : Elemento(id, fila, columna) {
    this->nombreMapa = LETRA_AGUA;
    this->cantidad = cantidad;
};

int Agua::devolverCantidad() {
    return cantidad;
}

void Agua::mostrar() {
    std::cout << "\n Soy AGUA" << std::endl;
    std::cout << "\n Cantidad: " << cantidad << std::endl;
}