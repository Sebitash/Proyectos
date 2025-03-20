#ifndef CAZADOR_H_
#define CAZADOR_H_

#include "Humano.h"
#include "Tablero.h"

class Cazador : public Humano {
public:
    //constructor
    Cazador(int id, int fila, int columna);

    //PRE: Recibe al personaje a ser atacado
    //POST: Se realiza el ataque correspondiente
    virtual void atacar(ITEM_ELEGIDO arma);

    //PRE:
    //POST:devuelve true si fue exitoso el elegir el arma para atacar
    bool elegirArma(Accion &error, ITEM_ELEGIDO &armaElegida);

    //PRE:
    //POST:imprime por pantalla las opciones de las armas a utilizar
    void mostrarOpcionesArmas(Accion &error, ITEM_ELEGIDO &armaElegida);

    //PRE:
    //POST:imprime por pantalla las opciones de defensa y le da al usuario la opcion a elegir
    virtual void elegirDefensa();

    //PRE:
    //POST: aumenta la vida del propio cazador
    virtual void defender();

    //PRE:
    //POST:imprime por pantalla su nombre, sus atributo, su ubicacion y si tiene, su inventario
    virtual void mostrar();
};


#endif /* CAZADOR_H_ */
