#ifndef TP3_INVENTARIO_H
#define TP3_INVENTARIO_H
#include "Escopeta.h"
#include "Utiles.h"

class Inventario {

private:
    //ATRIBUTOS
    unsigned int cruz;
    unsigned int aguaBendita;
    unsigned int bala;
    unsigned int estaca;
    bool escopeta; // Va a haber una unica escopeta por humano

public:
    //Constructor
    Inventario();

    //PRE: Recibe una cantidad
    //POST: Se cambia el valor del atributo cruz
    void setCruz(unsigned int cantidad);

    //PRE: -
    //POST: Devuelve el atributo cruz
    unsigned int getCruz();

    //PRE: Recibe una cantidad de agua
    //POST: Setea el valor de atributo agua
    void setAguaBendita(unsigned int cantidadAgua);

    //PRE: -
    //POST: Devuelve el valor del atributo Agua Bendita
    unsigned int getAguaBendita();

    //PRE: Recibe una cantidad de balas
    //POST: Setea el valor del atributo bala
    void setBala(unsigned int cantidadBalas);

    //PRE: -
    //POST: Devuelve el valor del atributo bala
    unsigned int getBala();

    //PRE: Recibe una cantidad
    //POST: Setea el valor del atributo estaca
    void setEstaca(unsigned int cantidad);

    //PRE:
    //POST: Devuelve el valor del atributo estaca
    unsigned int getEstaca();

    //PRE: -
    //POST: Cambia a true el atributo de tipo bool escopeta
    void setEscopeta(); //Cambia a true el booleano

    //PRE: -
    //POST: Devuelve el valor del atributo escopeta
    bool getEscopeta();

    //PRE:
    //POST: devuelve true si el inventario esta vacio
    bool inventarioVacio();

    //PRE:
    //POST: aumenta la cantidad del elemento especifico del inventario
    void aumentarElemento(int cantidad, char elemento);

    //PRE:
    //POST: disminuye la cantidad del elemento especifico del inventario
    void disminuirElemento(ITEM_ELEGIDO elemento);


    // PRE: -
    // POST: Se fija en el inventario si tiene o no una escopeta
    bool tieneEscopeta();

    // PRE: -
    // POST: Verifica si el Ser tiene 2 o mas balas
    bool tieneBalasSuficientes();

    // PRE: -
    // POST: Verifica dentro del inventario del Humano si tiene o no agua bendita
    bool tieneAguaBendita();

    //PRE: -
    //POST: Verifica si el Humano tiene una estaca
    bool tieneEstaca();

    //PRE: -
    //POST: Verifica si el Humano tiene una cruz en el inventario
    bool tieneCruz();

    //Destructor
    ~Inventario();
};


#endif //TP3_INVENTARIO_H
