#include "csv/CSVTipoAnalisis.h"
#include <fstream>
#include <sstream>
#include "utils/rlutil.h"


CSVTipoAnalisis::CSVTipoAnalisis(const std::string& ruta) : ArchivoCSV(ruta) {}

void CSVTipoAnalisis::guardar(TipoAnalisis tipoAnalisis) {
    bool vacio = archivoVacio();

    // Flujo de salida (como si fuera "cout" pero a un archivo en lugar de una linea de comandos)
    std::ofstream out(_ruta, std::ios::app);

    if (!out.is_open()) {
        std::cout << "No se pudo abrir el archivo en la ruta " << _ruta << "\n. Presione ENTER para salir.";
        rlutil::getkey();
        exit(0);
    }

    if (vacio) {
        // Encabezado
        out << "id,nombre_analisis,precio,tiempoResultado,eliminado?\n";
    }

    out << tipoAnalisis.getID() << ','
        << tipoAnalisis.getNombreAnalisis() << ','
        << tipoAnalisis.getPrecio() << ','
        << tipoAnalisis.getTiempoResultado() << ','
        << (tipoAnalisis.getEliminado() ? "Si" : "No") << '\n';

    out.close();
}

void CSVTipoAnalisis::guardarTodos(TipoAnalisis* tiposAnalisis, int cantidad) {
    std::ofstream out(_ruta, std::ios::trunc);

    if (!out.is_open()) {
        std::cout << "No se pudo abrir el archivo en la ruta " << _ruta << "\n. Presione ENTER para salir.";
        rlutil::getkey();
        exit(0);
    }

    // Encabezado
    out << "id,nombre_analisis,precio,tiempoResultado,eliminado?\n";

    for (int i = 0; i < cantidad; i++) {
        out << tiposAnalisis[i].getID() << ','
            << tiposAnalisis[i].getNombreAnalisis() << ','
            << tiposAnalisis[i].getPrecio() << ','
            << tiposAnalisis[i].getTiempoResultado() << ','
            << (tiposAnalisis[i].getEliminado() ? "Si" : "No") << '\n';
    }

    out.close();
}

TipoAnalisis CSVTipoAnalisis::leerRegistro(int nroRegistro) {
    if (nroRegistro <= 1) {
        std::cout << "Número de registro inválido. Presione ENTER para salir.";
        rlutil::getkey();
        exit(0);
    }

    const int ATRIBUTOS = 5;

    std::ifstream archivo(_ruta);
    if (!archivo.is_open()) {
        std::cout << "No se pudo abrir el archivo en la ruta " << _ruta << "\n. Presione ENTER para salir.";
        rlutil::getkey();
        exit(0);
    }

    if (archivoVacio()) {
        std::cout << "El archivo está vacío. Presione ENTER para salir.";
        rlutil::getkey();
        exit(0);
    }

    TipoAnalisis tipoAnalisis;

    std::string linea;
    std::string atributos[ATRIBUTOS];
    int lineaActual = 0;

    while (std::getline(archivo, linea)) {
        lineaActual++;

        if (lineaActual == nroRegistro) {
            std::stringstream ss(linea);
            
            for (int i = 0; i < ATRIBUTOS; i ++) {
                std::getline(ss, atributos[i], ',');
            }
            
            // IMPORTANTE: respetar el mismo orden que al guardar estos atributos en el metodo "guardar"
            tipoAnalisis.setID(std::stoi(atributos[0]));
            tipoAnalisis.setNombreAnalisis(atributos[1].c_str());
            tipoAnalisis.setPrecio(std::stof(atributos[2]));
            tipoAnalisis.setTiempoResultado(std::stoi(atributos[3]));
            tipoAnalisis.setEliminado(atributos[4] == "Si");
            break;
        }
    }

    archivo.close();
    return tipoAnalisis;
}

TipoAnalisis* CSVTipoAnalisis::leerTodo() {
    const int ATRIBUTOS = 5;
    const int CANTIDADLINEAS = cantidadLineasDatos();

    if (CANTIDADLINEAS == 0) {
        return nullptr;
    }

    TipoAnalisis* tiposAnalisis = new TipoAnalisis[CANTIDADLINEAS];

    std::ifstream archivo(_ruta);
    if (!archivo.is_open()) {
        std::cout << "No se pudo abrir el archivo en la ruta " << _ruta << "\n. Presione ENTER para salir.";
        rlutil::getkey();
        exit(0);
    }

    std::string linea;
    std::string atributos[ATRIBUTOS];

    std::getline(archivo, linea); // Saltar la primera linea (encabezado)

    for (int i = 0; i < CANTIDADLINEAS; i ++) {
        std::getline(archivo, linea);
        std::stringstream ss(linea);
        
        for (int j = 0; j < ATRIBUTOS; j ++) {
            std::getline(ss, atributos[j], ',');
        }
        
        tiposAnalisis[i].setID(std::stoi(atributos[0]));
        tiposAnalisis[i].setNombreAnalisis(atributos[1].c_str());
        tiposAnalisis[i].setPrecio(std::stof(atributos[2]));
        tiposAnalisis[i].setTiempoResultado(std::stoi(atributos[3]));
        tiposAnalisis[i].setEliminado(atributos[4] == "Si");
    }

    archivo.close();
    return tiposAnalisis;
}
