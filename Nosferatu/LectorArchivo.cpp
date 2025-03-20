#include "algorithm"
#include <fstream>
#include <string>
#include <sstream>

#include "LectorArchivo.h"
#include "Constantes.h"
#include "Inventario.h"

const string BENDITA = "bendita";

LectorArchivo::LectorArchivo(const string& pathArchivo) {
    archivo = new ifstream;
    archivo->open(pathArchivo, ios::in);
    if (!archivo) {
        archivo->close();
        delete archivo;
        cout << "El archivo " << pathArchivo << " no se pudo abrir"  << endl;
    }
}

string LectorArchivo::leerLinea() {
    string linea;
    getline(*archivo, linea);
    normalizarLinea(linea);
    return linea;
}

bool LectorArchivo::esFinalArchivo() {
    return (archivo->eof());
}

void LectorArchivo::normalizarLinea(string &linea) {
    reemplazarCaracter(linea, ',', ' ');

    for (int i = linea.length(); i >= 0; i--) {
        if (ispunct(linea[i])) {
            linea.erase(linea.begin() + i);
        }
    }
}

void LectorArchivo::reemplazarCaracter(string &texto, char caracterAReemplazar, char nuevoCaracter) {
    std::replace(texto.begin(), texto.end(), caracterAReemplazar, nuevoCaracter);
}


string LectorArchivo::procesarNombreObjeto(string& primerPalabra,  istringstream &iss, string& segundaPalabra) {
    string nombre = primerPalabra;
    if (segundaPalabra == NOMBRE_CV) {
        nombre += " " + segundaPalabra;
        iss >> segundaPalabra;
    } else if (primerPalabra == NOMBRE_BALAS) {
        nombre = NOMBRE_BALA;
    } else if (segundaPalabra == BENDITA) {
        nombre = NOMBRE_AGUA;
        iss >> segundaPalabra;
    }
    return nombre;
}

int LectorArchivo::procesarCantidadObjeto(const string& nombre, string &segundaPalabra, istringstream &iss) {
    int cantidadEnCasilla = 1;
    if (nombre == NOMBRE_AGUA || nombre == NOMBRE_BALA) {
        cantidadEnCasilla = stoi(segundaPalabra);
        iss >> segundaPalabra;
    }
    return cantidadEnCasilla;
}

void LectorArchivo::procesarCoordenadas(string palabra, int &fila, int &columna, istringstream &iss) {
    fila = stoi(palabra);
    iss >> palabra;
    columna = stoi(palabra);
}

void LectorArchivo::procesarAtributosPersonaje(string &palabra, istringstream &iss, float &armadura,float &fuerza, float &vida, float &energia) const {
    iss >> palabra;
    armadura = stof(palabra);
    iss >> palabra;
    fuerza = stof(palabra);
    iss >> palabra;
    vida = stof(palabra);
    iss >> palabra;
    energia = stof(palabra);
}


void LectorArchivo::procesarDatosInventario(string &palabra, istringstream &iss, unsigned int &aguaBendita,
                                            unsigned int &cruces, unsigned int &estacas, unsigned int &balas,
                                            bool &escopeta) const {
    iss >> palabra;
    aguaBendita = stoul(palabra);

    iss >> palabra;
    cruces = stoul(palabra);

    iss >> palabra;
    estacas = stoul(palabra);

    iss >> palabra;
    if (palabra == "1")
        escopeta = true;

    iss >> palabra;
    balas = stoul(palabra);
}

void LectorArchivo::procesarObjeto(string &nombre, int &fila, int &columna, int &cantidad, int &id, istringstream &iss) {
    string palabra, segundaPalabra;

    iss >> nombre;
    iss >> segundaPalabra;

    nombre = procesarNombreObjeto(nombre,iss ,segundaPalabra);
    cantidad = procesarCantidadObjeto(nombre, segundaPalabra, iss);

    procesarCoordenadas(segundaPalabra, fila, columna, iss);

    iss >> palabra;
    id = stoi(palabra);
}

LectorArchivo::~LectorArchivo() {
    if (archivo) {
        archivo->close();
        delete archivo;
    }
}
