#include <iostream>
#include "Arbol.h"

Arbol::Arbol() {
    this->raiz = nullptr;
}

Nodo *Arbol::insertar(Nodo *nodo, int clave, Objeto *data, Nodo *padre) {
    if (!nodo) { //Primer nodo del arbol
        nodo = new Nodo(clave, data);
        nodo->setPadre(padre);
    } else if (clave > nodo->getClave()) {
        padre = nodo;
        nodo->setDerecho(insertar(nodo->getDerecho(), clave, data, padre)); //El segundo es el padre
    } else {
        padre = nodo;
        nodo->setIzquierdo(insertar(nodo->getIzquierdo(), clave, data,padre));
    }
    return nodo;
}

bool Arbol::insertar(int clave, Objeto *data) {
    this->raiz = insertar(this->raiz, clave, data, nullptr);
    return this->raiz != nullptr;
}

Nodo *Arbol::buscar(Nodo *nodo, int clave) {
    if (!nodo || nodo->getClave() == clave)
        return nodo;

    if (clave > nodo->getClave())
        return buscar(nodo->getDerecho(), clave);

    return buscar(nodo->getIzquierdo(), clave);
}

bool Arbol::buscar(int clave) {
    return buscar(this->raiz, clave) != nullptr;
}

int Arbol::obtenerMin(Nodo *nodo) {
    if (!nodo)
        return 0;
    else if (!nodo->getIzquierdo())
        return nodo->getClave();
    else
        return obtenerMin(nodo->getIzquierdo());
}

int Arbol::sucesor(Nodo *nodo) {
    if (nodo->getDerecho() != nullptr) {
        return obtenerMin(nodo->getDerecho());
    }

    Nodo *sucesor = nullptr;
    Nodo *ancestro = this->raiz;
    while (ancestro != nodo) {
        if (nodo->getClave() < ancestro->getClave()) {
            sucesor = ancestro;
            ancestro = ancestro->getIzquierdo();
        } else
            ancestro = ancestro->getDerecho();
    }
    return sucesor->getClave();
}

int Arbol::sucesor(int clave) {
    Nodo *nodo = this->buscar(this->raiz, clave);
    // Devuelve la clave. Si no encuentra la clave o en el sucesor, devuelve -1
    if (!nodo)
        return 0;

    return sucesor(nodo);
}

Nodo *Arbol::borrar(Nodo *nodo, int clave) {
    // El nodo no se encuentra en el ABB
    if (!nodo)
        return nullptr;
    if (nodo->getClave() == clave) {
        if (nodo->esHoja()) {
            delete nodo;
            return nullptr;
        } else if (nodo->tieneSoloHijoDerecho()) {
            nodo->getDerecho()->setPadre(nodo->getPadre());

            Nodo *aux = nodo;
            nodo = nodo->getDerecho();
            verificacionDeRaiz(aux, nodo);
            delete aux;

        } else if (nodo->tieneSoloHijoIzquierdo()) {
            nodo->getIzquierdo()->setPadre(nodo->getPadre());

            Nodo *aux = nodo;
            nodo = nodo->getIzquierdo();
            verificacionDeRaiz(aux, nodo);
            delete aux;

        } else { // El nodo tiene dos hijos (izquierdo y derecho)

            Nodo* padreActual = nodo->getPadre();
            Nodo* izquierdoActual = nodo->getIzquierdo();
            Nodo* derechoActual = nullptr;
            Nodo* sucesor = buscar(nodo,this->sucesor(clave));   //Sucesor reemplaza al nodo que actualmente está
            Nodo* padreAnterior = sucesor->getPadre();
            // Sucesor es el mas a la izquierda de los hijos de la derecha
            if (padreAnterior != nodo ) {
                padreAnterior->setIzquierdo(nullptr); //Vuelvo a setear el puntero a los hijos del padre anterior del sucesor
                derechoActual = nodo->getDerecho(); //Seteo los hijos del sucesor derecho
                derechoActual->setPadre(sucesor);
                sucesor->setDerecho(derechoActual);
            }

            // Cambio el puntero al padre y el puntero del padre al hijo
            sucesor->setPadre(padreActual);
            if (nodo != raiz) {
                if (sucesor->getClave() < padreActual->getClave()) { //Es hijo izquierdo
                    padreActual->setIzquierdo(sucesor);
                } else {
                    padreActual->setDerecho(sucesor);
                }
            }

            //Seteo los hijos del sucesor izquierdo: tanto en el sucesor como el puntero a los padres de ambos hijos
            sucesor->setIzquierdo(izquierdoActual);
            izquierdoActual->setPadre(sucesor);

            verificacionDeRaiz(nodo,sucesor);
            delete nodo;
            return sucesor;
        }
    } else if (nodo->getClave() < clave){
        nodo->setDerecho(borrar(nodo->getDerecho(), clave));
    } else {
        nodo->setIzquierdo(borrar(nodo->getIzquierdo(), clave));
    }
    return nodo;
}

void Arbol::borrar(int clave) {
    this->raiz = borrar(this->raiz, clave);
    this->raiz->getData();
}

void Arbol::borrarTodo(Nodo *nodo) {
    if (!nodo)
        return;

    borrarTodo(nodo->getIzquierdo());
    borrarTodo(nodo->getDerecho());

    delete nodo;
}

void Arbol::verificacionDeRaiz(Nodo *&nodoBorrar, Nodo* nodoActual) {
    if (raiz == nodoBorrar){
        raiz = nodoActual;
    }
}

Objeto *Arbol::getDato(int clave) {
    Nodo *nodo = buscar(this->raiz, clave);
    if (!nodo)
        return nullptr;

    return nodo->getData();
}

void Arbol::eliminarTodo() {
    this->borrarTodo(this->raiz);
}

Arbol::~Arbol() {
    this->eliminarTodo();
}
