
## **Caminar:**
Movimiento libre en 8 direcciones utilizando los inputs “WASD” del teclado. Velocidad estándar.

## **Agacharse:**
Pone en cuclillas al personaje a partir de los inputs “Ctrl” o “C” del teclado. Reduce la altura y colisión del personaje en un 50%. Presionando nuevamente alguno de estos inputs, el personaje se vuelve a parar de forma normal.

## **Caminar agachado:**
Combina la mecánica de agacharse con la de caminar. Avanzar de esta forma reduce la velocidad en un 50%.

## **Correr:**
Mientras el jugador camina, manteniendo presionado el input “shift” aumenta su velocidad en un 50%.

## **Ruido:**
Cada mecánica ya mencionada maneja un nivel de ruido dentro del juego:
	Caminar: Ruido estándar.
	Caminar agachado: **-80%** del ruido estándar.
	Correr: **+50%** del ruido estándar.

## **IA de Mirna:**
Mirna posee un árbol de comportamiento definido por una Inteligencia artificial que sirve como sistema de detección de jugadores en base a estímulos auditivos y/o visuales.

## **Interactuar con Objetos:**
Con el input “E” del teclado, el jugador podrá interactuar con ciertos objetos del entorno. El efecto de la interacción depende de cada objeto en particular. Algunos se looten, otros cambian de estado (encendido, apagado), y otros tienen un efecto único.

	Estatuillas: Al interactuar, el objeto queda en pantalla para que el jugador lo cambie de lugar.
	Pulseras de la amistad: Looteo.
	Botón: Cambio de estado (presionado/sin presionar).
	Aretes de Mirna: Looteo.
	Cuadro de Goldina: Looteo.
	Fonógrafo: Cambio de estado (encendido/apagado).
	Campanas: Cambio de estado (sonido/silencio).
	Salerito: Looteo.
	Tintura: Looteo.
	Cerrojos: Cambio de estado (cerrado, cambio de posición en vertical de cada joya/abierto)

## **Esconderse:**
El jugador puede ocultarse dentro de armarios al estar adyacente a uno y presionando el input “E”.  
Mientras está escondido, Mirna no puede detectarlo. En caso de que Mirna estuviera persiguiendo al jugador y este se escondiera dentro del armario, perderá el aggro de Mirna inmediatamente.
El jugador desde dentro podrá ver hacia fuera con una visión reducida.
Cuando el jugador desee salir del armario puede presionar nuevamente la tecla “E” para poder salir. Entrar y salir del armario no genera ruido.
No pueden estar dos jugadores dentro del mismo armario.

## **Comunicación:**
Los jugadores pueden hablar entre sí usando un sistema de voz integrado si mantienen presionada la tecla “V”, o a través del chat de escritura in-game presionando la tecla “Enter”. Hablar por micrófono no generará ruido.