#ifndef TP3_NOSFERATU_JUEGO_H
#define TP3_NOSFERATU_JUEGO_H


#include <iostream>
#include <string>
#include <unistd.h>
#include "Utiles.h"
#include "MenuJuego.h"
#include <iomanip>
#include "Jugador.h"
#include "Simulacion.h"
#include "ImpresionesPantalla.h"

using namespace std;


class Juego {
private:
    //atributos
    Tablero *tablero;
public:
    //Constructor
    Juego();

    //PRE: -
    //POST: Se inicia la simulacion creandose el diccionario y mostrando el menu del juego
    void comenzar(bool &finalDeEjecucion);

    //PRE: -
    //POST: Se ejecutan las funciones del menu principal
    void ingresarMenuPrincipal();

    //PRE: -
    //POST: Se muestran por pantalla las opciones del menu principal
    void mostrarOpcionesMenuPrincipal();

    //PRE: Recibe el archivo a cargar, una palabra y un puntero a Jugador
    //POST: Se cargan los personajes del jugador correspondiente
    void cargarPersonajesJugador(LectorArchivo &archivoCargar, string &palabra, Simulacion &simulacion,
                                 int indiceJugador, istringstream &iss) const;

    //PRE: -
    //POST: Se carga el juego de la partida actual
    void cargarPartida(bool &seGuardaPartida,bool &finalDeJuego);

    int setNumeroJugador(int numeroPrimerJugador, bool cargaPrimerJugador);

    //PRE: -
    //POST: Se empieza una partida nueva
    void empezarPartidaNueva();

    //PRE: Recibe un objeto LectorArchivo que apunta al archivo para cargar la partida, como asi tambien un string stream
    //      que apunta a una linea de ese archivo, junto con la primera palabra leida
    //POST: Guarda los datos de los items que se encuentran en el archivo para cargar partida en el tablero
    void cargarDatosTablero(LectorArchivo &archivoCargar, string &palabra);


    //Destructor
    ~Juego();
};


#endif //TP3_NOSFERATU_JUEGO_H
