#include "csv/CSVAnalisisProtocolo.h"
#include <fstream>
#include <sstream>
#include "utils/rlutil.h"

CSVAnalisisProtocolo::CSVAnalisisProtocolo(const std::string& ruta) : ArchivoCSV(ruta) {}

void CSVAnalisisProtocolo::guardar(AnalisisProtocolo analisisProtocolo) {
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
        out << "id_protocolo,id_tipo_analisis,precio_solicitud,resultados,eliminado?\n";
    }

    out << analisisProtocolo.getIdProtocolo() << ','
        << analisisProtocolo.getIdTipoAnalisis() << ','
        << analisisProtocolo.getPrecioSolicitud() << ','
        << analisisProtocolo.getResultado() << ','
        << (analisisProtocolo.getEliminado() ? "Si" : "No") << '\n';

    out.close();
}

void CSVAnalisisProtocolo::guardarTodos(AnalisisProtocolo* analisisProtocolos, int cantidad) {
    std::ofstream out(_ruta, std::ios::trunc);

    if (!out.is_open()) {
        std::cout << "No se pudo abrir el archivo en la ruta " << _ruta << "\n. Presione ENTER para salir.";
        rlutil::getkey();
        exit(0);
    }

    // Encabezado
    out << "id_protocolo,id_tipo_analisis,precio_solicitud,resultados,eliminado?\n";

    for (int i = 0; i < cantidad; i++) {
        out << analisisProtocolos[i].getIdProtocolo() << ','
            << analisisProtocolos[i].getIdTipoAnalisis() << ','
            << analisisProtocolos[i].getPrecioSolicitud() << ','
            << analisisProtocolos[i].getResultado() << ','
            << (analisisProtocolos[i].getEliminado() ? "Si" : "No") << '\n';
    }

    out.close();
}

AnalisisProtocolo CSVAnalisisProtocolo::leerRegistro(int nroRegistro) {
    const int ATRIBUTOS = 5;
    if (nroRegistro <= 1) {
        std::cout << "Número de registro inválido. Presione ENTER para salir.";
        rlutil::getkey();
        exit(0);
    }

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

    AnalisisProtocolo analisis;

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
            analisis.setIdProtocolo(std::stoi(atributos[0]));
            analisis.setIdTipoAnalisis(std::stoi(atributos[1]));
            analisis.setPrecioSolicitud(std::stof(atributos[2]));
            analisis.setResultados(atributos[3].c_str());
            analisis.setEliminado(atributos[4] == "Si");
            break;
        }
    }

    archivo.close();
    return analisis;
}

AnalisisProtocolo* CSVAnalisisProtocolo::leerTodo() {
    const int CANTIDADLINEAS = cantidadLineasDatos();

    if (CANTIDADLINEAS == 0) {
        return nullptr;
    }

    AnalisisProtocolo* analisisProtocolos = new AnalisisProtocolo[CANTIDADLINEAS];

    std::ifstream archivo(_ruta);
    if (!archivo.is_open()) {
        std::cout << "No se pudo abrir el archivo en la ruta " << _ruta << "\n. Presione ENTER para salir.";
        rlutil::getkey();
        exit(0);
    }

    std::string linea;
    std::string atributos[5];

    std::getline(archivo, linea); // Saltar la primera linea (encabezado)

    for (int i = 0; i < CANTIDADLINEAS; i ++) {
        std::getline(archivo, linea);
        std::stringstream ss(linea);
        
        for (int j = 0; j < 5; j ++) {
            std::getline(ss, atributos[j], ',');
        }
        
        analisisProtocolos[i].setIdProtocolo(std::stoi(atributos[0]));
        analisisProtocolos[i].setIdTipoAnalisis(std::stoi(atributos[1]));
        analisisProtocolos[i].setPrecioSolicitud(std::stof(atributos[2]));
        analisisProtocolos[i].setResultados(atributos[3].c_str());
        analisisProtocolos[i].setEliminado(atributos[4] == "Si");
    }

    archivo.close();
    return analisisProtocolos;
}
