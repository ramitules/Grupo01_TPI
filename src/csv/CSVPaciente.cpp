#include <fstream>
#include <sstream>
#include "utils/rlutil.h"
#include "csv/CSVPaciente.h"
#include "archivo/ArchivoPaciente.h"


CSVPaciente::CSVPaciente(const std::string& ruta) : ArchivoCSV(ruta) {}

void CSVPaciente::guardar(Paciente paciente) {
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
        out << "dni,nombre,apellido,telefono,email,fecha_nacimiento,codigo_obra_social,eliminado?\n";
    }

    out << paciente.getDNI() << ','
        << paciente.getNombre() << ','
        << paciente.getApellido() << ','
        << paciente.getTelefono() << ','
        << paciente.getEmail() << ','
        << paciente.getFechaNacimiento().to_str() << ','
        << paciente.getCodigoObraSocial() << ','
        << (paciente.getEliminado() ? "Si" : "No") << '\n';

    out.close();
}

void CSVPaciente::guardarTodos() {
    std::ofstream out(_ruta, std::ios::trunc);

    if (!out.is_open()) {
        std::cout << "No se pudo abrir el archivo en la ruta " << _ruta << "\n. Presione ENTER para salir.";
        rlutil::anykey();
        exit(0);
    }

    ArchivoPaciente arPaciente;
    
    const int CANTIDAD = arPaciente.cantidadRegistros();
    if (CANTIDAD == 0) {
        out.close();
        return;
    }
    
    Paciente* pacientes = arPaciente.leerTodos();
    // Encabezado
    out << "dni,nombre,apellido,telefono,email,fecha_nacimiento,codigo_obra_social,eliminado?\n";

    for (int i = 0; i < CANTIDAD; i++) {
        out << pacientes[i].getDNI() << ','
            << pacientes[i].getNombre() << ','
            << pacientes[i].getApellido() << ','
            << pacientes[i].getTelefono() << ','
            << pacientes[i].getEmail() << ','
            << pacientes[i].getFechaNacimiento().to_str() << ','
            << pacientes[i].getCodigoObraSocial() << ','
            << (pacientes[i].getEliminado() ? "Si" : "No") << '\n';
    }

    out.close();
    delete[] pacientes;
}

Paciente CSVPaciente::leerRegistro(int nroRegistro) {
    if (nroRegistro <= 1) {
        std::cout << "Número de registro inválido. Presione ENTER para salir.";
        rlutil::anykey();
        exit(0);
    }

    const int ATRIBUTOS = 8;

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

    Paciente paciente;

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
            paciente.setDNI(std::stoi(atributos[0]));
            paciente.setNombre(atributos[1].c_str());
            paciente.setApellido(atributos[2].c_str());
            paciente.setTelefono(std::stoi(atributos[3]));
            paciente.setEmail(atributos[4].c_str());
            paciente.setFechaNacimiento(Fecha(atributos[5].c_str()));
            paciente.setCodigoObraSocial(std::stoi(atributos[6]));
            paciente.setEliminado(atributos[7] == "Si");
            break;
        }
    }

    archivo.close();
    return paciente;
}

Paciente* CSVPaciente::leerTodo() {
    const int ATRIBUTOS = 8;
    const int CANTIDADLINEAS = cantidadLineasDatos();

    if (CANTIDADLINEAS == 0) {
        return nullptr;
    }

    Paciente* pacientes = new Paciente[CANTIDADLINEAS];

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
        
        pacientes[i].setDNI(std::stoi(atributos[0]));
        pacientes[i].setNombre(atributos[1].c_str());
        pacientes[i].setApellido(atributos[2].c_str());
        pacientes[i].setTelefono(std::stoi(atributos[3]));
        pacientes[i].setEmail(atributos[4].c_str());
        pacientes[i].setFechaNacimiento(Fecha(atributos[5].c_str()));
        pacientes[i].setCodigoObraSocial(std::stoi(atributos[6]));
        pacientes[i].setEliminado(atributos[7] == "Si");
    }

    archivo.close();
    return pacientes;
}
