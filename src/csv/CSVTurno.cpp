#include <fstream>
#include <sstream>
#include "utils/rlutil.h"
#include "csv/CSVTurno.h"
#include "archivo/ArchivoTurno.h"


CSVTurno::CSVTurno() : ArchivoCSV("backup_turnos.csv") {}

void CSVTurno::guardar(Turno turno) {
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
        out << "id,dni_paciente,fecha_atencion,hora_atencion,importe,eliminado?\n";
    }

    out << turno.getID() << ','
        << turno.getDniPaciente() << ','
        << turno.getFechaAtencion().to_str() << ','
        << turno.getHoraAtencion().to_str() << ','
        << turno.getImporte() << ','
        << (turno.getEliminado() ? "Si" : "No") << '\n';

    out.close();
}

void CSVTurno::guardarTodos() {
    ArchivoTurno archivoTurno;
    
    const int CANTIDAD = archivoTurno.cantidadRegistros();
    if (CANTIDAD == 0) {
        return;
    }

    std::ofstream out(_ruta, std::ios::trunc);

    if (!out.is_open()) {
        std::cout << "No se pudo abrir el archivo en la ruta " << _ruta << ".\nPresione ENTER para salir.";
        rlutil::anykey();
        exit(0);
    }
    
    Turno* turnos = archivoTurno.leerTodos();

    // Encabezado
    out << "id,dni_paciente,fecha_atencion,hora_atencion,importe,eliminado?\n";

    for (int i = 0; i < CANTIDAD; i++) {
        out << turnos[i].getID() << ','
            << turnos[i].getDniPaciente() << ','
            << turnos[i].getFechaAtencion().to_str() << ','
            << turnos[i].getHoraAtencion().to_str() << ','
            << turnos[i].getImporte() << ','
            << (turnos[i].getEliminado() ? "Si" : "No") << '\n';
    }

    out.close();
    delete[] turnos;
}

Turno CSVTurno::leerRegistro(int nroRegistro) {
    if (nroRegistro <= 1) {
        std::cout << "Número de registro inválido. Presione ENTER para salir.";
        rlutil::anykey();
        exit(0);
    }

    const int ATRIBUTOS = 6;

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

    Turno turno;

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
            turno.setID(std::stoi(atributos[0]));
            turno.setDniPaciente(std::stoi(atributos[1]));
            turno.setFechaAtencion(Fecha(atributos[2].c_str()));
            turno.setHoraAtencion(Hora(atributos[3].c_str()));
            turno.setImporte(std::stof(atributos[4]));
            turno.setEliminado(atributos[5] == "Si");
            break;
        }
    }

    archivo.close();
    return turno;
}

Turno* CSVTurno::leerTodo() {
    const int ATRIBUTOS = 6;
    const int CANTIDADLINEAS = cantidadLineasDatos();

    if (CANTIDADLINEAS == 0) {
        return nullptr;
    }

    Turno* turnos = new Turno[CANTIDADLINEAS];

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
        
        turnos[i].setID(std::stoi(atributos[0]));
        turnos[i].setDniPaciente(std::stoi(atributos[1]));
        turnos[i].setFechaAtencion(Fecha(atributos[2].c_str()));
        turnos[i].setHoraAtencion(Hora(atributos[3].c_str()));
        turnos[i].setImporte(std::stof(atributos[4]));
        turnos[i].setEliminado(atributos[5] == "Si");
    }

    archivo.close();
    return turnos;
}
