#ifndef TP3_OBJETO_H
#define TP3_OBJETO_H

#include <string>

using namespace std;

class Objeto {
protected:
    //atributos
    int id, fila, columna;
    char nombreMapa;
public:
    // Constructor
    Objeto();

    //PRE: -
    //POST: Construye la entidad, definiendo la posicion que ocupa la misma
    Objeto(int id, int fila, int columna);

    //PRE: -
    //POST: Devuelve la fila donde se encuentra la entidad
    int obtenerFila();

    //PRE: -
    //POST: Devuelve la columna donde se encuentra la entidad
    int obtenerColumna();

    //PRE: -
    //POST: Devuelve el caracter asociado, que representa a la entidad en el mapa (En clases hijas)
    char obtenerNombreMapa();

    //PRE: -
    //POST: Muestra por pantalla un mensaje personalizado de la entidad (En clases hijas)
    virtual void mostrar() = 0;

    //PRE: -
    //POST: Devuelve el id del objeto
    int obtenerID();

    // PRE: -
    // POST: Setea la fila en la que se encuentra el objeto
    void setFila(int fila);

    // PRE: -
    // POST: Setea la columna en la que se encuentra el objeto
    void setColumna(int columna);

    // PRE: -
    // POST: Setea el nombre en el mapa del objeto
    void setNombreMapa(char nombre);

    // Destructor
    virtual ~Objeto();

};


#endif 
