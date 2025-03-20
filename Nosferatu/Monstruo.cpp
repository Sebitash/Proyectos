#include "Monstruo.h"

int Monstruo::cantidadMonstruos = 0;

Monstruo::Monstruo(int id, int fila, int columna) : Ser(id, fila, columna) {
    cantidadMonstruos++;
	this->escondido = false;
}

bool Monstruo::esta_escondido() {
    return escondido;
}

bool Monstruo::elegirArma(Accion &error, ITEM_ELEGIDO &armaElegida) {
    armaElegida = NINGUNO;
    return true;
}
int Monstruo::devolverCantidadMonstruos(){
    return cantidadMonstruos;
}
Monstruo::~Monstruo(){
   cantidadMonstruos--;

}
