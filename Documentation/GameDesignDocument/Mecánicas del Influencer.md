## **Movimiento**

- Utilizando los [[Controles|inputs]] de movimiento el jugador puede desplazarse libremente en 8 direcciones con una velocidad de $200\,cm/s$.
- Con el input de agachado, el jugador puede alternar entre un estado agachado y parado (default). Al estar agachado, la altura y la velocidad del personaje se reducen en un 50%.
- Con el input de correr el jugador puede incrementar su velocidad en un 200%.

## **Ruido**

Al moverse, el jugador hace [[ruido]] pudiendo [[IA de Mirna|alertar a Mirna]] de su presencia.
- Si se está caminando, emite un ruido de $40\,dB$.
- Si está agachado, emite un ruido de $16\,dB$ al moverse.
- Si está corriendo, emite un ruido de $60\,dB$.

## **Interactuar con Objetos**

Al recibir el input de interacción, el influencer podrá [[Objetos de Trasnochando con Mirna|interactuar con ciertos objetos]] del entorno, provocando distintos efectos dependiendo del objeto en cuestión.

### **Esconderse**

En el caso de los armarios, el jugador puede esconderse dentro de ellos al interactuar, volviéndose invisible para Mirna. Además, en caso de que Mirna estuviera previamente persiguiendo al jugador y este se esconda dentro del armario, Mirna dejará de perseguirlo instantáneamente.

Desde el interior del armario, el jugador podrá ver hacia afuera con una visión reducida. Al volver a interactuar con el armario, el jugador sale del armario volviendo a su posición original. Por último, no pueden estar dos jugadores dentro del mismo armario.

## **Comunicación**

Los jugadores pueden hablar entre sí usando un chat de voz o de texto integrados en el juego.