#ifndef MONSTRUO_H_
#define MONSTRUO_H_

#include "Ser.h"

class Monstruo : public Ser {

protected:
    //atributos
	bool escondido;
    static int cantidadMonstruos;
public:
    //Constructor
	Monstruo(int id, int fila, int columna);

    //PRE: -
    //POST: Devuelve el atributo escondido ya sea en true o false
	bool esta_escondido();

    //PRE: Recibe al personaje a ser atacado
    //POST: Se realiza el ataque correspondiente
    virtual void atacar(ITEM_ELEGIDO arma) = 0;

    //PRE: Recibe al personaje atacante
    //POST: Se modifican los atributos del personaje atacado
    virtual void recibeAtaque(Ser* atacante, ITEM_ELEGIDO arma) = 0;

    //PRE:
    //POST: devuelve true si fue exitoso el elegir el arma para atacar
    bool elegirArma(Accion &error, ITEM_ELEGIDO &armaElegida);

    //PRE:
    //POST:imprime por pantalla las opciones de las armas a utilizar
    void mostrarOpcionesArmas(Accion &error, ITEM_ELEGIDO &armaElegida){};

    //PRE:
    //POST:imprime por pantalla las opciones de defensa y le da al usuario la opcion a elegir
    virtual void elegirDefensa() = 0;

    //PRE:
    //POST: se ejecuta la opcion de defensa elegida
    virtual void defender() = 0;

    //PRE: -
	//POST: Devuelve la cantidad de monstruos
	static int devolverCantidadMonstruos();

	//Destructor
	~Monstruo();
};

#endif /* MONSTRUO_H_ */
