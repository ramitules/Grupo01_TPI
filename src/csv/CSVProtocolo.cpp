#include <fstream>
#include <sstream>
#include "utils/rlutil.h"
#include "csv/CSVProtocolo.h"
#include "archivo/ArchivoProtocolo.h"


CSVProtocolo::CSVProtocolo(const std::string& ruta) : ArchivoCSV(ruta) {}

void CSVProtocolo::guardar(Protocolo protocolo) {
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
        out << "id,id_turno,dni_enfermero,sala,observaciones,estado,eliminado?\n";
    }

    out << protocolo.getId() << ','
        << protocolo.getIdTurno() << ','
        << protocolo.getDniEnfermero() << ','
        << protocolo.getSala() << ','
        << protocolo.getObservaciones() << ','
        << (protocolo.getEstado() ? "Completo" : "Incompleto") << ','
        << (protocolo.getEliminado() ? "Si" : "No") << '\n';

    out.close();
}

void CSVProtocolo::guardarTodos() {
    std::ofstream out(_ruta, std::ios::trunc);

    if (!out.is_open()) {
        std::cout << "No se pudo abrir el archivo en la ruta " << _ruta << "\n. Presione ENTER para salir.";
        rlutil::getkey();
        exit(0);
    }

    ArchivoProtocolo arProtocolo;
    const int CANTIDAD = arProtocolo.cantidadRegistros();
    Protocolo* protocolos = arProtocolo.leerTodos();

    // Encabezado
    out << "id,id_turno,dni_enfermero,sala,observaciones,estado,eliminado?\n";

    for (int i = 0; i < CANTIDAD; i++) {
        out << protocolos[i].getId() << ','
            << protocolos[i].getIdTurno() << ','
            << protocolos[i].getDniEnfermero() << ','
            << protocolos[i].getSala() << ','
            << protocolos[i].getObservaciones() << ','
            << (protocolos[i].getEstado() ? "Completo" : "Incompleto") << ','
            << (protocolos[i].getEliminado() ? "Si" : "No") << '\n';
    }

    out.close();
    delete[] protocolos;
}

Protocolo CSVProtocolo::leerRegistro(int nroRegistro) {
    if (nroRegistro <= 1) {
        std::cout << "Número de registro inválido. Presione ENTER para salir.";
        rlutil::getkey();
        exit(0);
    }

    const int ATRIBUTOS = 7;

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

    Protocolo protocolo;

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
            protocolo.setId(std::stoi(atributos[0]));
            protocolo.setIdTurno(std::stoi(atributos[1]));
            protocolo.setDniEnfermero(std::stoi(atributos[2]));
            protocolo.setSala(std::stoi(atributos[3]));
            protocolo.setObservaciones(atributos[4].c_str());
            protocolo.setEstado(atributos[5] == "Completo");
            protocolo.setEliminado(atributos[6] == "Si");
            break;
        }
    }

    archivo.close();
    return protocolo;
}

Protocolo* CSVProtocolo::leerTodo() {
    const int ATRIBUTOS = 7;
    const int CANTIDADLINEAS = cantidadLineasDatos();

    if (CANTIDADLINEAS == 0) {
        return nullptr;
    }

    Protocolo* protocolos = new Protocolo[CANTIDADLINEAS];

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
        
        protocolos[i].setId(std::stoi(atributos[0]));
        protocolos[i].setIdTurno(std::stoi(atributos[1]));
        protocolos[i].setDniEnfermero(std::stoi(atributos[2]));
        protocolos[i].setSala(std::stoi(atributos[3]));
        protocolos[i].setObservaciones(atributos[4].c_str());
        protocolos[i].setEstado(atributos[5] == "Completo");
        protocolos[i].setEliminado(atributos[6] == "Si");
    }

    archivo.close();
    return protocolos;
}
