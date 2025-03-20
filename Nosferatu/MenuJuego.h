#ifndef TP3_NOSFERATU_MENUJUEGO_H
#define TP3_NOSFERATU_MENUJUEGO_H

#include <iostream>
#include <string>
#include <unistd.h>
#include "Utiles.h"
#include "Tablero.h"
#include "Casillero.h"
#include "LectorArchivo.h"
#include "Arbol.h"
#include "ImpresionesPantalla.h"

using namespace std;
class MenuJuego {
public:
    //Constructor
    MenuJuego();

    //PRE: Recibe punteros al tablero
    //POST:
    void mostrar(Tablero *tablero, bool &seGuardaPartida,bool &finalDeJuego);

    //PRE: Recibe un puntero al tablero y una opcion numerica
    //POST: Dependiendo de la opcion ingresada se ejecuta el método correspondiente
    void realizarAccion(Tablero *&tablero, int opcion,bool &finalDeJuego,bool &seGuardaPartida);

    //PRE: Recibe un puntero al tablero
    //POST: Se muestran las opciones de los objetos a agregar y se los agrega al tablero
    void agregarObjeto(Tablero *&tablero);

    //PRE: Recibe una opcion numerica y una cantidad
    //POST: Se ingresa la cantidad que se desea agregar
    void ingresarCantidadObjeto(int opcion, string &cantidad) const;

    //PRE: Recibe una opcion numerica
    //POST: Devuelve el nombre del objeto/personaje
    string obtenerNombreTipoObjeto(int opcionIngresada);

    //PRE: Recibe una opcion de tipo entero
    //POST: Devuelve el id (normal/aleatorio) del objeto o personaje
    int obtenerIDAleatorioObjeto(int opcionObjeto);

    //PRE: Recibe un puntero a tablero
    //POST: Se elimina el objeto del tablero
    void eliminarObjeto(Tablero *&tablero);

    //PRE: -
    //POST: Se muestra por pantalla las opciones de un menu
    void imprimirOpciones();

    //PRE: Recibe un puntero a tablero
    //POST: Se realiza la busqueda del elemento por cuadrante
    void buscarPorCuadrante(Tablero* &tablero);

    //PRE: Recibe un puntero a arbol
    //POST: Se realiza la busqueda por id del objeto/personaje
    void buscarPorID(Arbol *&arbol);

    //PRE: -
    //POST: Se muestra por pantalla opciones de objetos
    void imprimirOpcionObjetos();

    //PRE: -
    //POST: Se muestra por pantalla opciones de cuadrante
    void imprimirOpcionCuadrantes();

    //PRE: Recibe una fila y columna, junto a una fila y columna maxima
    //POST: Se le pide al usuario que ingrese una fila y columna y se validan
    void ingresarCoordenadas(int &fila, int &columna, int filaMaxima, int columnaMax);

};


#endif //TP3_NOSFERATU_MENUJUEGO_H
