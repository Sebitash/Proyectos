#include "Jugador.h"
#include "Constantes.h"


Jugador::Jugador() {}

Jugador::Jugador(Tablero* tablero, Arbol* arbol) {
    this->tablero = tablero;
    this->arbol = arbol;
    bando = " ";
}

Jugador::Jugador(const Jugador &jugadorACopiar){
    bando = jugadorACopiar.bando;
    numeroJugador = jugadorACopiar.numeroJugador;
}

int Jugador::getCantidadPersonajes() {
    return this->cantidadPersonajes;
}

bool Jugador::jugadorMuerto() {
    return (!cantidadPersonajes);
}

void Jugador::setBando(string bando) {
    this->bando = bando;
}

string Jugador::getBando() {
    return (this->bando);
}

void Jugador::setCantidadPersonajes(int cantidad) {
    this->cantidadPersonajes = cantidad;
}

void Jugador::setPersonaje(int idPersonajeNuevo) {
    vectorIDsPersonajes[contadorPersonajesIngresados] = idPersonajeNuevo;
    contadorPersonajesIngresados++;
}

void Jugador::setVectorIDs() {
    vectorIDsPersonajes = new int[cantidadPersonajes];
    contadorPersonajesIngresados = 0;
}

void Jugador::agregarPersonajeVectorIDs(Humano *personaje) {
    int* nuevoVectorIDS = new int[cantidadPersonajes+1];
    for (int i = 0 ; i < cantidadPersonajes ; i++){
        nuevoVectorIDS[i] = vectorIDsPersonajes[i];
    }
    nuevoVectorIDS[cantidadPersonajes] = personaje->obtenerID();
    delete [] vectorIDsPersonajes;
    vectorIDsPersonajes = nuevoVectorIDS;
    cantidadPersonajes++;
}

int* Jugador::getVectorIDs() {
    return this->vectorIDsPersonajes;
}

void Jugador::eliminarPersonajeVectorID(Ser *personaje) {
    int id = personaje->obtenerID();
    if (cantidadPersonajes > 1) {
        int *nuevoVectorIDs = new int[cantidadPersonajes - 1];
        int j = 0; //contador del nuevo vector

        for (int i = 0; i < cantidadPersonajes; i++) {
            if (id != vectorIDsPersonajes[i]) {
                nuevoVectorIDs[j] = vectorIDsPersonajes[i];
                j++;
            }
        }
        delete[] vectorIDsPersonajes;
        vectorIDsPersonajes = nuevoVectorIDs;
    } else {
        delete[] vectorIDsPersonajes;
        vectorIDsPersonajes = nullptr;
    }
    cantidadPersonajes--;

}

void Jugador::recorrerTableroNuevaPartida() {
    int id;
    int cantidadPersonajesIngresados = 0;
    int fila = 1, columna;

    while ((fila <= tablero->getAlto()) && (cantidadPersonajesIngresados < cantidadPersonajes)) {
        columna = 1;
        while ((columna <= tablero->getAlto()) && (cantidadPersonajesIngresados < cantidadPersonajes)) {
            if (tablero->devolverCasillero(fila, columna)->tieneSer()) {
                Ser* personaje = dynamic_cast<Ser *>(tablero->devolverCasillero(fila, columna)->devolverSer());
                id = personaje->obtenerID();
                setPersonajeBando(id, personaje, cantidadPersonajesIngresados);
            }
            columna++;
        }
        fila++;
    }
}

void Jugador::setPersonajeBando(int id, Ser* personaje, int cantidadPersonajesIngresados) {
    if (bando == BANDO_HUMANOS && personaje->esHumano()) {
        setPersonaje(id);
        cantidadPersonajesIngresados++;
    } else if (bando == BANDO_MONSTRUOS && personaje->esMonstruo()){
        setPersonaje(id);
        cantidadPersonajesIngresados++;
    }
}


void Jugador::setNumeroJugador(int numero) {
    this->numeroJugador = numero;
}

unsigned int Jugador::getNumeroJugador() {
    return numeroJugador;
}

void Jugador::imprimirVectorIDS() {
    cout << bando << ": ";
    cout << "Cantidad: " << cantidadPersonajes << endl;
    cout << "[";

    for(int i = 0; i < cantidadPersonajes; i++){

        cout << " " << vectorIDsPersonajes[i];
        cout << ",";
    }
    cout << "]\n";
}

int Jugador::obtenerIndiceJugadorContrario(int indiceJugadorActual) {
    int indiceJugadorContrario;
    if (indiceJugadorActual == 0) {
        indiceJugadorContrario = 1;
    } else {
        indiceJugadorContrario = 0;
    }
    return indiceJugadorContrario;
}

Jugador::~Jugador() {
    if (cantidadPersonajes > 0) {
        delete [] vectorIDsPersonajes;
    }
    vectorIDsPersonajes = nullptr;
}

