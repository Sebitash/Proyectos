#include "Coordenadas.h"
#include <iostream>
using namespace std;

Coordenadas::Coordenadas() {
    fila = 0;
    columna = 0;
    cantCasillerosVisitados = 0;
}

Coordenadas::Coordenadas(int f, int c, int cant) {
    fila = f;
    columna = c;
    cantCasillerosVisitados = cant;
}

int Coordenadas::getFila() {
    return fila;
}

int Coordenadas::getColumna() {
    return columna;
}

int Coordenadas::getCantidadCasillerosVisitados() {
    return cantCasillerosVisitados;
}

void Coordenadas::setFila(int f) {
    fila = f;
}

void Coordenadas::setColumna(int c) {
    columna = c;
}

void Coordenadas::incrementarCasillerosVisitados(int cantidadVisitadaActual) {
    cantCasillerosVisitados = cantidadVisitadaActual + 1;
}

void Coordenadas::setCoordenadas(int f, int c) {
    setFila(f);
    setColumna(c);
}

void Coordenadas::mostrarCoordenadas() {
    cout << "[" << fila << "," << columna << "] ";
}
