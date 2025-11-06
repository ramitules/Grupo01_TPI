#pragma once
#include <iostream>


// Muestra en pantalla una leyenda "Buscando . . ." con pausas entre puntos suspensivos
// para simular pensamiento y busqueda compleja.
void buscando();

// Dibuja un separador horizontal completo en donde este el cursor actualmente. Termina con un salto de linea.
// Recomendacion:
// std::cout << separador();
std::string separador();

// Dibuja un separador horizontal ocupando media pantalla en donde este el cursor actualmente.
// Termina con un salto de linea.
// Recomendacion:
// std::cout << separador();
std::string separadorParcial();
