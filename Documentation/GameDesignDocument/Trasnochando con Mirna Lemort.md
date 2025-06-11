## Introducción##

Este es el documento de diseño de _Trasnochando con Mirna Lemort_. Un videojuego para dos jugadores cooperativo en primera persona, desarrollado en Unreal Engine 5 para Windows PC.

A lo largo de este documento detallaremos las mecánicas de juego, diseño de niveles, especificaciones artísticas, análisis de competencia y negocio, y especificaciones técnicas.

## Concepto principal

_Trasnochando con Mirna_ Lemort es un juego donde dos jugadores controlan a unos [[Influencer Foodie|influencers gastronómicos]]  que han sido invitados al programa de TV de [[Mirna Lemort]]. Sin embargo todo cambia cuando llegan a la [[Mansión Lemort]] para el show.

El objetivo del juego es que ambos jugadores cooperen para [[Puzzles|resolver puzzles]] y [[Dinámica de sigilo|escapar de las garras de Mirna]], quien se revela como una diva vampírica que se alimenta no solo de sangre sino también de la juventud de los invitados. 

## Programa de TV ##

Trasnochando con Mirna Lemort es también el nombre del programa que protagoniza [[Mirna Lemort]]. En el programa se invitan [[Influencer Foodie|influencers y gente joven]] que van a cenar con Mirna. Cuando la grabación del programa termina, Mirna revela sus verdaderas intenciones y [[IA de Mirna|ataca]] a los invitados para robarles su juventud.

## Inicio del juego
El juego arranca en la [[Setup inicial - Sala 00|Sala 00]] de la [[Mansión Lemort]]. Ahí, los jugadores recibirán una [[Interfaz de Usuario|carta introductoria]] escrita por [[Goldina Lemort|Goldina]], la hermana gemela de Mirna, la cual indica el objetivo a cumplir para poder [[Condición de victoria y derrota|escapar]] sanos y salvos de las garras de Mirna.

## Puzzles cooperativos
El juego cuenta con 4 [[Puzzles]] en total, los cuales comparten la particularidad de requerir la cooperatividad de ambos jugadores para poder ser completados.
El [[Puzzle de Estatuillas|puzzle inicial]] funcionará a modo de tutorial para que los jugadores se familiaricen con los [[Controles]] del juego. Durante esta etapa, Mirna no participará y los jugadores podrán [[Mecánicas del Influencer|moverse]] de forma más tranquila sin tener que preocuparse por los niveles de [[Ruido]] que generen, pero sí comprenderán que existe y es un factor a tener en cuenta (ya que lo verán activo en el [[Interfaz de Usuario|HUD]]).

El resto de los puzzles se encontrarán en la zona de la mansión por donde Mirna [[Mapa de patrullaje|transita]] de forma activa. Esta zona presenta un recorrido no lineal donde los jugadores podrán resolver los puzzles restantes a medida que los encuentren.

El [[Puzzle de Joyas|puzzle final]] cuenta con la particularidad de necesitar las recompensas ([[Objetos Interactuables|pulseras de la amistad, cuadro de Goldina, aretes de Mirna, y salero de Mirna]]) de todos los puzzles anteriores para poder activarlo, ya que su resolución da acceso a la puerta de escape que, una vez atravesada, [[Condición de victoria y derrota|el juego finaliza]].