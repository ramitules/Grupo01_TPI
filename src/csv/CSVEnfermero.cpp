#include <fstream>
#include <sstream>
#include "utils/rlutil.h"
#include "csv/CSVEnfermero.h"
#include "archivo/ArchivoEnfermero.h"


CSVEnfermero::CSVEnfermero() : ArchivoCSV("backup_enfermero.csv") {}

void CSVEnfermero::guardar(Enfermero enfermero) {
    bool vacio = archivoVacio();

    // Flujo de salida (como si fuera "cout" pero a un archivo en lugar de una linea de comandos)
    std::ofstream out(_ruta, std::ios::app);

    if (!out.is_open()) {
        std::cout << "No se pudo abrir el archivo en la ruta " << _ruta << "\n. Presione ENTER para salir.";
        rlutil::anykey();
        exit(0);
    }

    if (vacio) {
        // Encabezado
        out << "dni_enfermero,nombre,apellido,telefono,email,fecha_nacimiento,habilitado?,fecha_ingreso,eliminado?\n";
    }

    out << enfermero.getDNI() << ','
        << enfermero.getNombre() << ','
        << enfermero.getApellido() << ','
        << enfermero.getTelefono() << ','
        << enfermero.getEmail() << ','
        << enfermero.getFechaNacimiento().to_str() << ','
        << (enfermero.getHabilitado() ? "Si" : "No") << ','
        << enfermero.getFechaIngreso().to_str() << ','
        << (enfermero.getEliminado() ? "Si" : "No") << '\n';
        
    out.close();
}

void CSVEnfermero::guardarTodos() {
    ArchivoEnfermero arEnfermero;

    const int CANTIDAD = arEnfermero.cantidadRegistros();
    if (CANTIDAD == 0) {
        return;
    }

    std::ofstream out(_ruta, std::ios::trunc);

    if (!out.is_open()) {
        std::cout << "No se pudo abrir el archivo en la ruta " << _ruta << "\n. Presione ENTER para salir.";
        rlutil::anykey();
        exit(0);
    }
    
    Enfermero* enfermeros = arEnfermero.leerTodos();

    // Encabezado
    out << "dni_enfermero,nombre,apellido,telefono,email,fecha_nacimiento,habilitado?,fecha_ingreso,eliminado?\n";

    for (int i = 0; i < CANTIDAD; i++) {
        out << enfermeros[i].getDNI() << ','
            << enfermeros[i].getNombre() << ','
            << enfermeros[i].getApellido() << ','
            << enfermeros[i].getTelefono() << ','
            << enfermeros[i].getEmail() << ','
            << enfermeros[i].getFechaNacimiento().to_str() << ','
            << (enfermeros[i].getHabilitado() ? "Si" : "No") << ','
            << enfermeros[i].getFechaIngreso().to_str() << ','
            << (enfermeros[i].getEliminado() ? "Si" : "No") << '\n';
    }

    out.close();
    delete[] enfermeros;
}

Enfermero CSVEnfermero::leerRegistro(int nroRegistro) {
    if (nroRegistro <= 1) {
        std::cout << "Número de registro inválido. Presione ENTER para salir.";
        rlutil::anykey();
        exit(0);
    }

    const int ATRIBUTOS = 9;

    std::ifstream archivo(_ruta);
    if (!archivo.is_open()) {
        std::cout << "No se pudo abrir el archivo en la ruta " << _ruta << "\n. Presione ENTER para salir.";
        rlutil::anykey();
        exit(0);
    }

    if (archivoVacio()) {
        std::cout << "El archivo está vacío. Presione ENTER para salir.";
        rlutil::anykey();
        exit(0);
    }

    Enfermero enfermero;

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
            enfermero.setDNI(std::stoi(atributos[0]));
            enfermero.setNombre(atributos[1].c_str());
            enfermero.setApellido(atributos[2].c_str());
            enfermero.setTelefono(std::stoi(atributos[3]));
            enfermero.setEmail(atributos[4].c_str());
            enfermero.setFechaNacimiento(Fecha(atributos[5].c_str()));
            enfermero.setHabilitado(atributos[6] == "Si");
            enfermero.setFechaIngreso(Fecha(atributos[7].c_str()));
            enfermero.setEliminado(atributos[8] == "Si");
            break;
        }
    }

    archivo.close();
    return enfermero;
}

Enfermero* CSVEnfermero::leerTodo() {
    const int ATRIBUTOS = 9;
    const int CANTIDADLINEAS = cantidadLineasDatos();

    if (CANTIDADLINEAS == 0) {
        return nullptr;
    }

    Enfermero* enfermeros = new Enfermero[CANTIDADLINEAS];

    std::ifstream archivo(_ruta);
    if (!archivo.is_open()) {
        std::cout << "No se pudo abrir el archivo en la ruta " << _ruta << "\n. Presione ENTER para salir.";
        rlutil::anykey();
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
        
        enfermeros[i].setDNI(std::stoi(atributos[0]));
        enfermeros[i].setNombre(atributos[1].c_str());
        enfermeros[i].setApellido(atributos[2].c_str());
        enfermeros[i].setTelefono(std::stoi(atributos[3]));
        enfermeros[i].setEmail(atributos[4].c_str());
        enfermeros[i].setFechaNacimiento(Fecha(atributos[5].c_str()));
        enfermeros[i].setHabilitado(atributos[6] == "Si");
        enfermeros[i].setFechaIngreso(Fecha(atributos[7].c_str()));
        enfermeros[i].setEliminado(atributos[8] == "Si");
    }

    archivo.close();
    return enfermeros;
}
