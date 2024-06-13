# Chase (Robots)
Chase es un juego por turnos en el que el jugador debe escapar de unos robots programados para perseguir y atraparle. El jugador puede destruir los robots moviéndose de forma tal que los robots colisionen entre ellos o con otros obstáculos.

Reglas completas - [Inglés](https://www.youtube.com/watch?v=K7L55s9sf4k)

## Reglas
Chase se juega en una grilla rectangular bidimensional. El objetivo es escapar de unos robots que han sido programados para matarnos.

El juego es por turnos. En el juego original, el jugador comienza en una posición aleatoria. En algunas variantes (como por ejemplo GNOME Robots) el jugador comienza en el centro de la grilla. Los robots comienzan en posiciones aleatorias. Cada vez que el jugador se mueve en cualquier dirección a una casilla adyacente (horizontal, vertical o diagonal), cada robot se mueve un casillero en la dirección del jugador. Si alguno de los robots llega a la casilla del jugador, el juego se considera perdido.

Si alguno de los robots colisiona con otro robot o con un obstáculo, el robot es destruido, y en su lugar quedan sus escombros, que serán considerados como un obstáculo hasta que termine el nivel. (Si dos robots colisionan entre sí, quedará un solo casillero con escombros en el lugar de la colisión.)

El jugador puede empujar los escombros moviéndose de forma tal de colisionar con uno de ellos. En lugar de colisionar, el escombro se moverá un casillero en la dirección correspondiente, siempre y cuando el casillero esté vacío. En caso contrario, el movimiento no está permitido. (Esto es similar a la mecánica del juego Sokoban.)

El jugador además puede teletransportarse a un casillero aleatorio de la grilla. Esto cuenta como un movimiento, y los robots responderán como siempre moviéndose hacia la nueva posición del jugador. Como la posición es seleccionada aleatoriamente, es posible que el jugador se teletransporte a una casilla ocupada por un robot o unos escombros, en cuyo caso el juego se considerará perdido.

Cuando todos los robots han sido eliminados, el jugador pasa al siguiente nivel, con más robots.

### Extras
No es necesario implementar los extras, pero pueden hacerlo si ya terminaron con el resto de la implementación del juego.

Algunas variantes de este juego tienen: - Una cantidad limitada (por ejemplo, una vez por nivel) de "teletransportaciones seguras", que garantizan que la casilla seleccionada está vacía. - Una cantidad limitada de usos de un arma que permite matar un robot adyacente. - Un tipo de robot que se mueve más rápido (de a dos casilleros por turno). - Un tipo de robot que no puede ser destruido (y no es necesario destruir para ganar el nivel).

## Requerimientos del TP
* El juego debe ser implementado con Gamelib y tener una interfaz gráfica con la cual interactuar para jugarlo.
* El juego debe constar con al menos 3 niveles que pueden ser autogenerados dadas ciertas constantes (cantidad de robots y obstáculos que debe cambiar nivel a nivel), o estar definidos en archivos.
* El juego puede no tener final, volviendose los niveles cada vez más difícil hasta que el jugador pierda; o puede tener un final definido luego de cierta cantidad fija de niveles. Si se puede ganar, debe mostrarle al jugador de alguna manera que el mismo ganó.

### Recursos
Posible visualización del juego: [link](https://en.wikipedia.org/wiki/Chase_(video_game)#/media/File:Robots_graphic_screenshot.png)

## Sugerencias de Implementación
Se recomienda seguir una estructura parecida a la siguiente para el ciclo 
```
main():
```
```
def main():
    juego = inicializar_juego()
    while not juego.terminado():
        juego.inicializar_siguiente_nivel()
        while not juego.nivel_terminado():
            mostrar_estado_juego(juego)
            accion = pedir_accion_al_jugador()
            juego.avanzar_un_step(accion)
    if juego.ganado():
        mostrar_pantalla_ganador()
    else:
        mostrar_pantalla_perdedor()
```
Notar que en esta implementación existe una clase Juego que tiene la mayoría del comportamiento. Queda a decisión del implementador decidir si utilizar esta u otras clases o no (recomendamos que usen al menos alguna clase porque les va a facilitar mantener el estado del juego).