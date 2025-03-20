#include "Grafo.h"


Grafo::Grafo(Tablero* tablero) {
    this->tablero = tablero;
    cantColumnas = tablero->getAncho();
    cantFilas = tablero->getAlto();
    cantCasilleros = cantFilas * cantColumnas;
    recorrido = nullptr;
    crearVectores();
    inicializarVectores();
}

void Grafo::definirCamino(int filaInicio, int columnaInicio, int filaDestino, int columnaDestino) {
    casilleroInicio = tablero->devolverCasillero(filaInicio, columnaInicio);
    casilleroDestino = tablero->devolverCasillero(filaDestino, columnaDestino);
    this->filaInicio = filaInicio;
    this->columnaInicio = columnaInicio;
    this->filaActual = filaInicio;
    this->columnaActual = columnaInicio;
    this->filaDestino = filaDestino;
    this->columnaDestino = columnaDestino;
    personaje = (casilleroInicio->devolverSer() ) -> obtenerNombreMapa();
}

int Grafo::caminosMinimos() {

    distancias[filaInicio-1][columnaInicio-1] = 0;
    int costoAcum;

    if (casilleroDestinoLibre()) {
        for (int i=0 ; i < cantCasilleros; i++) {
            costoAcum = distancias[filaActual-1][columnaActual-1]; //CasilleroActual - posicion en vectores

            revisarTablero(ARRIBA,-1,0,costoAcum);
            revisarTablero(ABAJO,1,0,costoAcum);
            revisarTablero(IZQUIERDA,0,-1,costoAcum);
            revisarTablero(DERECHA,0,1,costoAcum);

            visitados[filaActual-1][columnaActual-1] = true;

            cambiarCasilleroActual();
        }
        obtenerRecorrido();
    }
    costoCaminoMinimo = distancias[filaDestino-1][columnaDestino-1];
    return costoCaminoMinimo;
}

Coordenadas* Grafo::devolverRecorrido() {
    Coordenadas* nuevoRecorrido = new Coordenadas[cantCasillerosVisitados+1];
    for (int i = 0 ; i <= cantCasillerosVisitados ; i++){
        nuevoRecorrido[i] = recorrido[i];
    }
    return nuevoRecorrido;
}

int Grafo::devolverLargoRecorrido() {
    return (cantCasillerosVisitados+1);
}

void Grafo::mostrarRecorrido() {
    if (casilleroDestinoLibre()) {
        cout << endl;
        recorrido[0].mostrarCoordenadas();
        for (int i = 1 ; i <= cantCasillerosVisitados ; i++){
            if (i==10)
                cout << endl;
            cout << " --> ";
            recorrido[i].mostrarCoordenadas();
        }
        cout << endl;
        cout << "Se pasa por " << cantCasillerosVisitados << " casillero/s." << endl;
    } else {
        cout << endl << "No hay recorrido posible" << endl;
    }
}

void Grafo::crearVectores() {
    distancias = new int*[cantFilas];
    visitados = new bool*[cantFilas];
    predecesores = new Coordenadas*[cantFilas];

    for (int i = 0 ; i < cantFilas ; i++){
        distancias[i] = new int[cantColumnas];
        visitados[i] = new bool[cantColumnas];
        predecesores[i] = new Coordenadas[cantColumnas];
    }
}

void Grafo::inicializarVectores() {
    for (int f = 0; f < cantFilas; f++) {
        for (int c = 0; c < cantColumnas; c++) {
            distancias[f][c] = INFINITO;
            visitados[f][c] = false;
        }
    }
}


int Grafo::costo(Direccion casilleroARevisar) {
    int costoCasillero;

    if (casilleroARevisar == ARRIBA) {
        costoCasillero = tablero->devolverCasillero(filaActual-1,columnaActual) -> obtenerCosto(personaje);
    }
    else if (casilleroARevisar == ABAJO) {
        costoCasillero = tablero->devolverCasillero(filaActual+1,columnaActual) -> obtenerCosto(personaje);
    }
    else if (casilleroARevisar == IZQUIERDA) {
        costoCasillero = tablero->devolverCasillero(filaActual,columnaActual-1) -> obtenerCosto(personaje);
    }
    else { //DERECHA
        costoCasillero = tablero->devolverCasillero(filaActual,columnaActual+1) -> obtenerCosto(personaje);
    }

    return costoCasillero;
}


void Grafo::revisarTablero(Direccion direccionARevisar, int variacionFila, int variacionColumna, int costoAcum) {
    if (hayCasillero(direccionARevisar) && !(haySer(direccionARevisar)) && costoAcum + costo(direccionARevisar) < distancias[filaActual-1+variacionFila][columnaActual-1+variacionColumna]) {
        distancias[filaActual-1+variacionFila][columnaActual-1+variacionColumna] = costoAcum + costo(direccionARevisar);

        //ACA SE CAMBIA EL VALOR DEL VALOR EN PREDECESORES
        predecesores[filaActual-1+variacionFila][columnaActual-1+variacionColumna].setCoordenadas(filaActual,columnaActual);
        int cantidadVisitadaActual = predecesores[filaActual-1][columnaActual-1].getCantidadCasillerosVisitados();
        predecesores[filaActual-1+variacionFila][columnaActual-1+variacionColumna].incrementarCasillerosVisitados(cantidadVisitadaActual);
    }
}

Coordenadas Grafo::devolverPredecesor(int fila, int columna) {
    return predecesores[fila-1][columna-1];
}

bool Grafo::casilleroDestinoLibre() {
    return !(casilleroDestino->tieneSer());
}

bool Grafo::hayCasillero(Direccion direccion) {
    return (
            (direccion == ARRIBA && filaActual >= 2) ||
            (direccion == ABAJO && filaActual <= cantFilas - 1 ) ||
            (direccion == IZQUIERDA && columnaActual >= 2) ||
            (direccion == DERECHA && columnaActual <= cantColumnas - 1)
            );
}

bool Grafo::haySer(Direccion direccion) {
    return (
            (direccion == ARRIBA && tablero->devolverCasillero(filaActual - 1, columnaActual)->tieneSer() ) ||
            (direccion == ABAJO && tablero->devolverCasillero(filaActual + 1, columnaActual)->tieneSer() ) ||
            (direccion == IZQUIERDA && tablero->devolverCasillero(filaActual, columnaActual - 1)->tieneSer() ) ||
            (direccion == DERECHA && tablero->devolverCasillero(filaActual, columnaActual + 1)->tieneSer() )
    );
}

void Grafo::cambiarCasilleroActual() {
    //Busco de los nodos no visitados cual tiene menor peso en distancias
    int costoMenor = INFINITO+1;

    for (int f = 0; f < cantFilas; f++) {
        for (int c = 0; c < cantColumnas; c++) {
            if ( !visitados[f][c] && distancias[f][c] < costoMenor) {
                costoMenor = distancias[f][c];
                filaActual = f+1;
                columnaActual = c+1;
            }
        }
    }
}

void Grafo::obtenerRecorrido() {
    Coordenadas predecesor;
    cantCasillerosVisitados = predecesores[filaDestino-1][columnaDestino-1].getCantidadCasillerosVisitados();
    filaActual = filaDestino;
    columnaActual = columnaDestino;


    if (cantCasillerosVisitados != 0) {
        recorrido = new Coordenadas[cantCasillerosVisitados+1];
        recorrido[cantCasillerosVisitados] = Coordenadas(filaActual,columnaActual,cantCasillerosVisitados);
        for (int i = cantCasillerosVisitados-1  ; i >= 0 ; i--) {

            predecesor = devolverPredecesor(filaActual,columnaActual);
            recorrido[i] = predecesor;
            filaActual = predecesor.getFila();
            columnaActual = predecesor.getColumna();

            // Se fija el predecesor de fila actual y columna actual
            // Lo guardas en el vector
            // Moves la fila actual a ese predecesor
        }
    } else {
        recorrido = nullptr;
    }
}

int Grafo::getCostoCamino() {
    return costoCaminoMinimo;
}

void Grafo::mostrarVectores() { // Mantuvimos este metodo a modo de debug :)
    cout << endl << "DISTANCIAS" << endl << "[ ";
    for (int f = 0; f < cantFilas; f++) {
        for (int c = 0; c < cantColumnas; c++) {
            cout << setw(7) << distancias[f][c] << " ";
        }
        cout << endl << "  ";
    }
    cout << endl << "VISITADOS" << endl << "[ ";
    for (int f = 0; f < cantFilas; f++) {
        for (int c = 0; c < cantColumnas; c++) {
            cout << setw(7) << visitados[f][c] << " ";
        }
        cout << endl << "  ";
    }
    cout << endl << "PREDECESORES" << endl << "[ ";
    for (int f = 0; f < cantFilas; f++) {
        for (int c = 0; c < cantColumnas; c++) {
            cout << setw(7);
            predecesores[f][c].mostrarCoordenadas();
            cout << " ";
        }
        cout << endl << "  ";
    }
    cout << endl;
}


Grafo::~Grafo() {
    tablero = nullptr;
    for (int i = 0 ; i < cantFilas ; i++){
        delete [] distancias[i];
        delete [] visitados[i];
        delete [] predecesores[i];
    }
    delete [] predecesores;
    delete [] distancias;
    delete [] visitados;
    delete [] recorrido;
}
