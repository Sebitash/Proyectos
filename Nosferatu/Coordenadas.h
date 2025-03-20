#ifndef TP3_COORDENADAS_H
#define TP3_COORDENADAS_H


class Coordenadas {

private:
    //atributos
    int fila;

    int columna;

    int cantCasillerosVisitados;

public:
    //constructores
    Coordenadas();

    Coordenadas(int f, int c, int cant);

    //PRE:
    //POST:devuelve la fila de la coordenada
    int getFila();

    //PRE:
    //POST:devuelve la columna de la coordenada
    int getColumna();

    //PRE:
    //POST:setea la fila de la coordenada
    void setFila(int f);

    //PRE:
    //POST:setea la columna de la coordenada
    void setColumna(int c);

    //PRE:
    //POST:devuelve la cantidad de casilleros visitados
    int getCantidadCasillerosVisitados();

    //PRE:
    //POST:aumenta la cantidad de casilleros visitados
    void incrementarCasillerosVisitados(int cantidadVisitadaActual);

    //PRE:
    //POST: setea la coordenada
    void setCoordenadas(int f, int c);

    //PRE:
    //POST:imprime por pantalla las coordenadas
    void mostrarCoordenadas();

};


#endif //TP3_COORDENADAS_H
