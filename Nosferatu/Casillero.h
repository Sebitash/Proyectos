#ifndef TP3_NOSFERATU_CASILLERO_H
#define TP3_NOSFERATU_CASILLERO_H


#include "Objeto.h"
#include "Ser.h"
#include "Colores.h"

using namespace std;


class Casillero {

protected:
    //atributos
    Objeto *objetoSer;
    Objeto *objetoItem;
    string color;
    int fila;
    int columna;
    int costoHumano;
    int costoCazador;
    int costoVampiro;
    int costoZombi;
    int costoVanesa;
    int costoVampirella;
    int costoNosferatu;

public:
    //Constructor
    Casillero(int fila, int columna);

    //PRE: -
    //POST: Devuelve el atributo color
    string devolverColor();

    //PRE: -
    //POST: Devuelve el atributo puntero a Objeto
    Objeto *devolverSer();

    //PRE: -
    //POST: Devuelve el atributo ObjetoItem puntero a Objeto
    Objeto *devolverItem();

    //PRE: Recibe un personaje del tipo Ser
    //POST: Se setea el atributo ObjetoSer con el personaje pasado por por parametro
    void agregarSer(Ser *personaje);

    //PRE:
    //POST: crea un puero del tipo Objeto y lo setea a ObjetoSer o ObjetoItem
    void crearObjeto(const string &nombre, int id, int cantidadEnCasilla);

    //PRE:
    //POST: elimina el puntero del objeto Ser
    void eliminarObjeto();

    //PRE:
    //POST: libera el puntero del objeto Ser
    void liberarPunteroSer();

    //PRE:
    //POST: elimina el puntero del objeto Item
    void eliminarItem();

    //PRE:
    //POST:devuelve true si en el casillero hay un Ser
    bool tieneSer();

    //PRE:
    //POST:devuelve true si en el casillero hay un Item
    bool tieneItem();

    //PRE:
    //POST:devuelve el costo del camino para llegar al casillero
    int obtenerCosto(char personaje);

    //PRE:
    //POST:imprime por pantalla el casillero con su color y si hay un objeto ahi, su caracter para el mapa
    void mostrar(int &y, int &x);

    //destructor
    ~Casillero();
};


#endif //TP3_NOSFERATU_CASILLERO_H
