#include "CasilleroVolcan.h"

CasilleroVolcan::CasilleroVolcan(int fila , int columna) : Casillero(fila, columna) {
	color = BGND_DARK_RED_88;//NARANJA OSCURO O ROJO OSCURO
    costoHumano = 1;
    costoVampiro = 2;
    costoZombi = 0;
    costoCazador = 1;
    costoVanesa = 1;
    costoVampirella = 2;
    costoNosferatu = 2;
}
