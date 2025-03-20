#ifndef TP3_NOSFERATU_ESCRITURAARCHIVO_H
#define TP3_NOSFERATU_ESCRITURAARCHIVO_H

#include <iostream>
#include "fstream"

using namespace std;

class EscrituraArchivo {
private:
    //atributos
    ofstream* archivo;
public:

    //constructor
    EscrituraArchivo(string pathArchivo);

    //PRE:recibe la linea a escribir
    //POST:escribe la linea al final del archivo
    void escribir(const string& palabra);

    //PRE:
    //POST:escribe un fin de linea
    void escribirFinLinea();

    //PRE:
    //POST:si el archivo se encuentra abierto, lo cierra
    void cerrarArchivo();

    //PRE:recibe por parametro un float
    //POST:escribe el numero float en el archivo
    void escribir(float numero);

    //PRE:recibe por parametro un float
    //POST:escribe el numero float en el archivo
    void escribir(int numero);

    void escribirID(int numero);

    //PRE:recibe por parametro un int
    //POST:escribe el numero int en el archivo
    void escribir(unsigned int numero);

    //PRE:recibe por parametro un int
    //POST:escribe la ultima palabra de la linea
    void escribirUltimaPalabraLinea(int numero);

    //destructor
    ~EscrituraArchivo();
};


#endif //TP3_NOSFERATU_ESCRITURAARCHIVO_H
