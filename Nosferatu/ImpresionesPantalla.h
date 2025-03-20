#ifndef TP3_ULTIMA_IMPRESIONESPANTALLA_H
#define TP3_ULTIMA_IMPRESIONESPANTALLA_H

#include "Gotoxy.h"
#include <iostream>
#include <iomanip>
#include "Colores.h"

using namespace std;


class ImpresionesPantalla {
private:

public:
    //Constructor
    ImpresionesPantalla() {};

    //PRE:
    //POST:imprime por pantalla el menu del juego principal
    static void impresionJuego();

    //PRE:
    //POST:imprime por pantalla los creditos

    static void impresionCreditos();

    //PRE:
    //POST:imprime por pantalla el mensaje al salir
    static void impresionSalir();

    //PRE:
    //POST:imprime por pantalla el menuJuego
    static void imprimirMenuJuego();

    //PRE:
    //POST:imprime por pantalla las coordenadas del tablero
    static void impresionCoordenadas(int alto, int ancho);

    //PRE:
    //POST:imprime por pantalla las referencias del tablero
    static void referenciasTablero();

    //PRE:
    //POST:imprime por pantalla las opciones de los objetos
    static void impresionOpcionesObjetos();

    //PRE:
    //POST:imprime por pantalla las opciones de los cuadrantes
    static void impresionOpcionesCuadrante();

    //PRE:
    //POST:imprime por pantalla el titulo de busqueda por cuadrante
    static void impresionTituloBusquedaCuadrante();

    //PRE:
    //POST:imprime por pantalla el titulo "MENU"
    static void impresionTituloMenu();

    //PRE:
    //POST:imprime por pantalla el titulo de alta de objeto
    static void impresionTituloAltaObjeto();

    //PRE:
    //POST:imprime por pantalla el titulo de baja de objeto
    static void impresionTituloBajaObjeto();

    //PRE:
    //POST:imprime por pantalla el titulo de busqueda por ID
    static void impresionTituloBusquedaID();

    //PRE:
    //POST:imprime por pantalla el titulo "TABLERO"
    static void impresionTituloTablero();

    //PRE:
    //POST:imprime por pantalla el titulo "CREDITOS"
    static void impresionTituloCreditos();

    //PRE:
    //POST:imprime por pantalla el menu simulacion
    static void impresionMenuSimulacion();

    //PRE:
    //POST:imprime por pantalla el menu simulacion
    static void impresionMostrarCantidadBando(int humanos, int monstruos);

    //PRE:
    //POST: ubica el boton continuar a un posicion especifica
    static void impresionBotonContinuar();

    //PRE:
    //POST: imprime por pantalla el titulo "Game Over"
    static void impresionGameOver();
};


#endif //TP3_ULTIMA_IMPRESIONESPANTALLA_H
