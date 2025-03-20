#include "Elemento.h"
#include "Constantes.h"

int Elemento::cantidadElementos = 0;

Elemento::Elemento(int id, int fila, int columna) : Objeto(id, fila, columna) {
    cantidadElementos++;
};

int Elemento::devolverCantidadElementos() {
    return cantidadElementos;
}

bool Elemento::esItem(char nombreMapa) {
    return (nombreMapa == LETRA_AGUA || nombreMapa == LETRA_BALA || nombreMapa == LETRA_CRUZ ||
            nombreMapa == LETRA_ESTACA || nombreMapa == LETRA_ESCOPETA);
}

bool Elemento::esAguaBendita(char nombreMapa) {
    return (nombreMapa == LETRA_AGUA);
}

bool Elemento::esBala(char nombreMapa) {
    return (nombreMapa == LETRA_BALA);
}

bool Elemento::esCruz(char nombreMapa) {
    return (nombreMapa == LETRA_CRUZ);
}

bool Elemento::esEscopeta(char nombreMapa) {
    return (nombreMapa == LETRA_ESCOPETA);
}

bool Elemento::esEstaca(char nombreMapa) {
    return (nombreMapa == LETRA_ESTACA);
}

Elemento::~Elemento() {
    cantidadElementos--;
}