#include <iostream>
#include "Nodo.h"

Nodo::Nodo(int clave, Objeto *data) {
    this->clave = clave;
    this->data = data;
    this->izquierdo = nullptr;
    this->derecho = nullptr;
    this->padre = nullptr;
}

Objeto *Nodo::getData() {
    return this->data;
}

void Nodo::setData(Objeto *data) {
    this->data = data;
}

int Nodo::getClave() {
    return this->clave;
}

void Nodo::setClave(int nuevaClave) {
    this->clave = nuevaClave;
}

void Nodo::setDerecho(Nodo *derecho, Nodo *padre) {
    this->derecho = derecho;
    this->padre = padre;
}

void Nodo::setIzquierdo(Nodo *izquierdo, Nodo *padre) {
    this->izquierdo = izquierdo;
    this->padre = padre;
}

void Nodo::setIzquierdo(Nodo *izquierdo) {
    this->izquierdo = izquierdo;
}

void Nodo::setDerecho(Nodo *derecho) {
    this->derecho = derecho;
}

void Nodo::setPadre(Nodo *padre) {
    this->padre = padre;
}

Nodo *Nodo::getDerecho() {
    return this->derecho;
}

Nodo *Nodo::getIzquierdo() {
    return this->izquierdo;
}

Nodo *Nodo::getPadre() {
    return this->padre;
}

bool Nodo::esHoja() {
    return (!this->getIzquierdo() && !this->getDerecho());
}

bool Nodo::tieneSoloHijoDerecho() {
    return (!this->getIzquierdo() && this->getDerecho() != nullptr);
}

bool Nodo::tieneSoloHijoIzquierdo() {
    return (this->getIzquierdo() != nullptr && !this->getDerecho());
}

Nodo::~Nodo() {
    data = nullptr;
}
