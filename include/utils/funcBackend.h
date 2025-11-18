#pragma once
#include <iostream>

/// Realiza un backup de todos los datos actuales presentes en la carpeta raiz del programa.
/// Pide seleccionar la carpeta donde esten los datos en caso de no encontrarlos.
void backup();


/// Restaura una copia de seguridad, pidiendo el archivo necesario.
void restaurarBackup();


/// Permite seleccionar una paleta de colores para la linea de comandos.
void paletaColores();
