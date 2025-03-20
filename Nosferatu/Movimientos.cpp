#include "Movimientos.h"
#include "Constantes.h"

Movimientos::Movimientos(Tablero *tablero) {
    this->tablero = tablero;
}


void Movimientos::moverPersonaje(Ser *personaje, bool &ejecucionExitosa) {
    ejecucionExitosa = false;
    Accion error;
    int filaFin, columnaFin;
    int filaInicio = personaje->obtenerFila() + 1;
    int columnaInicio = personaje->obtenerColumna() + 1;
    tablero->ingresarCoordenadas(filaFin, columnaFin);

    if (!(filaInicio == filaFin && columnaInicio == columnaFin)) {

        Grafo *grafo = new Grafo(tablero);
        int energiaPersonaje = (int) personaje->obtenerEnergia();
        grafo->definirCamino(filaInicio, columnaInicio, filaFin, columnaFin);
        int costoCamino = grafo->caminosMinimos();

        if (costoCamino == INFINITO || costoCamino > energiaPersonaje) {
            if (costoCamino == INFINITO) {
                error = NO_PUEDE_MOVERSE_COSTO_INFINITO;
            } else {
                error = SIN_ENERGIA_MOVERSE;
                cout << "Se necesita " << costoCamino << " de energía para llegar! ";
            }
        } else {
            actualizarPosicionPersonaje(grafo, filaInicio, columnaInicio);
            ejecucionExitosa = true;
        }
        delete grafo;
    } else {
        error = MISMA_CASILLA_QUE_ESTOY_PARA_MOVERSE;
    }
    if (!ejecucionExitosa) {
        Utiles::mostrarError(error);
    }
}

void Movimientos::actualizarPosicionPersonaje(Grafo *grafo, int filaInicio, int columnaInicio) {
    int largoRecorrido = grafo->devolverLargoRecorrido();
    Coordenadas *coordenadas = grafo->devolverRecorrido();
    int filaActual = filaInicio;
    int columnaActual = columnaInicio;
    int filaCasilleroSiguiente, columnaCasilleroSiguiente;
    Ser *personaje, *personajeEnMovimiento;
    personaje = dynamic_cast<Ser *>(tablero->devolverCasillero(filaInicio, columnaInicio)->devolverSer());;

    cout << endl << "El costo del recorrido es de " << grafo->getCostoCamino() << " de energía." << endl;
    grafo->mostrarRecorrido();
    personaje->disminuirEnergia(grafo->getCostoCamino());
    Utiles::dormir(3);
    cout << endl;

    for (int i = 1; i < largoRecorrido; i++) {
        Utiles::limpiarPantalla();
        tablero->mostrar();

        filaCasilleroSiguiente = coordenadas[i].getFila();
        columnaCasilleroSiguiente = coordenadas[i].getColumna();

        personajeEnMovimiento = dynamic_cast<Ser *>(tablero->devolverCasillero(filaActual, columnaActual)->devolverSer());
        Casillero *casilleroActual = tablero->devolverCasillero(filaActual, columnaActual);
        Casillero *casilleroSiguiente = tablero->devolverCasillero(filaCasilleroSiguiente, columnaCasilleroSiguiente);

        casilleroSiguiente->agregarSer(personaje);

        agarrarItem(casilleroSiguiente);

        casilleroActual->liberarPunteroSer();

        tablero->devolverCasillero(filaCasilleroSiguiente, columnaCasilleroSiguiente)->devolverSer()->setFila(
                filaCasilleroSiguiente - 1);
        tablero->devolverCasillero(filaCasilleroSiguiente, columnaCasilleroSiguiente)->devolverSer()->setColumna(
                columnaCasilleroSiguiente - 1);

        filaActual = filaCasilleroSiguiente;
        columnaActual = columnaCasilleroSiguiente;

        Utiles::dormir(1);
    }
    tablero->mostrar();


    delete[] coordenadas;
}

void Movimientos::agarrarItem(Casillero *casillero) {
    if (casillero->tieneItem()) {
        if (dynamic_cast<Ser *>(casillero->devolverSer())->esHumano()) {
            agarrarParaHumanos(casillero);
        } else {
            agarrarParaMonstruos(casillero);
        }
    }
}

void Movimientos::agarrarParaHumanos(Casillero *casillero) {
    char elemento = casillero->devolverItem()->obtenerNombreMapa();
    Ser *personaje = dynamic_cast<Ser *>(casillero->devolverSer());
    if (elemento == LETRA_ESCOPETA) {
        if (!personaje->getInventario()->getEscopeta()) {
            personaje->getInventario()->setEscopeta();
            imprimirItemAgarrado(elemento);
            casillero->eliminarItem();
        }

    } else {
        int cantidad = devolverCantidadItemNuevo(casillero, elemento);
        insertarElementoInventario(personaje, cantidad, elemento);
        imprimirItemAgarrado(elemento);
        casillero->eliminarItem();

    }
}

void Movimientos::insertarElementoInventario(Ser *personaje, int cantidad, char elemento) {
    personaje->getInventario()->aumentarElemento(cantidad, elemento);
}

int Movimientos::devolverCantidadItemNuevo(Casillero *casillero, char nombreElemento) {
    ;
    Elemento *elemento = dynamic_cast<Elemento *>(casillero->devolverItem());
    int cantidad = elemento->devolverCantidad();
    return cantidad;
}

void Movimientos::agarrarParaMonstruos(Casillero *casillero) {
    Gotoxy gotox;
    char elemento = casillero->devolverItem()->obtenerNombreMapa();
    Ser *personaje = dynamic_cast<Ser *>(casillero->devolverSer());
    if ((elemento == LETRA_ESTACA) && (personaje->esVampiroGeneral())) {
        destruirEstaca(casillero);
        cout << gotox.pos(26, 74) << "Se ha destruído una estaca! ";
    } else if ((elemento == LETRA_AGUA) && (personaje->esZombi())) {
        int cantidadAgua = devolverCantidadItemNuevo(casillero, elemento);
        personaje->getInventario()->aumentarElemento(cantidadAgua, elemento);
        casillero->eliminarItem();
        cout << gotox.pos(26, 74) << "El zombi agarró un agua Bendita";
    }

}

void Movimientos::destruirEstaca(Casillero *casillero) {
    tablero->eliminarItem(casillero->devolverItem()->obtenerFila() + 1,
                          casillero->devolverItem()->obtenerColumna() + 1);
}

void Movimientos::imprimirItemAgarrado(char elemento) {
    Gotoxy gotox;
    if (elemento == LETRA_BALA) {
        cout << gotox.pos(26, 74) << "Se agarraron balas";
    } else if (elemento == LETRA_ESTACA) {
        cout << gotox.pos(26, 74) << "Se agarraro una estaca";
    } else if (elemento == LETRA_ESCOPETA) {
        cout << gotox.pos(26, 74) << "Se agarro una escopeta";
    } else if (elemento == LETRA_AGUA) {
        cout << gotox.pos(26, 74) << "Se agarraro agua bendita";
    } else if (elemento == LETRA_CRUZ) {
        cout << gotox.pos(26, 74) << "Se agarro una cruz" << endl;
    }
}

Movimientos::~Movimientos() {
    tablero = nullptr;
}