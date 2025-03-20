#ifndef TP3_NOSFERATU_HUMANO_H
#define TP3_NOSFERATU_HUMANO_H

#include "Ser.h"
#include "Escopeta.h"
#include "Utiles.h"

class Humano : public Ser {

protected:

    //ATRIBUTOS
    bool convertidoVampiro;

    bool convertidoZombi;

    float PORCENTAJE_ATAQUE_ZOMBI;

    float PORCENTAJE_ATAQUE_VAMPIRO;

    unsigned int turnosConversionZombi;

    static int cantidadHumanos;

public:
    //Constructor
    Humano(int id, int fila, int columna);

    //PRE: -
    //POST: Devuelve el atributo CantidadHumanos
    static int devolverCantidadHumanos();

    //PRE: -
    //POST: Muestra por pantalla los objetos del inventario
    void mostrarInventario();

    //PRE:
    //POST:devuelve true si fue exitoso el elegir el arma para atacar
    virtual bool elegirArma(Accion &error, ITEM_ELEGIDO &armaElegida);

    //PRE:
    //POST:imprime por pantalla las opciones de las armas a utilizar
    virtual void mostrarOpcionesArmas(Accion &error, ITEM_ELEGIDO &armaElegida){};

    //PRE: Recibe al personaje a ser atacado
    //POST: Se realiza el ataque correspondiente
    virtual void atacar(ITEM_ELEGIDO arma);

    //PRE: Recibe al personaje atacante
    //POST: Se modifican los atributos del personaje atacado
    void recibeAtaque(Ser* atacante, ITEM_ELEGIDO arma);

    //PRE:
    //POST: devuelve por pantalla el tipo de ataque recibido y el daño
    virtual void mostrarAtaqueRecibido(Ser* atacante, ITEM_ELEGIDO arma, int vidaQuitada);

    //PRE:
    //POST: devuelve true si el humano se convirtio en vampiro
    bool convertidoEnVampiro();

    //PRE:
    //POST: devuelve true si el humano se convirtio en zombi
    bool convertidoEnZombi();

    //PRE:
    //POST: aumenta el contador de turno que necesitara esperar hasta convertirse en zombi
    void esperarConversionZombi();

    //PRE:
    //POST: devuelve true si se convirtio en zombi ahora
    bool seConvierteEnZombiAhora();

    //PRE:
    //POST: se setea en false que no se va a convertir en zombi
    void seEvitoLaConversionZombi();

    //PRE:
    //POST: llama al usuario para que ingrese que tipo de defensa usar para el humano
    virtual void elegirDefensa();

    //PRE:
    //POST:devuelve el porcentaje del ataque al zombi
    float getPorcentajeAtaqueZombi();

    //PRE:
    //POST:devuelve el porcentaje del ataque al vampiro
    float getPorcentajeAtaqueVampiro();

    //PRE:
    //POST: dependiendo la eleccion del usuario, se realiza una defensa especifica
    virtual void defender();

    //PRE:
    //POST: imprime por pantalla quien es, sus atributos, su ubicacion y su inventario si es que tiene
    void mostrar();

    //Destructor
    ~Humano();
};


#endif //TP3_NOSFERATU_HUMANO_H
