#include "csv/CSV.h"
#include <fstream>
#include <sstream>

ArchivoCSV::ArchivoCSV(const std::string& ruta) : _ruta(ruta) {}

int ArchivoCSV::cantidadLineasDatos() {
    std::ifstream archivo(_ruta);
    if (!archivo.is_open()) {
        return 0;
    }

    std::string linea;
    int contador = 0;

    // Saltar la primera linea (encabezado)
    std::getline(archivo, linea);

    while (std::getline(archivo, linea)) {
        contador++;
    }

    archivo.close();
    return contador;
}

bool ArchivoCSV::archivoVacio() {
    std::ifstream archivo(_ruta);
    if (!archivo.is_open()) {
        return true; // Si no se puede abrir el archivo, considerarlo vacío
    }

    std::string linea;
    bool esVacio = !std::getline(archivo, linea); // Leer la primera línea

    if (!esVacio) {
        // Si la primera línea no esta vacia, verificar si hay al menos una mas
        esVacio = !std::getline(archivo, linea);
    }

    archivo.close();
    return esVacio;
}
