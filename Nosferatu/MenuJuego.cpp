#include "MenuJuego.h"
#include "Grafo.h"
#include "Constantes.h"
#include "Simulacion.h"

enum OPCIONES_MENU_INICIAL {
    ALTA_OBJETO = 1,
    BAJA_OBJETO = 2,
    MOSTRAR_TABLERO_MENU_INICIAL = 3,
    BUSCAR_POR_CUADRANTE = 4,
    BUSCAR_POR_ID_MENU_INICIAL = 5,
    SIMULACION = 6,
    SALIR_MENU_INICIAL = 7,
};

static const int OPCION_MAXIMA_MENU_JUEGO = 7;
static const int OPCION_MAXIMA_OBJETOS = 12;


MenuJuego::MenuJuego() { }

void MenuJuego::mostrar(Tablero *tablero, bool &seGuardaPartida, bool &finalDeJuego) {
    string opcionElegida;
    int opcion;
    while (opcionElegida != "7" && !seGuardaPartida && !finalDeJuego) {
        Utiles::limpiarPantalla();
        imprimirOpciones();
        cin >> opcionElegida;
        cout << endl;
        cout << endl;

        opcion = Utiles::ingresoValido(opcionElegida, OPCION_MINIMA, OPCION_MAXIMA_MENU_JUEGO);

        realizarAccion(tablero, opcion,finalDeJuego,seGuardaPartida);
    }
}

void MenuJuego::realizarAccion(Tablero *&tablero, int opcion, bool &finalDeJuego,bool &seGuardaPartida) {
    switch (opcion) {
        case (ALTA_OBJETO):
            Utiles::limpiarPantalla();
            agregarObjeto(tablero);
            break;
        case (BAJA_OBJETO):
            Utiles::limpiarPantalla();
            eliminarObjeto(tablero);
            break;
        case (MOSTRAR_TABLERO_MENU_INICIAL): {
            Utiles::limpiarPantalla();
            tablero->mostrar();
            ImpresionesPantalla::impresionTituloTablero();
            Utiles::botonContinuar();
            break; }
        case (BUSCAR_POR_CUADRANTE):
            Utiles::limpiarPantalla();
            buscarPorCuadrante(tablero);
            break;
        case (BUSCAR_POR_ID_MENU_INICIAL):{
            Utiles::limpiarPantalla();
            Arbol* arbol = tablero->getDiccionario();
            buscarPorID(arbol);
            break;
        }
        case (SIMULACION):
            Utiles::limpiarPantalla();
            Simulacion simulacion(tablero,NUEVA_PARTIDA,finalDeJuego,seGuardaPartida);
            break;
    }
}


void MenuJuego::agregarObjeto(Tablero *&tablero) {
    string eleccionUsuario, nombre, cantidad = "1";
    int fila, columna, id, opcion;
    ImpresionesPantalla::impresionTituloAltaObjeto();
    imprimirOpcionObjetos();
    cin >> eleccionUsuario;

    opcion = Utiles::ingresoValido(eleccionUsuario, OPCION_MINIMA, OPCION_MAXIMA_OBJETOS);

    id = obtenerIDAleatorioObjeto(opcion);
    ingresarCoordenadas(fila, columna, tablero->getAlto(), tablero->getAncho());
    if(!(tablero->devolverCasillero(fila, columna)->tieneItem()) && !(tablero->devolverCasillero(fila, columna)->tieneSer())){
        nombre = obtenerNombreTipoObjeto(opcion);

        ingresarCantidadObjeto(opcion, cantidad);

        tablero->agregarObjeto(nombre, fila, columna, stoi(cantidad), id);
        cout << "\nSE AGREGO EL OBJETO CON EXITO" << endl;

    }
    else{
        cout<< "\nEN ESA UBICACION YA HAY UN OBJETO" << endl;
    }
    Utiles::botonContinuar();
}

void MenuJuego::eliminarObjeto(Tablero *&tablero) {
    int fila, columna;
    ImpresionesPantalla::impresionTituloBajaObjeto();
    ingresarCoordenadas(fila, columna, tablero->getAlto(), tablero->getAncho());

    if (!tablero->hayObjetoEnCasillero(fila, columna)) {
        cout << "No se encuentra ningun objeto en ese casillero" << endl;
    } else {
        if(tablero->devolverCasillero(fila, columna)->tieneSer()){
            tablero->eliminarObjeto(fila, columna);

        }
        else{
            tablero->eliminarItem(fila, columna);
        }
        cout << "\nSE ELIMINO EL OBJETO CON EXITO" << endl;
    }
    Utiles::botonContinuar();
}

void MenuJuego::ingresarCantidadObjeto(int opcion, string &cantidad) const {
    if (opcion == AGUA || opcion == BALA) {
        cout << "Ingrese la cantidad que desea agregar: ";
        cin >> cantidad;
        while (! Utiles::esStringNumerico(cantidad) || stoi(cantidad) < 0) {
            cout << "Ingreso invalido" << endl;
            cin >> cantidad;
        }
    }
}

string MenuJuego::obtenerNombreTipoObjeto(int opcionIngresada) {
    string nombre;
    switch (opcionIngresada) {
        case HUMANO:
            nombre = NOMBRE_HUMANO; break;
        case VAMPIRO:
            nombre = NOMBRE_VAMPIRO; break;
        case ZOMBI:
            nombre = NOMBRE_ZOMBI; break;
        case ESTACA:
            nombre = NOMBRE_ESTACA; break;
        case ESCOPETA:
            nombre = NOMBRE_ESCOPETA; break;
        case CRUZ:
            nombre = NOMBRE_CRUZ; break;
        case AGUA:
            nombre = NOMBRE_AGUA; break;
        case BALA:
            nombre = NOMBRE_BALA; break;
        case VANESA:
            nombre = NOMBRE_VANESA; break;
        case VAMPIRELLA:
            nombre = NOMBRE_VAMPIRELLA; break;
        case NOSFERATU:
            nombre = NOMBRE_NOSFERATU; break;
        default:
            nombre = ""; break;
    }
    return nombre;
}

int MenuJuego::obtenerIDAleatorioObjeto(int opcionObjeto) {
    int id = 1;
    switch (opcionObjeto) {
        case (HUMANO):
            id = Utiles::buscarNumeroAleatorio(ID_HUMANO_MINIMO, ID_HUMANO_MAXIMO);
            break;
        case (CV):
            id = Utiles::buscarNumeroAleatorio(ID_CAZADOR_MINIMO, ID_CAZADOR_MAXIMO);
            break;
        case (VANESA):
            id = ID_VANESA;
            break;
        case (VAMPIRELLA):
            id = ID_VAMPIRELLA;
            break;
        case (VAMPIRO):
            id = Utiles::buscarNumeroAleatorio(ID_VAMPIROS_MINIMO, ID_VAMPIROS_MAXIMO);
            break;
        case (NOSFERATU):
            id = ID_NOSFERATU;
            break;
        case (ZOMBI):
            id = Utiles::buscarNumeroAleatorio(ID_ZOMBIES_MINIMO, ID_ZOMBIES_MAXIMO);
            break;
        case (AGUA):
            id = Utiles::buscarNumeroAleatorio(ID_AGUA_MINIMO, ID_AGUA_MAXIMO);
            break;
        case (BALA):
            id = Utiles::buscarNumeroAleatorio(ID_BALAS_MINIMO, ID_BALAS_MAXIMO);
            break;
        case (ESTACA):
            id = Utiles::buscarNumeroAleatorio(ID_ESTACAS_MINIMO, ID_ESTACAS_MAXIMO);
            break;
        case (ESCOPETA):
            id = Utiles::buscarNumeroAleatorio(ID_ESCOPETAS_MINIMO, ID_ESCOPETAS_MAXIMO);
            break;
        case (CRUZ):
            id = Utiles::buscarNumeroAleatorio(ID_CRUCES_MINIMO, ID_CRUCES_MAXIMO);
            break;
        default:
            break;
    }
    return id;
}

void MenuJuego::imprimirOpciones() {
    ImpresionesPantalla::imprimirMenuJuego();
}

void MenuJuego::imprimirOpcionObjetos() {
    ImpresionesPantalla::impresionOpcionesObjetos();
    cout << "Ingrese el objeto: ";
}

void MenuJuego::imprimirOpcionCuadrantes() {
    ImpresionesPantalla::impresionOpcionesCuadrante();
    cout << "Ingrese el cuadrante: ";
}

void MenuJuego::buscarPorCuadrante(Tablero *&tablero) {
    string inputObjeto, inputCuadrante;
    int cuadrante, objeto;
    ImpresionesPantalla::impresionTituloBusquedaCuadrante();
    imprimirOpcionObjetos();
    cin >> inputObjeto;

    objeto = Utiles::ingresoValido(inputObjeto, 1, 12);
    Utiles::limpiarPantalla();
    ImpresionesPantalla::impresionTituloBusquedaCuadrante();
    imprimirOpcionCuadrantes();
    cin >> inputCuadrante;

    cuadrante = Utiles::ingresoValido(inputCuadrante, 1, 4);
    if (tablero->busquedaPorCuadrante(cuadrante, objeto)) {
        cout << "\nENCONTRADO" << endl;
    } else {
        cout << "\nNO ENCONTRADO" << endl;
    }

    Utiles::botonContinuar();

}

void MenuJuego::buscarPorID(Arbol *&arbol) {
    string input;
    int opcion;

    Utiles::limpiarPantalla();
    ImpresionesPantalla::impresionTituloBusquedaID();
    cout << "Ingrese el ID del objeto a buscar: " << endl;
    cin >> input;
    opcion = Utiles::ingresoValido(input, ID_MINIMO, ID_MAXIMO);
    cout << endl;


    Objeto *objeto = arbol->getDato(opcion);
    if (objeto != nullptr) {
        objeto->mostrar();
    } else {
        cout << "NO SE ENCONTRO UN OBJETO CON ESE ID" << endl;
    }

    Utiles::botonContinuar();
    Utiles::limpiarPantalla();
}

void MenuJuego::ingresarCoordenadas(int &fila, int &columna, int filaMaxima, int columnaMax) {
    string inputColumna, inputFila;
    cout << "\nFila: ";
    cin >> inputFila;
    fila = Utiles::ingresoValido(inputFila, COORDENADA_MINIMA, filaMaxima);

    cout << "\nColumna: ";
    cin >> inputColumna;

    columna = Utiles::ingresoValido(inputColumna, COORDENADA_MINIMA, columnaMax);
}
