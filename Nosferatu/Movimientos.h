#ifndef TP3_MOVIMIENTOS_H
#define TP3_MOVIMIENTOS_H
#include <iostream>
#include "Objeto.h"
#include "Arbol.h"
#include "Casillero.h"
#include "Utiles.h"
#include "Jugador.h"
#include "Tablero.h"
#include "Humano.h"
#include "Vampiro.h"
#include "Bala.h"
#include "Agua.h"
#include "Monstruo.h"
#include "Grafo.h"
#include "EscrituraArchivo.h"
#include "ImpresionesPantalla.h"
#include "Constantes.h"
#include <iomanip>

class Movimientos {
private:
    //atributos
    Tablero* tablero;

public:
    //constructor
    Movimientos( Tablero* tablero);

    //PRE: Recibe un personaje del tipo Ser
    //POST: Se mueve el personaje
    void moverPersonaje(Ser* personaje, bool &ejecucionExitosa);

    //destructor
    ~Movimientos();

private:

    //PRE: Recibe un puntero al grafo, una fila y columna inicial
    //POST: Se actualiza la posicion del personaje
    void actualizarPosicionPersonaje(Grafo* grafo, int filaInicio, int columnaInicio);

    //PRE: recibe un puntero al casillero actual
    //POST:verifica si el humano puede agarrar el item o no del casillero
    void agarrarParaHumanos(Casillero *casillero);

    //PRE: recibe un puntero al casillero actual
    //POST:agarra el item del casillero y aumenta su inventario
    void agarrarItem(Casillero *casillero);

    //PRE:
    //POST:devuelve la cantidad del elemento a agarrar
    int devolverCantidadItemNuevo(Casillero *caillero, char nombreElemento);

    //PRE:recibe el personaje, la cantidad y el elemento
    //POST:agrega al inventario la cantidad respectivamente
    void insertarElementoInventario(Ser* personaje, int cantidad, char elemento);

    //PRE: recibe un puntero al casillero actual
    //POST:verifica si el humano puede agarrar el item o no del casillero
    void agarrarParaMonstruos(Casillero *casillero);

    //PRE:solo pasa si es un vampiro
    //POST: se elimina el puntero del item en el casillero
    void destruirEstaca(Casillero* casillero);

    //PRE:
    //POST: imprime por pantalla el item agarrado
    void imprimirItemAgarrado(char elemento);

};


#endif //TP3_MOVIMIENTOS_H
