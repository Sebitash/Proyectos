#include "Casillero.h"
#include "Objeto.h"
#include "Agua.h"
#include "Cruz.h"
#include "Bala.h"
#include "Escopeta.h"
#include "Estaca.h"
#include "Humano.h"
#include "Cazador.h"
#include "Vanesa.h"
#include "Zombi.h"
#include "Vampiro.h"
#include "Nosferatu.h"
#include "Vampirella.h"
#include "Constantes.h"

static const char *const TERMINAR_COLOR = "\033[0m";

Casillero::Casillero(int fila, int columna) {
    objetoSer = nullptr;
    objetoItem = nullptr;
    this->fila = fila;
    this->columna = columna;
}

void Casillero::mostrar(int &y, int &x) {
    Gotoxy gotox;
    if (tieneSer()) {
        cout << gotox.pos(y, x) << devolverColor() << "  " << TXT_BLACK_16 << devolverSer()->obtenerNombreMapa()
             << "  " << TERMINAR_COLOR;
    } else if (tieneItem()) {
        cout << gotox.pos(y, x) << devolverColor() << "  " << TXT_BLACK_16 << devolverItem()->obtenerNombreMapa()
             << "  " << TERMINAR_COLOR;
    } else {
        cout << gotox.pos(y, x) << devolverColor() << "     " << TERMINAR_COLOR;
    }
}

string Casillero::devolverColor() {
    return color;
}

Objeto *Casillero::devolverSer() {
    return objetoSer;
}

Objeto *Casillero::devolverItem() {
    return objetoItem;
}


bool Casillero::tieneSer() {
    return (objetoSer);
}

bool Casillero::tieneItem() {
    return (objetoItem);
}

void Casillero::eliminarObjeto() {
    delete objetoSer;
    objetoSer = nullptr;
}

void Casillero::liberarPunteroSer() {
    objetoSer = nullptr;
}

void Casillero::eliminarItem() {
    delete objetoItem;
    objetoItem = nullptr;
}

void Casillero::agregarSer(Ser *personaje) {
    this->objetoSer = personaje;
}

void Casillero::crearObjeto(const string &nombre, int id, int cantidadEnCasilla) {
    if (nombre == NOMBRE_AGUA) {
        objetoItem = new Agua(id, fila, columna, cantidadEnCasilla);
    } else if (nombre == NOMBRE_CRUZ) {
        objetoItem = new Cruz(id, fila, columna);
    } else if (nombre == NOMBRE_BALA) {
        objetoItem = new Bala(id, fila, columna, cantidadEnCasilla);
    } else if (nombre == NOMBRE_ESCOPETA) {
        objetoItem = new Escopeta(id, fila, columna);
    } else if (nombre == NOMBRE_ESTACA) {
        objetoItem = new Estaca(id, fila, columna);
    } else if (nombre == NOMBRE_HUMANO) {
        objetoSer = new Humano(id, fila, columna);
    } else if (nombre == NOMBRE_CAZADOR) {
        objetoSer = new Cazador(id, fila, columna);
    } else if (nombre == NOMBRE_VANESA) {
        objetoSer = new Vanesa(id, fila, columna);
    } else if (nombre == NOMBRE_ZOMBI) {
        objetoSer = new Zombi(id, fila, columna);
    } else if (nombre == NOMBRE_VAMPIRO) {
        objetoSer = new Vampiro(id, fila, columna);
    } else if (nombre == NOMBRE_NOSFERATU) {
        objetoSer = new Nosferatu(id, fila, columna);
    } else if (nombre == NOMBRE_VAMPIRELLA) {
        objetoSer = new Vampirella(id, fila, columna);
    } else {
        objetoSer = nullptr;
        objetoItem = nullptr;
    }
}

int Casillero::obtenerCosto(char personaje) {
    int costo;
    if (personaje == LETRA_HUMANO) {
        costo = costoHumano;
    } else if (personaje == LETRA_CV) {
        costo = costoCazador;
    } else if (personaje == LETRA_VANESA) {
        costo = costoVanesa;
    } else if (personaje == LETRA_ZOMBI) {
        costo = costoZombi;
    } else if (personaje == LETRA_VAMPIRO) {
        costo = costoVampiro;
    } else if (personaje == LETRA_NOSFERATU) {
        costo = costoNosferatu;
    } else if (personaje == LETRA_VAMPIRELLA) {
        costo = costoVampirella;
    }

    return costo;
}

Casillero::~Casillero() {
    delete objetoSer;
    delete objetoItem;
}
