#include <fstream>
#include <sstream>

#include "csv/CSVObraSocial.h"
#include "archivo/ArchivoObraSocial.h"


CSVObraSocial::CSVObraSocial() : ArchivoCSV("backup_obra_social.csv") {}

void CSVObraSocial::guardar(ObraSocial obraSocial) {
    bool vacio = archivoVacio();

    // Flujo de salida (como si fuera "cout" pero a un archivo en lugar de una linea de comandos)
    std::ofstream out(_ruta, std::ios::app);

    if (!out.is_open()) {
        std::cout << "No se pudo abrir el archivo en la ruta " << _ruta << "\n. Presione ENTER para salir.";
        std::cin.get();
        exit(0);
    }

    if (vacio) {
        // Encabezado
        out << "id,nombre,nombre_contacto,telefono,email,eliminado?\n";
    }

    out << obraSocial.getID() << ','
        << obraSocial.getNombre() << ','
        << obraSocial.getNombreContacto() << ','
        << obraSocial.getTelefono() << ','
        << obraSocial.getEmail() << ','
        << (obraSocial.getEliminado() ? "Si" : "No") << '\n';

    out.close();
}

void CSVObraSocial::guardarTodos() {
    ArchivoObraSocial archivoOS;

    const int CANTIDAD = archivoOS.cantidadRegistros();
    if (CANTIDAD == 0) {
        return;
    }

    std::ofstream out(_ruta, std::ios::trunc);

    if (!out.is_open()) {
        std::cout << "No se pudo abrir el archivo en la ruta " << _ruta << "\n. Presione ENTER para salir.";
        std::cin.get();
        exit(0);
    }
    
    ObraSocial* obraSociales = archivoOS.leerTodos();

    // Encabezado
    out << "id,nombre,nombre_contacto,telefono,email,eliminado?\n";

    for (int i = 0; i < CANTIDAD; i++) {
        out << obraSociales[i].getID() << ','
            << obraSociales[i].getNombre() << ','
            << obraSociales[i].getNombreContacto() << ','
            << obraSociales[i].getTelefono() << ','
            << obraSociales[i].getEmail() << ','
            << (obraSociales[i].getEliminado() ? "Si" : "No") << '\n';
    }

    out.close();
    delete[] obraSociales;
}

ObraSocial CSVObraSocial::leerRegistro(int nroRegistro) {
    if (nroRegistro <= 1) {
        std::cout << "Número de registro inválido. Presione ENTER para salir.";
        std::cin.get();
        exit(0);
    }

    const int ATRIBUTOS = 6;

    std::ifstream archivo(_ruta);
    if (!archivo.is_open()) {
        std::cout << "No se pudo abrir el archivo en la ruta " << _ruta << "\n. Presione ENTER para salir.";
        std::cin.get();
        exit(0);
    }

    if (archivoVacio()) {
        std::cout << "El archivo está vacío. Presione ENTER para salir.";
        std::cin.get();
        exit(0);
    }

    ObraSocial obraSocial;

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
            obraSocial.setID(std::stoi(atributos[0]));
            obraSocial.setNombre(atributos[1].c_str());
            obraSocial.setNombreContacto(atributos[2].c_str());
            obraSocial.setTelefono(std::stoi(atributos[3]));
            obraSocial.setEmail(atributos[4].c_str());
            obraSocial.setEliminado(atributos[5] == "Si");
            break;
        }
    }

    archivo.close();
    return obraSocial;
}

ObraSocial* CSVObraSocial::leerTodo() {
    const int ATRIBUTOS = 6;
    const int CANTIDADLINEAS = cantidadLineasDatos();

    if (CANTIDADLINEAS == 0) {
        return nullptr;
    }

    ObraSocial* obraSociales = new ObraSocial[CANTIDADLINEAS];

    std::ifstream archivo(_ruta);
    if (!archivo.is_open()) {
        std::cout << "No se pudo abrir el archivo en la ruta " << _ruta << "\n. Presione ENTER para salir.";
        std::cin.get();
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
        
        obraSociales[i].setID(std::stoi(atributos[0]));
        obraSociales[i].setNombre(atributos[1].c_str());
        obraSociales[i].setNombreContacto(atributos[2].c_str());
        obraSociales[i].setTelefono(std::stoi(atributos[3]));
        obraSociales[i].setEmail(atributos[4].c_str());
        obraSociales[i].setEliminado(atributos[5] == "Si");
    }

    archivo.close();
    return obraSociales;
}
