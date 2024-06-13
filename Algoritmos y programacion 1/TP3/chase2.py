import random
import gamelib
import time
import dibujar
ANCHO_JUEGO, ALTO_JUEGO = 45, 30
ANCHO_PANTALLA, ALTO_PANTALLA = 600,400
IZQUIERDA, DERECHA = -1, 1
ABAJO, ARRIBA = 1, -1
POSICION_PERSONAJE = (45//2, 30//2)
ROBOT = "robot"
PERSONAJE = "personaje"
ESCOMBRO = "escombro"

def leer_niveles(ruta):
    """
    recibe por ruta el archivo con la cantidad de robots por nivel y
    devuelve un diccionario como clave el numero del nivel y valor la cantidad de robots a generarse
    """
    niveles = {}
    with open(ruta) as f:
        contador = 1
        for linea in f:
            robots = linea.rstrip("\n")
            niveles[contador] = (int(robots))
            contador += 1
    return niveles


class Juego:
    
    def __init__(self):
        """
        inicializa en puntaje en 0, inicializa los niveles a jugarse que reciben del diccionario, la cantidad de robots por nivel,
        y ademas crea una lista donde se pondran las posiciones de los robots,
        una lista donde se pondran la posicion de los escombros, la grilla que posteriormente se ampliara y una lista donde indicara el nivel actual del juego
        """
        self.niveles = leer_niveles("niveles.txt")
        self.nivel_actual = 1
        self.juego = []
        self.posicion_robots = []
        self.posicion_escombros = []
        self.puntaje = 0
        self.teletransportes_seguros = 5
        self.crear_juego()
    
    def crear_juego(self):
        """
        se llama a la clase juego, a los metodos del mismo y devuelve el juego con el nivel inicial
        """
        self.generar_grilla()
        self.generar_robots()
        self.ubicar_robots_y_obstaculos()
        self.ubicar_personaje()
    
    def generar_robots(self):
        """
        dependiendo el nivel a jugar, genera por cada robot una posicion aleatoria sin chocarse con la del personaje y con la de otro robot
        y las agrega en la lista
        """
        self.posicion_robots = []
        for i in range(self.niveles[self.nivel_actual]):
            posicion = (random.randint(0, 44), random.randint(0, 29))
            if not posicion == POSICION_PERSONAJE and not posicion in self.posicion_robots:
                self.posicion_robots.append(posicion)

    def generar_grilla(self):
        """
        crea la grilla, con la altura y el ancho del juego ya preestablecidos
        """
        for f in range(ALTO_JUEGO):
            self.juego.append([])
            for c in range(ANCHO_JUEGO):
                self.juego[f].append(None)
                
    def ubicar_robots_y_obstaculos(self):
        """
        ubica en el juego los robots y los escombros en sus respectivas posiciones
        """
        for f in range(ALTO_JUEGO):
            for c in range(ANCHO_JUEGO):
                ubicacion = (c,f)
                if self.juego[f][c] != PERSONAJE:
                    self.juego[f][c] = None
                for i in self.posicion_robots:
                    if ubicacion == i:
                        self.juego[f][c] = ROBOT
                for i in self.posicion_escombros:
                    if ubicacion == i:
                        self.juego[f][c] = ESCOMBRO
    def ubicar_personaje(self):
        """
        ubica en el juego el personaje en la posicion ya predefinida
        """
        x, y = POSICION_PERSONAJE
        self.juego[y][x] = PERSONAJE
    
    def posicion_personaje(self):
        """
        devuelve el x,y de la posicion donde se encuentra el personaje en el juego
        """
        for f in range(ALTO_JUEGO):
            for c in range(ANCHO_JUEGO):
                if self.juego[f][c] == PERSONAJE:
                    personaje = (c, f)
                    return personaje
    
    def trasladar_personaje(self, x , y, dx, dy):
        """
        traslada al personaje sumandole dx y dy, respectivamente
        """
        self.juego[y][x] = None
        if self.juego[y + dy][x + dx] != ROBOT: 
            self.juego[y + dy][x + dx] = PERSONAJE
        
    def mover_personaje_juego(self, x, y, direccion_horizontal, direccion_vertical):
        if se_puede_mover(x, y, direccion_horizontal, direccion_vertical):
            if self.hay_escombro(y + direccion_vertical, x + direccion_horizontal):
                mover = self.mover_escombro(x, y, direccion_horizontal, direccion_vertical)
                if mover == True:
                    self.trasladar_personaje(x , y, direccion_horizontal, direccion_vertical)
            else:
                self.trasladar_personaje(x , y, direccion_horizontal, direccion_vertical)
                
    def teletransportar(self):
        """
        genera una nueva posicion para el personaje y en la que se encontraba anteriormente desaparece
        y aparece en la nueva posicion aleatoria
        """
        posicion_random = (random.randint(0, 44), random.randint(0, 29))
        x, y = self.posicion_personaje()
        if self.juego[posicion_random[1]][posicion_random[0]] == ROBOT:
            self.juego[y].remove(PERSONAJE)
        else:
            self.juego[y][x] = None
            self.juego[posicion_random[1]][posicion_random[0]] = PERSONAJE
    
    def hay_escombro(self, y, x):
        """
        Verifica si en la posicion x,y hay un escombro y devuelve un booleano si lo hay
        o no
        """
        if self.juego[y][x] != ESCOMBRO:
            return False
        return True
    
    def mover_escombro(self, x, y, dx, dy):
        """
        verifica si es posible mover el escombro y si se puede, actualiza el juego con la nueva posicion del escombro, si no se puede
        devuelve False
        """
        if se_puede_mover(x, y, dx * 2, dy * 2) and not self.hay_escombro(y + dy * 2, x + dx * 2):
            if self.hay_robot(x + dx * 2, y + dy * 2):
                self.posicion_robots.remove((x + dx * 2, y + dy * 2))
                self.puntaje += 10
            self.posicion_escombros.remove((x + dx, y + dy))
            self.posicion_escombros.append((x + dx * 2, y + dy * 2))
            self.ubicar_robots_y_obstaculos()
            return True
        return False
    
    def hay_robot(self, x, y):
        """
        Verifica si en la posicion x,y hay un robot y devuelve un booleano si lo hay
        o no
        """
        if self.juego[y][x] != ROBOT:
            return False
        return True 

    def teletransportar_lugar_seguro(self):
        """
        genera una nueva posicion para el personaje asegurandose que esa posicion no haya robot ni escombro y en la que se
        encontraba anteriormente desaparece y aparece en la nueva posicion aleatoria segura y le resta a su cantidad de teletransportaciones
        seguras
        """
        posicion_random = (random.randint(0, ANCHO_JUEGO - 1), random.randint(0, ALTO_JUEGO - 1))
        x, y  = self.posicion_personaje()
        posicion_robots = self.posicion_robots
        posicion_escombros = self.posicion_escombros
        while self.teletransportes_seguros > 0:
            if posicion_random not in posicion_robots and posicion_random not in posicion_escombros:
                self.juego[y][x] = None
                self.juego[posicion_random[1]][posicion_random[0]] = PERSONAJE
                self.teletransportes_seguros -= 1
                break
            posicion_random = (random.randint(0, ANCHO_JUEGO - 1), random.randint(0, ALTO_JUEGO - 1))
     
    def teletransportar_robot(self):
        """
        verifica la nueva posicion del personaje, y mueve cada robot hacia la direccion del personaje
        """
        posicion_robots = self.posicion_robots
        posicion_nuevas = []
        c, f = self.posicion_personaje()
        for x, y in posicion_robots:
            if f == y and c > x: 
                posicion_nuevas.append((x + DERECHA, y))
            elif f == y and c < x:
                posicion_nuevas.append((x + IZQUIERDA, y))
            elif c == x and f > y:
               posicion_nuevas.append((x, y + ABAJO))
            elif c == x and f < y:
                posicion_nuevas.append((x, y + ARRIBA))
            elif c > x and f < y:
                posicion_nuevas.append((x+DERECHA, y+ARRIBA))
            elif c < x and f < y:
                posicion_nuevas.append((x+IZQUIERDA, y+ARRIBA))
            elif c > x and f > y:
                posicion_nuevas.append((x+DERECHA, y+ABAJO))
            elif c < x and f > y:
                posicion_nuevas.append((x+IZQUIERDA, y+ABAJO))
        self.posicion_robots = posicion_nuevas
        self.ubicar_robots_y_obstaculos() 
        
    def destruir_robot(self):
        """
        calcula si hay un choque entre robots, elimina sus posiciones y ubica en esa posicion un escombro. Si un robot colisiona con un escombro,
        la posicion del robot desaparece
        """
        posicion_robots = self.posicion_robots
        for i in posicion_robots:
            posicion = posicion_robots.count(i)
            if posicion >= 2:
                self.posicion_escombros.append(i)
                posicion_robots.remove(i)
                posicion_robots.remove(i)
                self.puntaje += 20
                self.posicion_robots = posicion_robots
                self.ubicar_robots_y_obstaculos()
                continue
            if i in self.posicion_escombros:
                posicion_robots.remove(i)
                self.puntaje += 10
                self.posicion_robots = posicion_robots
                self.ubicar_robots_y_obstaculos()
    
    def reiniciar_posicion_personaje(self):
        """
        elimina la ultima posicion del personaje y lo ubica en el centro de la grilla
        """
        x, y = self.posicion_personaje()
        self.juego[y][x] = None
        self.ubicar_personaje()
        
    def nivel_terminado(self):
        """
        verifica si no hay mas robots y no se perdio el nivel y si es asi, pasa al siguiente nivel, estableciendo la posicion del personaje,
        la cantidad de robots y sus posiciones y resetea los teletransportes_seguros
        """
        if len(self.posicion_robots) == 0 and not self.nivel_perdido():
            if self.nivel_actual + 1 in self.niveles:
                self.nivel_actual += 1
                self.reiniciar_posicion_personaje()
                self.posicion_escombros = []
                self.teletransportes_seguros = 5
                self.generar_robots()
                self.ubicar_robots_y_obstaculos()
            return True
        return False
    
    def nivel_perdido(self):
        """
        verifica si en el juego esta el personaje, devuelve False, sino devuelve True
        """
        for elem in self.juego:
            if PERSONAJE in elem:
                return False
        return True
        
    def terminado(self):
        """
        devuelve True si el juego esta terminado, sino devuelve False
        """
        if self.nivel_actual + 1 not in self.niveles and self.nivel_terminado():
            return True
        return False
    
    def actualizar_juego(self, tecla):
        """
        actualiza el juego dependiendo la tecla recibida
        """
        x, y = self.posicion_personaje()
        if tecla == "d":
            self.mover_personaje_juego(x, y, DERECHA, 0) 
                    
        if tecla == "w":
            self.mover_personaje_juego(x, y, 0, ARRIBA)  
                           
        if tecla == "s":
            self.mover_personaje_juego(x, y, 0, ABAJO)
            
        if tecla == "e":
            self.mover_personaje_juego(x, y, DERECHA, ARRIBA)

        if tecla == "q":
            self.mover_personaje_juego(x, y, IZQUIERDA, ARRIBA)
                           
        if tecla == "c":
            self.mover_personaje_juego(x, y, DERECHA, ABAJO)
                    
        if tecla == "z":
            self.mover_personaje_juego(x, y, IZQUIERDA, ABAJO)
                               
        if tecla == "a":
            self.mover_personaje_juego(x, y, IZQUIERDA, 0)
                
        if tecla == "x":
            self.teletransportar()
        
        if tecla == "r":
            self.teletransportar_lugar_seguro()
            
        if not self.nivel_perdido():    
            self.teletransportar_robot()  
            self.destruir_robot()          
        
def cantidad(game):
    robots = (0, len(game.posicion_robots))
    personaje = 0
    escombros = (0, len(game.posicion_escombros))
    for i in game.juego:
        for e in i:
            if e == ROBOT:
                robots = (robots[0] + 1, robots[1])
            if e == PERSONAJE:
                personaje += 1
            if e == ESCOMBRO:
                escombros = (escombros[0] + 1, escombros[1])
    print(f"Robots : {robots}")
    print(f"Personaje : {personaje}")
    print(f"Escombros : {escombros}")
    print("")

def se_puede_mover(x, y, direccion_horizontal, direccion_vertical):
    """
    verifica si es posible moverse en la direccion horizontal y devuelve un booleano
    si es posible o no
    """
    if (x + direccion_horizontal >= 0 and x + direccion_horizontal < ANCHO_JUEGO) and (y + direccion_vertical >=0 and y + direccion_vertical < ALTO_JUEGO):
        return True
    return False  

def dibujar_juego(game):
    """
    dibuja en pantalla el escenario y los objetos y el mensaje con su sonido si se perdio
    """
    dibujar.dibujar_escenario(game)
    dibujar.dibujar_objetos(game)
    if game.nivel_perdido():
        gamelib.play_sound("game_over.wav")
        gamelib.draw_text("Game Over", 300, 20)
    

def main():
    gamelib.resize(ANCHO_PANTALLA, ALTO_PANTALLA)
    gamelib.title("Chase")
    game = Juego()
    
    while gamelib.is_alive():       
        gamelib.draw_begin()
        dibujar_juego(game)
        gamelib.draw_end()
        
        if game.terminado():
            gamelib.play_sound("win.wav")
            gamelib.say("Ganaste")
            return
        
        if game.nivel_perdido():
            gamelib.say("Perdiste, apreta aceptar para salir del juego")
            return
            
        if game.nivel_terminado():
            gamelib.play_sound("win.wav")
            time.sleep(5)
            
        for event in gamelib.get_events():
          if not event:
              break
          if event.type == gamelib.EventType.KeyPress:
              tecla = event.key
              game.actualizar_juego(tecla)
              
              if event.type == gamelib.EventType.KeyPress and event.key == "Escape":
                  return
        

gamelib.init(main)