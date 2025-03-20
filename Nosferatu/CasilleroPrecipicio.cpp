#include "CasilleroPrecipicio.h"

CasilleroPrecipicio::CasilleroPrecipicio(int fila , int columna) : Casillero(fila , columna) {
	color = BGND_LIGHT_GRAY_246; //gris claro

    costoHumano = 2;
    costoVampiro = 0;
    costoZombi = 1;
    costoCazador = 2;
    costoVanesa = 2;
    costoVampirella = 0;
    costoNosferatu = 0;
}
