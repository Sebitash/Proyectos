#ifndef TP3_NOSFERATU_JUGADOR_H
#define TP3_NOSFERATU_JUGADOR_H

#include "Ser.h"
#include "Tablero.h"
#include "Arbol.h"
#include <iostream>

using namespace std;

class Jugador {

private:
    //atributos

    Tablero* tablero;

    Arbol* arbol;

    int cantidadPersonajes = 0;

    int contadorPersonajesIngresados;

    int* vectorIDsPersonajes;

    string bando;

    unsigned int numeroJugador;

public:
    //Constructor
    Jugador();

    Jugador(Tablero* tablero, Arbol* arbol);

    //PRE: SE DEBE EJECUTAR ANTES DE CARGAR LOS IDS
    Jugador(const Jugador &jugadorACopiar);

    //PRE: -
    //POST: Devuelve el atributo bando de tipo string
    string getBando();

    //PRE: Recibe un nuevo bando del tipo string
    //POST: Se cambia el atributo bando
    void setBando(string nuevoBando);

    //PRE: Recibe una nueva cantidad
    //POST: Se cambia el atributo cantidadActualPersonajes
    void setCantidadPersonajes(int nuevaCantidad);

    //PRE: -
    //POST: Devuelve la cantidad de personajes
    int getCantidadPersonajes();

    //PRE: -
    //POST: Agrega un nuevo personaje al vector
    void setPersonaje(int idPersonajeNuevo);

    //PRE: -
    //POST: Setea el vector de IDS
    void setVectorIDs();

    //PRE: -
    //POST: Agrega un personaje en el vector de IDS
    void agregarPersonajeVectorIDs(Humano* personaje);

    //PRE: -
    //POST: Devuelve el vector de IDS
    int* getVectorIDs();

    //PRE:
    //POST: elimina el personaje del vector de ids y disminuye la cantidad de personajes
    void eliminarPersonajeVectorID(Ser* personaje);

    //PRE:
    //POST: imprime por pantalla el vector de ids
    void imprimirVectorIDS();

    //PRE: -
    //POST: Devuelve true si el jugador tiene puntos de vida. False en caso contrario
    bool jugadorMuerto();

    //PRE:
    //POST: recorre el tablero para agregar el personaje al vector
    void recorrerTableroNuevaPartida();

    //PRE:
    //POST: setea el tipo de bando que sera el jugador
    void setPersonajeBando(int id, Ser* personaje, int cantidadPersonajesIngresados);

    //PRE: -
    //POST: Setea el atributo nombre
    void setNumeroJugador(int numero);

    //PRE: -
    //POST: Devuelve e atributo nombre
    unsigned int getNumeroJugador();

    int obtenerIndiceJugadorContrario(int indiceJugadorActual);

    //Destructor
    ~Jugador();

};


#endif //TP3_NOSFERATU_JUGADOR_H
