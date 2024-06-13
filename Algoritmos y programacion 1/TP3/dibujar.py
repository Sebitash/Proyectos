import gamelib
def dibujar_juego(game):
    """
    dibuja en pantalla el escenario y los objetos y el mensaje con su sonido si se perdio
    """
    dibujar_escenario(game)
    dibujar_objetos(game)
    if nivel_perdido(game):
        gamelib.play_sound("game_over.wav")
        gamelib.draw_text("Game Over", 300, 20)

def dibujar_escenario(game):
    """
    dibuja el recuadro del juego, y al costado las imagenes que pertencen al juego con su especificacion
    """
    gamelib.draw_rectangle(10, 10, 490, 390, outline='white', fill= None)
    gamelib.draw_text(f'Puntaje:{game.puntaje}', 540, 380, fill='white')
    gamelib.draw_text("= personaje", 550, 330)
    gamelib.draw_image("personaje.gif", 495, 325)
    gamelib.draw_text("= Robot", 545, 300)
    gamelib.draw_image("robot.gif", 505, 295)
    gamelib.draw_text("= Obstaculo", 548, 270)
    gamelib.draw_image("escombro.gif", 494, 265)
    gamelib.draw_text("ESC : Salir", 540, 220)
    gamelib.draw_text("X : Teletransporte", 550, 190, size = 10)
    gamelib.draw_text("R: Tp Seguro", 540, 170, size = 10)
    gamelib.draw_text(f"TPs seguros:{game.teletransportes_seguros}", 545, 20)
    dibujar_controles()

def dibujar_controles():
    """
    dibuja los controles con la direccion respectiva a donde se moveria el personaje
    """
    gamelib.draw_line(550, 100, 550, 130)
    gamelib.draw_text("s", 550, 140)
    gamelib.draw_line(550, 90, 550, 60)
    gamelib.draw_text("w", 550, 50)
    gamelib.draw_line(555, 95, 585, 95)
    gamelib.draw_text("d", 595, 95)
    gamelib.draw_line(545, 95, 515, 95)
    gamelib.draw_text("a", 505, 95)
    gamelib.draw_line(555, 90, 575, 70)
    gamelib.draw_text("e", 585, 60)
    gamelib.draw_line(545, 90, 525, 70)
    gamelib.draw_text("q", 515, 60)
    gamelib.draw_line(545, 100, 525, 120)
    gamelib.draw_text("z", 520, 125)
    gamelib.draw_line(555, 100, 575, 120)
    gamelib.draw_text("c", 580, 125)

def dibujar_objetos(game):
    """
    dibuja en pantalla los robots, los escombros y el personaje
    """
    lado_x, lado_y = 10.66, 12.66
    if game.posicion_personaje() != None:
        pos_x, pos_y = game.posicion_personaje()
        gamelib.draw_image("personaje.gif", lado_x * (pos_x + 1) + (lado_x / 2), lado_y * (pos_y + 1) + (lado_y / 2))
     
    for i in game.posicion_robots:
        gamelib.draw_image("robot.gif", lado_x * (i[0] + 1) + (lado_x / 2), lado_y * (i[1] + 1) + (lado_y / 2))
    for e in game.posicion_escombros:
        gamelib.draw_image("escombro.gif", lado_x * (e[0] + 1) + (lado_x / 2), lado_y * (e[1] + 1) + (lado_y / 2))