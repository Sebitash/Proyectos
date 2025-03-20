#include "Objeto.h"

Objeto::Objeto() {}

Objeto::Objeto(int id, int fila, int columna) {
    this->id = id;
    this->fila = fila;
    this->columna = columna;
}

int Objeto::obtenerFila() {
    return fila;
}

int Objeto::obtenerColumna() {
    return columna;
}

int Objeto::obtenerID(){
	return id;
}

char Objeto::obtenerNombreMapa() {
    return nombreMapa;
}

void Objeto::setNombreMapa(char nombre) {
    this->nombreMapa = nombre;
}

void Objeto::setFila(int fila) {
    this->fila = fila;
}

void Objeto::setColumna(int columna) {
    this->columna = columna;
}

Objeto::~Objeto() {

}
