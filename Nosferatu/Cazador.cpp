#include "Cazador.h"
#include "Utiles.h"
#include "Constantes.h"

const int NULO = 0;

Cazador::Cazador(int id, int fila, int columna) : Humano(id, fila, columna) {
    this->nombreMapa = LETRA_CV;
    this->recargaEnergiaTurno = 8;
    this->energiaMinimaAtaque = 6;
    this->energiaMinimaDefensa = 5;
    this->PORCENTAJE_ATAQUE_ZOMBI = 1.05;
    this->PORCENTAJE_ATAQUE_VAMPIRO = 0.3;
}

void Cazador::atacar(ITEM_ELEGIDO arma) {
    if (arma == ITEM_ESCOPETA) {
        disminuirEnergia(energiaMinimaAtaque);
        inventario->disminuirElemento(ITEM_BALA);
    } else if (arma == ITEM_AGUA_BENDITA) {
        inventario->disminuirElemento(arma);
    }
}

bool Cazador::elegirArma(Accion &error, ITEM_ELEGIDO &armaElegida) {
    bool exito;
    mostrarOpcionesArmas(error, armaElegida);
    if (armaElegida == ITEM_ESCOPETA && !inventario->tieneBalasSuficientes()) {
        error = SIN_BALAS_SUFICIENTES;
    }

    if (error == ES_REALIZABLE) {
        exito = true;
    } else {
        exito = false;
    }
    return exito;
}

void Cazador::mostrarOpcionesArmas(Accion &error, ITEM_ELEGIDO &armaElegida) { //SE VALIDO QUE TENGA EL ARMA ELEGIDA
    string input;
    bool ingresoArmaValida = false;
    if (!inventario->inventarioVacio()) {

        while (!ingresoArmaValida) {
            cout << endl << "ELIJA UN ARMA:" << endl;
            if (inventario->tieneEscopeta()) {
                cout << "1 - Escopeta" << endl;
            }
            if (inventario->tieneEstaca()) {
                cout << "2 - Estaca: " << endl;
            }
            if (inventario->tieneAguaBendita()) {
                cout << "3 - Agua Bendita: " << endl;
            }
            cin >> input;
            int opcionElegida = Utiles::ingresoValido(input, 1, 3);

            if (opcionElegida == ITEM_ESCOPETA && inventario->tieneEscopeta()) {
                armaElegida = ITEM_ESCOPETA;
                ingresoArmaValida = true;
            } else if (opcionElegida == ITEM_ESTACA && inventario->tieneEstaca()) {
                armaElegida = ITEM_ESTACA;
                ingresoArmaValida = true;
            } else if (opcionElegida == ITEM_AGUA_BENDITA && inventario->tieneAguaBendita()) {
                armaElegida = ITEM_AGUA_BENDITA;
                ingresoArmaValida = true;
            } else {
                cout << "El numero ingresado no es una opción. Intente de nuevo.. " << endl;
            }
        }

    } else {
        error = INVENTARIO_VACIO;
        armaElegida = NINGUNO;
    }
}

void Cazador::elegirDefensa() {
    string input;
    cout << "1 - Se cura 50 puntos de vida" << endl;
    cout << "2 - Se cura a todo el equipo 20 puntos de vida menos a este Cazador " << endl;
    cin >> input;
    int opcion = Utiles::ingresoValido(input, 1, 2);
    if (opcion == 1) {
        defensaElegida = DEFENSA_NINGUN_ELEMENTO;
        cout << endl << "El cazador se curará hasta 50 de vida" << endl;
    } else {
        defensaElegida = DEFENSA_CAZADOR_CURAR_EQUIPO;
    }
}

void Cazador::defender() { //Solo puede ser defensa de curarse su propia vida
    aumentarVida(50);
}

void Cazador::mostrar() {
    std::cout << "Soy Cazador de vampiros y Zombis" << std::endl;
    mostrarAtributos();
    mostrarInventario();
}