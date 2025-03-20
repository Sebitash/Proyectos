#ifndef TP3_GRAFO_H
#define TP3_GRAFO_H

#include "Tablero.h"
#include "Casillero.h"
#include "Coordenadas.h"

const int INFINITO = 9999999;

enum Direccion {
    IZQUIERDA,
    DERECHA,
    ARRIBA,
    ABAJO
};

//Grafo no crea un grafo en sí, sino que es la clase que se encarga de la tarea de caminos minimos y mover
class Grafo {

private:
    //atributos
    Tablero *tablero;

    int cantCasilleros;

    int cantFilas; //Si hay 8 filas, el indice mas grande sera 7 para las filas

    int cantColumnas;

    int **distancias;

    bool **visitados;

    Coordenadas **predecesores;

    Coordenadas *recorrido;

    Casillero *casilleroInicio;

    Casillero *casilleroDestino;

    int filaInicio; // NO SE REFIEREN AL INDICE DE LA MATRIZ
    //FILA 1 COLUMNA 1 ES MATRIZ[0][0]

    int columnaInicio;

    int filaActual;

    int columnaActual;

    int filaDestino;

    int columnaDestino;

    int cantCasillerosVisitados;

    int costoCaminoMinimo;

    char personaje; //personaje que se mueve

public:
    //Constructor
    //PRE: Antes de realizar este procedimiento, se pide verificar que la casilla a moverse NO esté ocupada
    Grafo(Tablero *tablero);

    //PRE
    //POST:setea esas los parametros recibidos
    void definirCamino(int filaInicio, int columnaInicio, int filaDestino, int columnaDestino);


    //PRE:
    //POST: devuelve el costo del camino minimo, Si devuelve 9999999 es que NO se puede llegar
    int caminosMinimos();

    //PRE:
    //POST:Devuelve en la posicion 0 la casilla de inicio y en la ultima, la de llegada
    Coordenadas *devolverRecorrido();

    //PRE:Debe ejecutarse luego de haber hecho caminos minimos
    //POST devuelve el largo del recorrido
    int devolverLargoRecorrido();

    //PRE: SOLO PUEDE MOSTRAR ANTES DE MOVER AL JUGADOR
    //POST: muestra por pantalla el recorrido
    void mostrarRecorrido();

    //PRE:Si y solo si se ejecuto caminosMinimos
    //POST:devuelve el costo del camino
    int getCostoCamino();

    //destructor
    ~Grafo();


private:

    //PRE:
    //POST:crea los vectores
    void crearVectores();

    //PRE:
    //POST: inicializa los vectores
    void inicializarVectores();

    //PRE:
    //POST: devuelve el costod el casillero a revisar
    int costo(Direccion casilleroARevisar);

    //PRE:
    //POST: revisa el tablero para ver si hay casillero disponible
    void revisarTablero(Direccion direccionARevisar, int variacionFila, int variacionColumna, int costoAcum);

    //PRE
    //POST: devuelve las coordenadas del predecesor
    Coordenadas devolverPredecesor(int fila, int columna);

    //PRE:
    //POST: devuelve true si el casillero destino esta libre
    bool casilleroDestinoLibre();

    //PRE:
    //POST:Se fija si en la direccion que quiero fijarme hay un casillero o no
    bool hayCasillero(Direccion direccion);

    //PRE:
    //POST: se fija si en la direccion que quiero fijarme hay un ser o no
    bool haySer(Direccion direccion);

    //PRE:
    //POST: cambia el casillero siguiente a casillero actual
    void cambiarCasilleroActual();

    //PRE:
    //POST: recibis el recorrido del camino minimo
    void obtenerRecorrido();

    //PRE:
    //POST: muestra por pantalla los vectores
    void mostrarVectores();

};


#endif //TP3_GRAFO_H
