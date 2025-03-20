#include "CasilleroCamino.h"

CasilleroCamino::CasilleroCamino(int fila, int columna) : Casillero( fila , columna ) {
	color = BGND_GRAY_241; //gris
	costoHumano = 1;
	costoVampiro = 1;
	costoZombi = 1;
    costoCazador = 1;
    costoVanesa = 1;
    costoVampirella = 1;
    costoNosferatu = 1;
}
