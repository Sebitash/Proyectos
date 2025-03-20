#ifndef TP3_NOSFERATU_CONSTANTES_H
#define TP3_NOSFERATU_CONSTANTES_H

// Constantes de los nombres de los archivos
const string ARCHIVO_ESTADO_INICIAL = "../estado.txt";
const string ARCHIVO_TABLERO = "../tablero.txt";
const string ARCHIVO_CARGAR_PARTIDA = "../partida.txt";

// Constantes que definen el bando de un jugador
const string BANDO_HUMANOS = "humanos";
const string BANDO_MONSTRUOS = "monstruos";

// Constantes para cada una de las palabras que definen el tipo de objeto
const string NOMBRE_AGUA = "agua";
const string NOMBRE_CRUZ = "cruz";
const string NOMBRE_BALA = "bala";
const string NOMBRE_BALAS = "balas";
const string NOMBRE_ESCOPETA = "escopeta";
const string NOMBRE_ESTACA = "estaca";
const string NOMBRE_HUMANO = "humano";
const string NOMBRE_CAZADOR = "humano CV";
const string NOMBRE_CV = "CV";
const string NOMBRE_VANESA = "Vanesa";
const string NOMBRE_ZOMBI = "zombi";
const string NOMBRE_VAMPIRO = "vampiro";
const string NOMBRE_NOSFERATU = "Nosferatu";
const string NOMBRE_VAMPIRELLA = "Vampirella";

const int OPCION_MINIMA = 1;
const int OPCION_MAXIMA_MENU_SIMULACION = 5;

const string NUEVA_PARTIDA = "NUEVA_PARTIDA";
const string CARGAR_PARTIDA = "CARGAR";

// Constantes con los IDs maximos y minimos de cada objeto
enum ID_OBJETOS {
    ID_VANESA = 000,
    ID_NOSFERATU = 200,
    ID_VAMPIRELLA = 201,

    ID_HUMANO_MINIMO = 001,
    ID_HUMANO_MAXIMO = 49,
    ID_CAZADOR_MINIMO = 50,
    ID_CAZADOR_MAXIMO = 99,
    ID_ZOMBIES_MINIMO = 100,
    ID_ZOMBIES_MAXIMO = 199,
    ID_VAMPIROS_MINIMO = 202,
    ID_VAMPIROS_MAXIMO = 299,
    ID_AGUA_MINIMO = 300,
    ID_AGUA_MAXIMO = 319,
    ID_CRUCES_MINIMO = 320,
    ID_CRUCES_MAXIMO = 339,
    ID_ESCOPETAS_MINIMO = 340,
    ID_ESCOPETAS_MAXIMO = 359,
    ID_BALAS_MINIMO = 360,
    ID_BALAS_MAXIMO = 379,
    ID_ESTACAS_MINIMO = 380,
    ID_ESTACAS_MAXIMO = 999
};

// Constantes de los nombres de las fichas de cada objeto dentro del tablero
enum FICHAS_OBJETOS {
    LETRA_AGUA = 'A',
    LETRA_HUMANO = 'h',
    LETRA_BALA = 'b',
    LETRA_CV = 'H',
    LETRA_CRUZ = 'C',
    LETRA_ESCOPETA = 'E',
    LETRA_ESTACA = 'e',
    LETRA_NOSFERATU = 'N',
    LETRA_VAMPIRELLA = 'V',
    LETRA_VAMPIRO = 'v',
    LETRA_VANESA = 'W',
    LETRA_ZOMBI = 'z'
};

enum OPCIONES_OBJETO {
    HUMANO = 1,
    CV = 2,
    VANESA = 3,
    VAMPIRELLA = 4,
    VAMPIRO = 5,
    NOSFERATU = 6,
    ZOMBI = 7,
    AGUA = 8,
    BALA = 9,
    ESTACA = 10,
    ESCOPETA = 11,
    CRUZ = 12,
};


enum OPCIONES_SIMULACION {
    BUSCAR_POR_ID = 1,
    MOSTRAR_TABLERO = 2,
    MOSTRAR_CANTIDAD_POR_BANDO = 3,
    SELECCIONAR_BANDO = 4,
    SALIR = 5
};

enum OPCION_BANDO {
    HUMANOS = 1,
    MONSTRUOS = 2,
};

enum OPCIONES_SIMULACION_JUGADOR {
    ATACAR = 1,
    DEFENDER = 2,
    MOVER = 3,
    PASAR = 4
};
enum OPCIONES_MENU_PRINCIPAL {
    JUGAR = 1,
    CREDITOS = 2,
    SALIR_MENU_PRINCIPAL = 3
};

const int INDICE_PRIMER_JUGADOR = 0;
const string ITEMS = "items";

const int ID_MINIMO = 0;
const int ID_MAXIMO = 999;
const int COORDENADA_MINIMA = 1;

#endif //TP3_NOSFERATU_CONSTANTES_H
