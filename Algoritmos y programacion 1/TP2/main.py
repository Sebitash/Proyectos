import tetris
import gamelib

ESPERA_DESCENDER = 12
ANCHO_JUEGO, ALTO_JUEGO = 9, 18
PIX_POR_CUADRADO = 30
GRILLA_PX_X = 270
GRILLA_PX_Y = 540
TAMANIO = 540
IZQUIERDA, DERECHA = -1, 1

def dibujar_grilla(juego):
    """
    recibe el juego y dibuja el tablero del juego y ademas,
    dibuja los bloques consolidados a la superficie
    """
    tablero = juego[0]
    for i in range(0, 541, PIX_POR_CUADRADO):
        gamelib.draw_line(0, i, GRILLA_PX_X, i, fill= "white", width=3)
    for i in range(0, 271, PIX_POR_CUADRADO):
        gamelib.draw_line(i, 0, i, GRILLA_PX_Y, fill= "white", width=3)
    for y in range(ALTO_JUEGO):
        for x in range(ANCHO_JUEGO):
            if tetris.hay_superficie(juego, x, y):
                gamelib.draw_rectangle(2+x*PIX_POR_CUADRADO,
                                       2+y*PIX_POR_CUADRADO,
                                       28+x*PIX_POR_CUADRADO,
                                       28+y*PIX_POR_CUADRADO,
                                       fill='red')
def dibujar_pieza(juego):
    """
    recibe el juego y dibuja en pantalla la pieza actual que va a bajar
    y su ubicacion durante el juego
    """
    for x, y in juego[1]:
        gamelib.draw_rectangle(2 + x * PIX_POR_CUADRADO,
                               2 + y * PIX_POR_CUADRADO,
                               28 + x *PIX_POR_CUADRADO,
                               28 + y * PIX_POR_CUADRADO,fill = "red")
        
def dibujar_siguiente_pieza(siguiente_pieza):
    """
    recibe la pieza siguiente a salir y la dibuja a un costado con su tablero
    """
    for i in range(120, 241, PIX_POR_CUADRADO):
        gamelib.draw_line(320, i, 440, i, fill='white', width=3)
    for i in range(320, 441, PIX_POR_CUADRADO):
        gamelib.draw_line(i, 120, i, 240, fill='white', width=3)
    for x, y in siguiente_pieza:
        gamelib.draw_rectangle(322 + x * PIX_POR_CUADRADO,
                               122 + y * PIX_POR_CUADRADO,
                               348 + x * PIX_POR_CUADRADO,
                               148 + y * PIX_POR_CUADRADO,
                               fill = 'blue')
        
def dibujar_texto(puntaje):
    """
    recibe el puntaje actual y dibuja en pantalla el mismo y titulos para identificar
    """
    gamelib.draw_text('Bienvenido al Tetris', 400, PIX_POR_CUADRADO, size=15, fill = 'orange')
    gamelib.draw_text(f"Puntaje: {puntaje}", 350, 80, size=15, fill = 'white')
    gamelib.draw_text("SIGUIENTE PIEZA", 380, 260, size=12, fill= 'white')

def procesar_teclas(ruta):
    """
    lee cada linea del archivo y devuelve un diccionario con clave la tecla y su valor la accion
    """
    teclas = {}
    with open(ruta) as archivo:
        for linea in archivo:
            linea = linea.rstrip("\n")
            if not linea:
                continue
            tecla, funcion = linea.replace(" ", "").split("=")
            teclas[tecla] = funcion
    return teclas
    
def leer_puntajes(ruta):
    """
    lee cada linea del archivo y
    devuelve una lista con una lista de tuplas con los puntajes guardados y sus nombres
    """
    puntajes = []
    try:
        with open(ruta) as f:
            for linea in f:
                linea = linea.rstrip("\n")
                if not linea:
                    continue
                nombre_jugador, puntaje_jugador = linea.split(",")
                puntajes.append((nombre_jugador, puntaje_jugador))
        return puntajes
    except:
        return puntajes

def grabar_puntajes(puntaje):
    """
    si es posible, guarda el nuevo puntaje con su nombre en la lista y luego guarda los puntajes
    de la lista en el archivo
    """
    puntajes = leer_puntajes("puntajes.txt")
    mostrar_puntajes = False
    if len(puntajes) == 10 and puntaje < int(puntajes[-1][1]):
        return (puntajes, mostrar_puntajes)
    nombre = gamelib.input("INGRESE SU NOMBRE: ")
    puntajes.append((nombre, puntaje))
    mostrar_puntajes = True
    puntajes_final = sorted(puntajes, key=lambda x: int(x[1]), reverse=True)
    if len(puntajes_final) > 10:
        puntajes_final.pop()
    with open("puntajes.txt", "w") as f:
        for nombre_jugador, puntaje_jugador in puntajes_final:
            f.write(f"{nombre_jugador},{puntaje_jugador}\n")
    return (puntajes_final, mostrar_puntajes)

def main():
    # Inicializar el estado del juego
    siguiente_pieza = tetris.generar_pieza()
    juego = tetris.crear_juego(tetris.generar_pieza())
    rotaciones = tetris.leer_rotaciones("piezas.txt")
    gamelib.resize(TAMANIO, TAMANIO)
    
    cerrar_juego = False
    puntaje = 0

    timer_bajar = ESPERA_DESCENDER
    while gamelib.loop(fps=30) and not tetris.terminado(juego):
        
        gamelib.draw_begin()
        # Dibujar la pantalla
        dibujar_grilla(juego)
        dibujar_texto(puntaje)
        dibujar_pieza(juego)
        dibujar_siguiente_pieza(siguiente_pieza)
        gamelib.draw_end()
        
        
        for ev in gamelib.get_events():
            if not ev:
                break
            if ev.type == gamelib.EventType.KeyPress:
                
                tecla = ev.key
                teclas = procesar_teclas("teclas.txt")
                if tecla in teclas.keys():
                    if teclas[tecla] == "IZQUIERDA":
                        juego = tetris.mover(juego, IZQUIERDA)
                    if teclas[tecla] == "DERECHA":
                        juego = tetris.mover(juego, DERECHA)
                    if teclas[tecla] == "DESCENDER":
                        juego, cambiar_pieza = tetris.avanzar(juego, siguiente_pieza)
                        puntaje += 1
                    if teclas[tecla] == "ROTAR":
                        juego = tetris.rotar(juego)
                    if teclas[tecla] == "GUARDAR":
                        tetris.guardar_partida(juego, "guardar.txt", siguiente_pieza, puntaje)
                    if teclas[tecla] == "CARGAR":
                        puntaje_guardado, tablero, pieza_guardada, siguiente_pieza_guardada = tetris.cargar("guardar.txt")
                        puntaje = int(puntaje_guardado)
                        siguiente_pieza = siguiente_pieza_guardada
                        juego[0] = tetris.restaurar_tablero(juego)
                        juego[1] = pieza_guardada
                    if teclas[tecla] == "SALIR":
                        cerrar_juego = True
                    # Actualizar el juego, según la tecla presionada
        if cerrar_juego:
            break
                        
        timer_bajar -= 1
        if timer_bajar == 0:
            timer_bajar = ESPERA_DESCENDER
            puntaje += 1
            juego_nuevo, cambiar_pieza = tetris.avanzar(juego, siguiente_pieza)
            if cambiar_pieza:
                siguiente_pieza = tetris.generar_pieza()
            juego = juego_nuevo
                
            # Descender la pieza automáticamente
    if tetris.terminado(juego):
        puntajes_final, mostrar_puntajes = grabar_puntajes(puntaje)
    
    
    while True:
        #pantalla final al tener el juego terminado
        if cerrar_juego:
            break
        gamelib.draw_text("FIN DEL JUEGO", 440, 520, size=15, fill= 'white')
        if mostrar_puntajes:
            gamelib.draw_text("Top 10 puntajes:", 380, 280, size=10, fill='red')
            for i in range(len(puntajes_final)):
                gamelib.draw_text(f"{puntajes_final[i][0]}: {puntajes_final[i][1]}", 380, 300 + (20 * i), size=8, fill ='white')
        ev = gamelib.wait()
        if ev.type == gamelib.EventType.KeyPress and ev.key == 'Escape':
            break
        
gamelib.init(main)