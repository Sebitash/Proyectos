#include "Inventario.h"
#include <iostream>

const int CANTIDAD_MINIMA_BALAS = 2;

Inventario::Inventario() {
    this->cruz = 0;
    this->aguaBendita = 0;
    this->bala = 0;
    this->escopeta = false;
    this->estaca = 0;
}

void Inventario::setCruz(unsigned int cantidad) {
    this->cruz = cantidad;
}

unsigned int Inventario::getCruz() {
    return cruz;
}

void Inventario::setAguaBendita(unsigned int cantidadAgua) {
    aguaBendita = cantidadAgua;
}

unsigned int Inventario::getAguaBendita() {
    return aguaBendita;
}

void Inventario::setBala(unsigned int cantidadBalas) {
    bala = cantidadBalas;
}

unsigned int Inventario::getBala() {
    return bala;
}

void Inventario::setEstaca(unsigned int cantidad) {
    this->estaca = (this->estaca + cantidad);
}

unsigned int Inventario::getEstaca() {
    return estaca;
}

void Inventario::setEscopeta() {
    escopeta = true;
}

bool Inventario::getEscopeta() {
    return escopeta;
}

bool Inventario::inventarioVacio() {
    return (!(escopeta || estaca > 0 || cruz > 0 || aguaBendita > 0 || bala > 0));
}

void Inventario::aumentarElemento(int cantidad, char elemento) {
    if (Elemento::esEstaca(elemento)) {
        this->estaca++;

    } else if (Elemento::esBala(elemento)) {
        this->bala += cantidad;

    } else if (Elemento::esCruz(elemento)) {
        this->cruz++;

    } else if (Elemento::esAguaBendita(elemento)) {
        this->aguaBendita += cantidad;
    }
}

void Inventario::disminuirElemento(ITEM_ELEGIDO elemento) {
    if (elemento == ITEM_ESTACA) {
        this->estaca--;
    } else if (elemento == ITEM_BALA) {
        this->bala -= CANTIDAD_MINIMA_BALAS; //disminuye siempre dos ya que para usar la escopeta se utilizan dos balas
    } else if (elemento == ITEM_CRUZ) {
        this->cruz--;
    } else if (elemento == ITEM_AGUA_BENDITA) {
        this->aguaBendita--;
    }

}

bool Inventario::tieneAguaBendita() {
    return (getAguaBendita());
}

bool Inventario::tieneEscopeta() {
    return (getEscopeta());
}

bool Inventario::tieneBalasSuficientes() {
    return (getBala() >= Escopeta::cantidadMinimaBalas);
}

bool Inventario::tieneEstaca() {
    return (getEstaca());
}

bool Inventario::tieneCruz() {
    return (getCruz());
}

Inventario::~Inventario() {}
