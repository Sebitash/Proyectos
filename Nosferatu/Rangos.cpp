#include "Rangos.h"

enum DIRECCIONES_ALEATORIAS {
    ALEATORIO_ARRIBA = 1,
    ALEATORIO_ABAJO = 2,
    ALEATORIO_IZQUIERDA = 3,
    ALEATORIO_DERECHA = 4
};

Rangos::Rangos(Tablero *tablero) {
    this->tablero = tablero;
}


bool Rangos::estaEnRango(int filaPersonaje, int columnaPersonaje , int &filaElegida, int &columnaElegida, TIPO_ACCION tipoAccion, Accion &error, ITEM_ELEGIDO itemElegido,Ser *personaje) {
    error = POSICION_FUERA_RANGO;
    bool enRango = false;

    if (tipoAccion == ATAQUE && ( (personaje->esCazadorGeneral() && itemElegido == ITEM_AGUA_BENDITA) ||
                                  (personaje->esHumanoSimple() && itemElegido == ITEM_ESCOPETA) ) ) {

        enRango = estaEnRangoRadio1(filaPersonaje, columnaPersonaje, filaElegida, columnaElegida, error);

    } else if ( (tipoAccion == ATAQUE && personaje->esCazador() && itemElegido == ITEM_ESCOPETA) ||
                ( personaje->esVanesa() && ( (tipoAccion == ATAQUE && itemElegido == ITEM_ESCOPETA)  || tipoAccion == DEFENSA ) )
                || personaje->esNosferatu() ) {

        enRango = estaEnRangoRadio2(filaPersonaje, columnaPersonaje,filaElegida, columnaElegida, error);

    } else {
        enRango = estaEnRangoRadioFlor(filaPersonaje, columnaPersonaje, filaElegida, columnaElegida, error,personaje);
    }

    if (enRango) {
        error = ES_REALIZABLE;
    }
    return enRango;
}

bool Rangos::estaEnRangoRadio1(int filaPersonaje, int columnaPersonaje  , int &filaElegida, int &columnaElegida, Accion &error) {
    return (definirRangosConRadio(1,filaPersonaje,columnaPersonaje,filaElegida,columnaElegida, error));
}

bool Rangos::estaEnRangoRadio2(int filaPersonaje, int columnaPersonaje , int &filaElegida, int &columnaElegida, Accion &error) {
    return (definirRangosConRadio(2,filaPersonaje,columnaPersonaje,filaElegida,columnaElegida, error));
}

bool Rangos::definirRangosConRadio(int radio , int filaPersonaje, int columnaPersonaje , int &filaElegida, int &columnaElegida, Accion &error) {

    bool enRangoArriba , enRangoAbajo , enRangoIzquierda , enRangoDerecha;

    //ELEMENTO [0] --> FILA  || ELEMENTO [1] --> COLUMNA
    int abajoIzquierda[2] = {filaPersonaje + radio, columnaPersonaje - radio};
    int abajoDerecha[2] = {filaPersonaje + radio, columnaPersonaje + radio};
    int arribaIzquierda[2] = {filaPersonaje - radio, columnaPersonaje - radio};
    int arribaDerecha[2] = {filaPersonaje - radio, columnaPersonaje + radio};

    corregirRangos(arribaDerecha, arribaIzquierda, abajoDerecha, abajoIzquierda);
    mostrarRangoRadial(abajoIzquierda , abajoDerecha, arribaIzquierda , arribaDerecha );
    tablero->ingresarCoordenadas(filaElegida,columnaElegida);

    bool esMismaCasilla = (filaPersonaje == filaElegida && columnaPersonaje == columnaElegida);

    if (!esMismaCasilla) {
        enRangoArriba = filaElegida >= arribaIzquierda[0];//QUE NO SEA MAYOR QUE LAS FILAS DE ARRIBA

        enRangoAbajo = filaElegida <= abajoDerecha[0];// QUE NO SEA MENOR QUE LAS FILAS DE ABAJO

        enRangoIzquierda = columnaElegida >= abajoIzquierda[1];// QUE NO SEA MENOR QUE LAS COLUMNAS DE LA IZQUIERDA

        enRangoDerecha = columnaElegida <= arribaDerecha[1];//QUE NO SEA MAYOR QUE LAS COLUMNAS DE LA DERECHA
    } else {
        error = MISMO_CASILLERO_QUE_ATACANTE;
    }

    return (!esMismaCasilla && ( enRangoArriba && enRangoAbajo && enRangoIzquierda && enRangoDerecha ) );
}

void Rangos::corregirRangos(int *arribaDerecha, int *arribaIzquierda, int *abajoDerecha, int *abajoIzquierda) {
    int primerFila = 1;
    int primerColumna = 1;
    int ultimaFila = tablero->getAlto();
    int ultimaColumna = tablero->getAncho();


    if (abajoDerecha[0] > ultimaFila) {
        abajoIzquierda[0] = ultimaFila;
        abajoDerecha[0] = ultimaFila;
    }
    if (arribaIzquierda[0] < primerFila) {
        arribaIzquierda[0] = primerFila;
        arribaDerecha[0] = primerFila;
    }
    if (abajoDerecha[1] > ultimaColumna) {
        abajoDerecha[1] = ultimaColumna;
        arribaDerecha[1] = ultimaColumna;
    }
    if (arribaIzquierda[1] < primerColumna) {
        arribaIzquierda[1] = primerFila;
        abajoIzquierda[1] = primerFila;
    }
}


bool Rangos::estaEnRangoRadioFlor(int filaAtacante, int columnaAtacante , int &filaElegida, int &columnaElegida, Accion &error, Ser* personaje) {
    int arriba[2] = {filaAtacante-1 , columnaAtacante};
    int abajo[2] = { filaAtacante+1 , columnaAtacante};
    int izquierda[2] = {filaAtacante , columnaAtacante-1};
    int derecha[2] = {filaAtacante , columnaAtacante+1};

    bool estaEnRango = false;

    corregirRangoFlor(arriba,abajo,izquierda,derecha);

    if (!personaje->esZombi()) {
        mostrarRangoFlor(arriba,abajo,izquierda,derecha);
        tablero->ingresarCoordenadas(filaElegida, columnaElegida);
        bool esMismaCasilla = (filaAtacante == filaElegida && columnaAtacante == columnaElegida);

        if (!esMismaCasilla) {
            if (filaElegida == arriba[0] && columnaElegida == arriba[1]) {
                estaEnRango = true;
            } else if (filaElegida == abajo[0] && columnaElegida == abajo[1]) {
                estaEnRango = true;
            } else if (filaElegida == izquierda[0] && columnaElegida == izquierda[1]) {
                estaEnRango = true;
            } else if (filaElegida == derecha[0] && columnaElegida == derecha[1]) {
                estaEnRango = true;
            }
        } else {
            error = MISMO_CASILLERO_QUE_ATACANTE;
        }

    } else if (hayHumanoAlrededorZombi(arriba,abajo,izquierda,derecha)){
        coordenadasAtaqueAleatorioZombi(filaAtacante,columnaAtacante,filaElegida,columnaElegida,arriba,abajo,izquierda,derecha,personaje);
        estaEnRango = true;
    } else {
        error = ZOMBI_NO_TIENE_QUIEN_ATACAR_ALEATORIAMENTE;
    }
    return estaEnRango;
}


void Rangos::corregirRangoFlor(int *arriba, int *abajo, int *izquierda, int *derecha) {
    int primerFila = 1;
    int primerColumna = 1;
    int ultimaFila = tablero->getAlto();
    int ultimaColumna = tablero->getAncho();
    if (arriba[0] < primerFila){
        arriba[0] = primerFila;
    }
    if (abajo[0] > ultimaFila) {
        abajo[0] = ultimaFila;
    }
    if (izquierda[1] < primerColumna) {
        izquierda[1] = primerColumna;
    }
    if (derecha[1] > ultimaColumna) {
        derecha[1] = ultimaColumna;
    }
}

void Rangos::coordenadasAtaqueAleatorioZombi(int filaAtacante , int columnaAtacante , int &filaElegida, int &columnaElegida, int *arriba, int *abajo,int *izquierda, int *derecha, Ser* personaje) {
    Accion errorFlag;

    bool esMismaCasilla;
    do {
        int posicionAleatoria = Utiles::buscarNumeroAleatorio(1, 4);
        switch (posicionAleatoria) {
            case ALEATORIO_ARRIBA:
                filaElegida = arriba[0];
                columnaElegida = arriba[1];
                break;
            case ALEATORIO_ABAJO:
                filaElegida = abajo[0];
                columnaElegida = abajo[1];
                break;
            case ALEATORIO_IZQUIERDA:
                filaElegida = izquierda[0];
                columnaElegida = izquierda[1];
                break;
            case ALEATORIO_DERECHA:
                filaElegida = derecha[0];
                columnaElegida = derecha[1];
                break;
        }
        esMismaCasilla = (filaAtacante == filaElegida && columnaAtacante == columnaElegida);
    } while (esMismaCasilla || !tablero->hayQuienAtacarDefender(personaje,errorFlag,filaElegida,columnaElegida,ATAQUE));
}

bool Rangos::hayHumanoAlrededorZombi(int *arriba, int *abajo, int *izquierda, int *derecha) {
    bool hayArriba = false, hayAbajo = false , hayIzquierda = false , hayDerecha = false;
    if (tablero->devolverCasillero(arriba[0],arriba[1])->tieneSer()) {
        hayArriba = dynamic_cast<Ser *>(tablero->devolverCasillero(arriba[0],arriba[1])->devolverSer())->esHumano();
    }
    if (tablero->devolverCasillero(abajo[0],abajo[1])->tieneSer()) {
        hayAbajo = dynamic_cast<Ser *>(tablero->devolverCasillero(abajo[0],abajo[1])->devolverSer())->esHumano();
    }
    if (tablero->devolverCasillero(izquierda[0],izquierda[1])->tieneSer()){
        hayIzquierda = dynamic_cast<Ser *>(tablero->devolverCasillero(izquierda[0],izquierda[1])->devolverSer())->esHumano();
    }
    if (tablero->devolverCasillero(derecha[0],derecha[1])->tieneSer()){
        hayDerecha = dynamic_cast<Ser *>(tablero->devolverCasillero(derecha[0],derecha[1])->devolverSer())->esHumano();
    }
    return (hayArriba || hayAbajo || hayIzquierda || hayDerecha);
}

void Rangos::mostrarRangoRadial(int *abajoIzquierda, int *abajoDerecha, int *arribaIzquierda, int *arribaDerecha) {
    cout << endl << "EL RANGO ES:" << endl;
    cout << "[ " << arribaIzquierda[0] << " , " << arribaIzquierda[1] << " ]" << " --- "
         << "[ " << arribaDerecha[0] << " , " << arribaDerecha[1] << " ]" << endl;
    cout << "||                  ||"<< endl;
    cout << "||                  ||"<< endl;
    cout << "[ " << abajoIzquierda[0] << " , " << abajoIzquierda[1] << " ]" << " --- "
         << "[ " << abajoDerecha[0] << " , " << abajoDerecha[1] << " ]" << endl;
}

void Rangos::mostrarRangoFlor(int *arriba, int *abajo, int *izquierda, int *derecha) {
    cout << endl << "EL RANGO ES:" << endl;
    cout << "     [ " << arriba[0] << " , " << arriba[1] << " ]" << endl;
    cout << "[ " << izquierda[0] << " , " << izquierda[1] << " ]\t"
         << "[ " << derecha[0] << " , " << derecha[1] << " ]" << endl;
    cout << "     [ " << abajo[0] << " , " << abajo[1] << " ]" << endl;
}

Rangos::~Rangos() {
    tablero = nullptr;
}