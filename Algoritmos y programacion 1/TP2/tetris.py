ANCHO_JUEGO, ALTO_JUEGO = 9, 18
IZQUIERDA, DERECHA = -1, 1
CUBO = 0
PISO = "piso"
Z = 1
S = 2
I = 3
L = 4
L_INV = 5
T = 6

import random

def leer_rotaciones(ruta):
    """
    lee la ruta y devuelve una lista de tuplas con las piezas y sus respectivas rotaciones
    """
    rotaciones = []
    with open(ruta) as f:
        
        for linea in f:
            rotaciones_pieza = []
            linea = linea.rstrip("\n").split(" ")
            for x in linea:
                rotacion = []
                x=x.split(";")
                for i in x:
                    i = i.split(",")
                    pos_x, pos_y = int(i[0]), int(i[1])
                    rotacion.append((pos_x, pos_y))
                rotaciones_pieza.append(tuple(rotacion))
            rotaciones.append(tuple(rotaciones_pieza))
    return rotaciones

PIEZAS = leer_rotaciones("piezas.txt")

def generar_pieza(pieza=None):
    """
    Genera una nueva pieza de entre PIEZAS al azar. Si se especifica el parámetro pieza
    se generará una pieza del tipo indicado. Los tipos de pieza posibles
    están dados por las constantes CUBO, Z, S, I, L, L_INV, T.

    El valor retornado es una tupla donde cada elemento es una posición
    ocupada por la pieza, ubicada en (0, 0). Por ejemplo, para la pieza
    I se devolverá: ( (0, 0), (0, 1), (0, 2), (0, 3) ), indicando que 
    ocupa las posiciones (x = 0, y = 0), (x = 0, y = 1), ..., etc.
    """
     
    if pieza == None:
        pieza = PIEZAS[random.randrange(0, len(PIEZAS))][0]
    else:
        pieza = PIEZAS[pieza][0]
    return pieza

def trasladar_pieza(pieza, dx, dy):
    """
    Traslada la pieza de su posición actual a (posicion + (dx, dy)).

    La pieza está representada como una tupla de posiciones ocupadas,
    donde cada posición ocupada es una tupla (x, y). 
    Por ejemplo para la pieza ( (0, 0), (0, 1), (0, 2), (0, 3) ) y
    el desplazamiento dx=2, dy=3 se devolverá la pieza 
    ( (2, 3), (2, 4), (2, 5), (2, 6) ).
    """
    nueva_posicion_pieza= []
    for i in pieza:
        nueva_posicion_pieza.append((i[0] + dx,i[1] + dy))
    pieza = tuple(nueva_posicion_pieza)
    return pieza

def crear_juego(pieza_inicial):
    """
    Crea un nuevo juego de Tetris.

    El parámetro pieza_inicial es una pieza obtenida mediante 
    pieza.generar_pieza. Ver documentación de esa función para más información.

    El juego creado debe cumplir con lo siguiente:
    - La grilla está vacía: hay_superficie da False para todas las ubicaciones
    - La pieza actual está arriba de todo, en el centro de la pantalla.
    - El juego no está terminado: terminado(juego) da False

    Que la pieza actual esté arriba de todo significa que la coordenada Y de 
    sus posiciones superiores es 0 (cero).
    """
    pieza_centrada = trasladar_pieza(pieza_inicial, ANCHO_JUEGO // 2, 0)
    
    juego = []
    for f in range(ALTO_JUEGO):
        juego.append([])
        for c in range(ANCHO_JUEGO):
            juego[f].append(None)
    grilla = [juego, pieza_centrada]
    
    return grilla


def dimensiones(juego):
    """
    Devuelve las dimensiones de la grilla del juego como una tupla (ancho, alto).
    """
    tablero = juego[0]
    alto = len(tablero)
    ancho = len(tablero[0])
    return (ancho, alto)

def pieza_actual(juego):
    """
    Devuelve una tupla de tuplas (x, y) con todas las posiciones de la
    grilla ocupadas por la pieza actual.

    Se entiende por pieza actual a la pieza que está cayendo y todavía no
    fue consolidada con la superficie.

    La coordenada (0, 0) se refiere a la posición que está en la esquina 
    superior izquierda de la grilla.
    """
    
    return juego[1]

def hay_superficie(juego, x, y):
    """
    Devuelve True si la celda (x, y) está ocupada por la superficie consolidada.
    
    La coordenada (0, 0) se refiere a la posición que está en la esquina 
    superior izquierda de la grilla.
    """
    tablero = juego[0]
    
    if tablero[y][x] != PISO:
        return False
    return True

def se_puede_mover(grilla,pieza,direccion):
    """
    Busca la mayor posicion sobre la columna, hacia la izquierda
    """
    for x,y in pieza:
        if x + direccion >=0 and x + direccion < ANCHO_JUEGO:
            if not hay_superficie([grilla,pieza],x+ direccion,y):
               continue
        return False
    return True
 
def mover(juego, direccion):
    """
    Mueve la pieza actual hacia la derecha o izquierda, si es posible.
    Devuelve un nuevo estado de juego con la pieza movida o el mismo estado 
    recibido si el movimiento no se puede realizar.

    El parámetro direccion debe ser una de las constantes DERECHA o IZQUIERDA.
    """
    tablero = juego[0]
    pieza = juego[1]
    if se_puede_mover(tablero, pieza, direccion):
        return [tablero,trasladar_pieza(juego[1],direccion,0)]
    return juego
def verificar_extremos(grilla, pieza):
    """
    verifica los extremos de la pieza ingresada, y devuelve un booleano si es posible
    pueda la misma bajar o no
    """
    for x,y in pieza:
        if y + 1 >=0 and y + 1 < ALTO_JUEGO:
            if grilla[y + 1][x] == None:
                continue
        return False
    return True
def eliminar_fila_llena(grilla):
    """
    si dentro del juego, hay una fila llena, lo elimina y
    se inserta una nueva fila vacia. Devuelve el nuevo estado del juego
    """
    for i, f in enumerate(grilla):
        if not None in f:
            grilla.pop(i)
            grilla.insert(0, [None] * ANCHO_JUEGO)
    return grilla

def buscar_rotacion(pieza_en_origen):
    """
    verifica cual es la siguiente rotacion que debe hacer la pieza actual
    """
    
    for p in PIEZAS:
        if pieza_en_origen in p:
            if p.index(pieza_en_origen) == len(p) - 1:
                return p[0]
            else:
                indice = p.index(pieza_en_origen)
                return p[indice + 1]
            
def verificar_rotacion(juego, siguiente_rotacion, x, y):
    """
    Verifica si es posible que la pieza actual rote y devuelve un booleano si puede o no
    """
    tablero = juego[0]
    for pos_x, pos_y in siguiente_rotacion:
        if (pos_x + x >= 0) and (pos_x + x < ANCHO_JUEGO) and (pos_y + y >=0) and (pos_y + y < ALTO_JUEGO):
            if not hay_superficie([tablero, siguiente_rotacion], pos_x + x, pos_y + y):
                continue              
        return False
    return True

def rotar(juego):
    """
    recibe el juego con la pieza actual, todas las rotaciones de las piezas y luego revisa las rotaciones de la pieza actual
    y devuelve el juego con la pieza rotada
    """
    tablero, pieza_actual = juego
    pieza_ordenada = sorted(pieza_actual)
    primera_posicion = pieza_ordenada[0]
    x, y = primera_posicion
    pieza_en_origen = trasladar_pieza(pieza_ordenada, -x, -y)
    siguiente_rotacion = buscar_rotacion(pieza_en_origen)
    if verificar_rotacion(juego, siguiente_rotacion, x, y):
        return [tablero, trasladar_pieza(siguiente_rotacion, x, y)]
    return [tablero, pieza_actual]

def avanzar(juego, siguiente_pieza):
    """
    Avanza al siguiente estado de juego a partir del estado actual.
    
    Devuelve una tupla (juego_nuevo, cambiar_pieza) donde el primer valor
    es el nuevo estado del juego y el segundo valor es un booleano que indica
    si se debe cambiar la siguiente_pieza (es decir, se consolidó la pieza
    actual con la superficie).
    
    Avanzar el estado del juego significa:
     - Descender una posición la pieza actual.
     - Si al descender la pieza no colisiona con la superficie, simplemente
       devolver el nuevo juego con la pieza en la nueva ubicación.
     - En caso contrario, se debe
       - Consolidar la pieza actual con la superficie.
       - Eliminar las líneas que se hayan completado.
       - Cambiar la pieza actual por siguiente_pieza.

    Si se debe agregar una nueva pieza, se utilizará la pieza indicada en
    el parámetro siguiente_pieza. El valor del parámetro es una pieza obtenida 
    llamando a generar_pieza().

    **NOTA:** Hay una simplificación respecto del Tetris real a tener en
    consideración en esta función: la próxima pieza a agregar debe entrar 
    completamente en la grilla para poder seguir jugando, si al intentar 
    incorporar la nueva pieza arriba de todo en el medio de la grilla se
    pisara la superficie, se considerará que el juego está terminado.

    Si el juego está terminado (no se pueden agregar más piezas), la funcion no hace nada, 
    se debe devolver el mismo juego que se recibió.
    """
    
    tablero = juego[0]
    pieza_actual = juego[1]
    seguir = verificar_extremos(tablero, pieza_actual)
    if terminado(juego):
        return(juego, False)
    if seguir:
        return ([tablero, trasladar_pieza(juego[1], 0, 1)], False)
    for c,f in juego[1]:
        tablero[f][c] = PISO
    tablero = eliminar_fila_llena(tablero)
    return([tablero, trasladar_pieza(siguiente_pieza, ANCHO_JUEGO // 2, 0)], True)

def guardar_partida(juego, ruta, siguiente_pieza, puntaje):
    """
    recibe el ultimo estado del juego, con el tablero, la pieza actual, la siguiente pieza y el puntaje
    y lo guarda en el archivo en formato de coordenadas
    """
    separador = ";"
    tablero, pieza = juego
    with open(ruta, "w") as f:
        f.write(f"{puntaje}\n")
        for y in range(ALTO_JUEGO):
            for x in range(ANCHO_JUEGO):
                if hay_superficie(juego, x, y):
                    f.write(f"{x},{y};")
        f.write("\n")
        for x,y in pieza:
            f.write(f"{x},{y};")
        f.write("\n")
        for x,y in siguiente_pieza:
            f.write(f"{x},{y};")
        f.write("\n")
        
def cargar(ruta):
    """
    lee el archivo que contiene el ultimo estado del juego guardado y devuelve una lista con su contenido
    """
    restaurando_juego = []
    with open(ruta) as f:
        puntaje = f.readline()
        puntaje = puntaje.rstrip("\n")
        restaurando_juego.append(puntaje)
        for linea in f:
            elemento = []
            linea = linea.rstrip("\n").split(";")
            linea.pop()
            for i in linea:
                i = i.split(",")
                x, y = int(i[0]), int(i[1])
                elemento.append((x,y))
            restaurando_juego.append(elemento)
    return restaurando_juego

def restaurar_tablero(juego):
    """
    recibe las coordenadas donde habia superficie consolidada, y devuelve el tablero de la partida guardada
    """
    puntaje_guardado, tablero_viejo, pieza_guardada, siguiente_pieza_guardada = cargar("guardar.txt")
    tablero = []
    for f in range(ALTO_JUEGO):
        tablero.append([])
        for c in range(ANCHO_JUEGO):
            tablero[f].append(None)
    for f in range(ALTO_JUEGO):
        for c in range(ANCHO_JUEGO):
            ubicacion = (c,f)
            for i in tablero_viejo:
                if ubicacion == i:
                    tablero[f][c] = PISO
    return tablero
            

def terminado(juego):
    """
    Devuelve True si el juego terminó, es decir no se pueden agregar
    nuevas piezas, o False si se puede seguir jugando.
    """
    tablero = juego[0]
    for x,y in juego[1]:
        if tablero[y][x] == PISO:
            return True
    return False
