#include "EscrituraArchivo.h"


EscrituraArchivo::EscrituraArchivo(string pathArchivo) {
    archivo = new ofstream;
    archivo->open(pathArchivo, ios::out);
}

void EscrituraArchivo::escribir(const string &palabra) {
    *archivo << palabra << " ";
}

void EscrituraArchivo::escribir(float numero) {
    *archivo << to_string((int) numero) << " ";
}

void EscrituraArchivo::escribir(int numero) {
    *archivo << to_string(numero) << " ";
}

void EscrituraArchivo::escribirID(int numero) {
    string datoAGuardar = to_string(numero);
    if (numero < 100){
        datoAGuardar = "0"+datoAGuardar;
        if (numero < 10) {
            datoAGuardar = "0"+datoAGuardar;
        }
    }
    *archivo << datoAGuardar << " ";
}

void EscrituraArchivo::escribirFinLinea() {
    *archivo << "\n";
}

void EscrituraArchivo::cerrarArchivo() {
    archivo->close();
}

void EscrituraArchivo::escribir(unsigned int numero) {
    *archivo << to_string((int) numero) << " ";
}

void EscrituraArchivo::escribirUltimaPalabraLinea(int numero) {
    *archivo << to_string((int) numero);
}

EscrituraArchivo::~EscrituraArchivo() {
    archivo->close();
    delete archivo;
}
