#include "CasilleroVacio.h"

CasilleroVacio::CasilleroVacio(int fila , int columna) : Casillero(fila , columna) {
    color = BGND_DARK_PURPLE_53; //violeta oscuro
    costoHumano = 15;
    costoVampiro = 15;
    costoZombi = 15;
    costoCazador = 15;
    costoVanesa = 15;
    costoVampirella = 15;
    costoNosferatu = 15;
}
