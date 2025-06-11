El personaje de [[Mirna Lemort]] está manejado por una inteligencia artificial que responde a un árbol de comportamiento definido. Además, esta inteligencia artificial cuenta con un sistema de percepción que le ayuda a registrar estímulos que generen sus cambios de comportamiento.

## Sistema de percepción

Como percepción principal, Mirna posee una visión en forma de cono con "n" cm de rango en un ángulo de 50° con el que detecta a los [[Influencer Foodie|influencers]].

Como percepción secundaria, Mirna posee también un oído que registra ruidos de manera radial de acuerdo a la fórmula

$$
y = 0.2\,\mathrm{dB/cm} \cdot x
$$

donde _y_ es el ruido mínimo que Mirna puede escuchar (medido en dB) dado _x_ que es la distancia entre Mirna y el origen del ruido (medida en cm).

## Árbol de comportamiento

- Mirna comienza patrullando en loop (por qué) los puntos definidos en el [[Mapa de patrullaje|mapa de patrullaje]].
- Si escucha un ruido, Mirna pasa a un estado de **investigación** donde interrumpe su patrullaje para ir a la posición donde se originó dicho ruido. Una vez que llega, espera 3 segundos y vuelve al patrullaje desde donde fue interrumpido.
- Si Mirna detecta al jugador con su visión, pasará a un estado de **persecución** donde interrumpe su patrullaje o su investigación para dirigirse hacia la última posición donde vio al jugador. Si pierde de vista al jugador, al llegar a la posición donde lo vio espera 3 segundos y luego pasa a su estado previo (investigación o patrullaje). Si Mirna llega a la posición de alguno de los jugadores, estos [[Condición de victoria y derrota|pierden el juego]].