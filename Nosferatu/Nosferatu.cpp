#include "Nosferatu.h"
#include "Constantes.h"

Nosferatu::Nosferatu(int id, int fila, int columna) : Vampiro(id, fila, columna) {
    nombreMapa = LETRA_NOSFERATU;
    this->humanoMordido = false;
    this->recargaEnergiaTurno = 10;
    this->energiaMinimaAtaque = 6;
    this->energiaMinimaDefensa = 10;
}

void Nosferatu::elegirDefensa() {
    defensaElegida = DEFENSA_NOSFERATU;
    cout << endl << "Nosferatu intercambiará vida con otro vampiro que se encuentre cerca." << endl;
    cout << endl << "Obvio, siempre y cuando le convenga.." << endl;
}

void Nosferatu::mostrar() {
    std::cout << "Soy Nosferatu" << endl;
    mostrarAtributos();
}
