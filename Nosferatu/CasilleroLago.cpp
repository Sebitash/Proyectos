#include "CasilleroLago.h"

CasilleroLago::CasilleroLago(int fila, int columna) : Casillero(fila, columna) {
    color = BGND_BLUE_4; //celeste
    costoHumano = 0;
    costoVampiro = 1;
    costoZombi = 2;
    costoCazador = 0;
    costoVanesa = 0;
    costoVampirella = 1;
    costoNosferatu = 1;
}


