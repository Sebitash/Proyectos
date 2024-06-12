# Proyecto: Bitcoin - 1er Cuatrimestre 2023

### Fechas de entrega:

Entrega intermedia: lunes 22 de mayo

Entrega final de la cursada: lunes 26 de junio

Estas entregas serán presenciales en la sede de la Facultad.


### Alcance de la entrega intermedia:

La entrega intermedia deberá incluir los siguientes puntos desarrollados en la seccion Requerimientos funcionales:

Conexion a la red
Comportamiento del Nodo

Opcional: Se deberá presentar una interfaz gráfica, similar a la imagen que se observa en Ver transacciones pero utilizando distintas pestañas para Headers, Bloques y Transacciones

La entrega se realizara en forma de Demostración (Demo) en la cual los alumnos deberán abarcar los siguientes puntos:

Explicación general de la solución, incluyendo diagramas que muestren el diseño desarrollado.

Recorrido por el código fuente escrito, explicando los principales contenidos de cada módulo.

Demo en vivo del programa, en donde se comprobará que el programa cumple con los puntos solicitados.

Nota: Todos los miembros del grupo deberán participar de la demo y explicar su participación en el proyecto, incluyendo detalles de implementación.

## Introduccion a Blockchain
Blockchain es una tecnología descentralizada que se utiliza para registrar transacciones de manera segura e inmutable. La información se organiza en bloques conectados en una cadena y cada participante en la red tiene una copia idéntica del registro completo. La seguridad proviene de la criptografía y la naturaleza descentralizada del sistema. Se utiliza comúnmente para la gestión de criptomonedas, pero también tiene aplicaciones en otras áreas como la gestión de cadenas de suministro y la votación electrónica.

## Introduccion a Bitcoin
Bitcoin es una criptomoneda digital descentralizada basada en una red de nodos que ejecutan software Bitcoin Core. La red está asegurada mediante el uso de criptografía y un sistema de incentivos llamado "minería de Bitcoin", donde los participantes compiten para resolver un problema matemático complejo y validar transacciones en la red. Las transacciones se registran en una base de datos blockchain, que contiene un registro inmutable de todas las transacciones de Bitcoin desde su creación. El White Paper original fue escrito en 2009 por una persona o grupo anónimo de personas bajo el seudónimo de Satoshi Nakamoto.

### Importante: 
durante el desarrollo del proyecto utilizaremos la red de testing de Bitcoin: 'testnet' la cual no involucra dinero real y permite obtener test coins para realizar pruebas.

## Objetivo del Proyecto
El objetivo principal del presente proyecto de desarrollo consiste en la implementacion de un Nodo Bitcoin con funcionalidades acotadas que se detallan en el presente enunciado. Siguiendo las guias de desarrollo y especificaciones de Bitcoin.

El objetivo secundario del proyecto consiste en el desarrollo de un proyecto real de software de mediana envergadura aplicando buenas prácticas de desarrollo de software, incluyendo entregas y revisiones usando un sistema de control de versiones.

Se espera que se haga un uso lo más idiomático posible del lenguaje de programación Rust, siguiendo los estándares que éste promueve.

## Requerimientos funcionales
Los siguientes son los requerimientos funcionales para el desarrollo del Trabajo.

El nodo de Bitcoin deberá ser capaz de descargar y almacenar la cadena completa de headers desde el inicio de la blockchain y los bloques completos a partir de una fecha determinada, que correspondera al inicio del presente proyecto.

A su vez debera mantener actualizada la informacion de nuevos bloques (incluyendo sus headers y las transacciones incluidas) y nuevas transacciones (no confirmadas) que se van trasmitiendo por la red.

Tambien debera mantener la lista de UTXO (unspent transactions) a partir de la fecha mencionada y permitir al usuario realizar transacciones utilizando dichas UTXO.