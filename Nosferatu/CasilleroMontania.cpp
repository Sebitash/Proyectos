#include "Casillero.h"
#include "CasilleroMontania.h"

CasilleroMontania::CasilleroMontania(int fila, int columna) : Casillero(fila, columna) {
    color = BGND_BROWN_94; //marron

    costoHumano = 2;
    costoVampiro = 1;
    costoZombi = 1;
    costoCazador = 0;
    costoVanesa = 0;
    costoVampirella = 1;
    costoNosferatu = 1;
}



