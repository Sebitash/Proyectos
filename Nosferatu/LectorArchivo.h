#ifndef TP3_NOSFERATU_LECTORARCHIVO_H
#define TP3_NOSFERATU_LECTORARCHIVO_H

#include <iostream>
#include "Inventario.h"

using namespace std;

// Clase para leer un archivo
class LectorArchivo {
protected:
    //atributos
    ifstream* archivo;

public:
    // Constructor de la clase, recibe la direccion del archivo por parametro
    LectorArchivo(const string& pathArchivo);

    // POST: Lee una linea del archivo y la devuelve como un string
    string leerLinea();

    // POST: Verifica si esta o no en el final del archivo, devuelve true si lo esta de lo contrario false
    bool esFinalArchivo();

    // POST: Elimina caracteres innecesarios o los reemplaza por otros, con el fin de obtener una linea de texto simple de procesar
    void normalizarLinea(string &linea);

    // PRE: Recibe una linea de texto y un caracter que se quiera reemplazar por otro
    // POST: Reemplaza dentro del texto, el caracter pasado por parametro en "caracterAReemplazar" y
    //      lo reemplaza por el pasado por "nuevoCaracter"
    void reemplazarCaracter(string &texto, char caracterAReemplazar, char nuevoCaracter);

    //PRE: Recibe la primera y segunda palabra de una linea de texto
    //POST: Verifica si es el nombre de un objeto y si es un nombre compuesto como "humano CV" lo une
    string procesarNombreObjeto(string& primerPalabra, istringstream &iss, string &segundaPalabra);

    //PRE: Recibe el nombre del objeto y la segunda palabra de una linea de texto
    //POST: Procesa la cantidad del objeto, si es que la tiene
    int procesarCantidadObjeto(const string& nombre, string &segundaPalabra, istringstream &iss);

    //PRE: Recibe las referencias de una fila y columna de un objeto
    //POST: Procesa el archivo de forma tal que guarda la fila y columna del objeto
    void procesarCoordenadas(string palabra, int &fila, int &columna, istringstream &iss);

    //PRE: Recibe referencias a los atributos de un personaje
    //POST: Lee el archivo y va guardando en los parametros pasados los datos de cada atributo de un ser
    void procesarAtributosPersonaje(string &palabra, istringstream &iss, float &armadura, float &fuerza, float &vida,
                                    float &energia) const;

    //PRE: Recibe como parametro la primera palabra de una linea de texto y referencias a las cantidades del inventario de un ser
    //POST: Procesa los datos del inventario de un ser a partir de un archivo, luego los guarda en las referencias pasadas como parametro
    void procesarDatosInventario(string &palabra, istringstream &iss, unsigned int &aguaBendita, unsigned int &cruces,
                                 unsigned int &estacas, unsigned int &balas, bool &escopeta) const;

    //PRE: Recibe las referencias de los datos de un objeto
    //POST: Lee el archivo y guarda los datos en los parametros
    void procesarObjeto(string &nombre, int &fila, int &columna, int &cantidad, int &id, istringstream &iss);

    // Destructor de la clase
    ~LectorArchivo();

};


#endif //TP3_NOSFERATU_LECTORARCHIVO_H
