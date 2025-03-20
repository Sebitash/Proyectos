#include "Juego.h"
#include "Constantes.h"


Juego::Juego() {
    tablero = nullptr;
    ingresarMenuPrincipal();
}

void Juego::mostrarOpcionesMenuPrincipal() {
    Utiles::limpiarPantalla();
    ImpresionesPantalla::impresionJuego();
}

void Juego::ingresarMenuPrincipal() {
    string input;
    int opcion = 0;
    bool finalDeEjecucion = false;

    while (opcion != SALIR_MENU_PRINCIPAL && !finalDeEjecucion) {
        mostrarOpcionesMenuPrincipal();
        cin >> input;
        cout << endl;
        cout << endl;
        opcion = Utiles::ingresoValido(input, 1, 3);
        Utiles::limpiarPantalla();
        if (opcion == JUGAR) {
            comenzar(finalDeEjecucion);
        } else if (opcion == CREDITOS) {
            Utiles::limpiarPantalla();
            ImpresionesPantalla::impresionCreditos();
            Utiles::botonContinuar();
            Utiles::limpiarPantalla();
        }
    }
    Utiles::limpiarPantalla();
    ImpresionesPantalla::impresionSalir();
}

void Juego::comenzar(bool &finalDeEjecucion) {
    LectorArchivo archivoTablero(ARCHIVO_TABLERO);
    tablero = new Tablero(archivoTablero);
    bool seGuardaPartida = false, finalDeJuego = false;

    if (Utiles::archivoExistente(ARCHIVO_CARGAR_PARTIDA)) {
        cargarPartida(seGuardaPartida,finalDeJuego);
    } else {
        empezarPartidaNueva();
    }

    if (!seGuardaPartida || !finalDeJuego) {
        MenuJuego menu;
        menu.mostrar(tablero,seGuardaPartida,finalDeJuego);
    }

    if (finalDeJuego || seGuardaPartida){
        finalDeEjecucion = true;
    }
}

void Juego::empezarPartidaNueva() {
    LectorArchivo archivoEstadoInicial(ARCHIVO_ESTADO_INICIAL);
    this->tablero->rellenar(archivoEstadoInicial);
}

void Juego::cargarPartida(bool &seGuardaPartida, bool &finalDeJuego) {
    Simulacion simulacion(tablero, CARGAR_PARTIDA,finalDeJuego,seGuardaPartida);

    LectorArchivo archivoCargar(ARCHIVO_CARGAR_PARTIDA);

    string palabra;

    bool cargaPrimerJugador = true;
    int numeroJugador;

    palabra = archivoCargar.leerLinea();
    numeroJugador = stoi(palabra);

    while (!archivoCargar.esFinalArchivo()) {

        for (int indiceVectorJugadores = 0; indiceVectorJugadores < 2; indiceVectorJugadores++) {
            string linea = archivoCargar.leerLinea();
            istringstream iss(linea);
            iss >> palabra;
            simulacion.setNombreJugador(setNumeroJugador(numeroJugador, cargaPrimerJugador), indiceVectorJugadores);
            simulacion.setBando(palabra, indiceVectorJugadores);
            iss >> palabra;
            simulacion.cargarCantidadPersonajes(indiceVectorJugadores, stoi(palabra));
            simulacion.getJugador(indiceVectorJugadores)->setVectorIDs();
            cargarPersonajesJugador(archivoCargar, palabra, simulacion, indiceVectorJugadores, iss);
            cargaPrimerJugador = false;
        }
        cargarDatosTablero(archivoCargar, palabra);
    }
    simulacion.setTablero(tablero);
    simulacion.setDiccionario(tablero->getDiccionario());
    simulacion.comenzarSimulacion(false, seGuardaPartida,finalDeJuego);
}

int Juego::setNumeroJugador(int numeroPrimerJugador, bool cargaPrimerJugador) {
    int numeroJugadorActual;
    if (!cargaPrimerJugador) {
        if (numeroPrimerJugador == 1) {
            numeroJugadorActual = 2;
        } else {
            numeroJugadorActual = 1;
        }
    } else {
        numeroJugadorActual = numeroPrimerJugador;
    }
    return numeroJugadorActual;
}

void Juego::cargarDatosTablero(LectorArchivo &archivoCargar, string &palabra) {
    string linea = archivoCargar.leerLinea();
    istringstream iss(linea);
    iss >> palabra;
    iss >> palabra;
    int cantidadItems = stoi(palabra);
    int id, fila, columna, cantidad;
    string segundaPalabra, nombre;

    for (int i = 0; i < cantidadItems; i++) {
        string linea = archivoCargar.leerLinea();
        istringstream iss(linea);
        iss >> palabra;
        iss >> segundaPalabra;

        nombre = archivoCargar.procesarNombreObjeto(palabra, iss, segundaPalabra);
        id = stoi(segundaPalabra);

        iss >> palabra;
        cantidad = stoi(palabra);
        iss >> palabra;
        archivoCargar.procesarCoordenadas(palabra, fila, columna, iss);

        this->tablero->agregarObjeto(nombre, fila, columna, cantidad, id);
    }
}

void
Juego::cargarPersonajesJugador(LectorArchivo &archivoCargar, string &palabra, Simulacion &simulacion, int indiceJugador,
                               istringstream &iss) const {
    string segundaPalabra, nombre;
    int id, fila, columna;
    float armadura, fuerza, vida, energia;
    int cantidadPersonajes = simulacion.getJugador(indiceJugador)->getCantidadPersonajes();

    for (int i = 0; i < cantidadPersonajes; i++) {
        string linea = archivoCargar.leerLinea();
        istringstream iss(linea);
        iss >> palabra;
        iss >> segundaPalabra;
        nombre = archivoCargar.procesarNombreObjeto(palabra, iss, segundaPalabra);

        id = stoi(segundaPalabra);
        archivoCargar.procesarAtributosPersonaje(palabra, iss, armadura, fuerza, vida, energia);
        iss >> palabra;
        archivoCargar.procesarCoordenadas(palabra, fila, columna, iss);

        unsigned int cantAgua = 0, cantEstacas = 0, cantBalas = 0, cantCruces = 0;
        bool tieneEscopeta = false;
        archivoCargar.procesarDatosInventario(palabra, iss, cantAgua, cantCruces, cantEstacas, cantBalas,
                                              tieneEscopeta);

        // Cantidad = 1 porque son seres
        this->tablero->agregarSer(nombre, fila, columna, 1, id, vida, armadura, fuerza, energia);
        dynamic_cast<Ser *>(this->tablero->devolverObjetoEnCasillero(fila, columna))->guardarEnInventario(cantAgua,cantCruces,cantEstacas,cantBalas,tieneEscopeta);
        simulacion.setPersonajeBando(id, simulacion.getJugador(indiceJugador)->getBando());
    }

}


Juego::~Juego() {
    delete tablero;
}
