#include "archivo/ArchivoPaciente.h"
#include "utils/ManagerFecha.h"
#include <iostream>
#include <fstream>
#include <sstream>


ArchivoPaciente::ArchivoPaciente(): Archivo("paciente.dat", "base_de_datos") {};

bool ArchivoPaciente::guardar(Paciente paciente){
    FILE *p;

    p = fopen(this->getRutaCompleta().c_str(), "ab");

    if (p == nullptr){
        return false;
    }

    bool ok = fwrite(&paciente, sizeof(Paciente), 1, p);

    fclose(p);

    return ok;
}

bool ArchivoPaciente::modificar(Paciente paciente, int pos){
    FILE *p;

    p = fopen(this->getRutaCompleta().c_str(), "rb+");

    if (p == nullptr){
        return false;
    }

    fseek(p, pos * sizeof(Paciente), SEEK_SET);

    bool ok = fwrite(&paciente, sizeof(Paciente), 1, p);

    fclose(p);

    return ok;
}

bool ArchivoPaciente::eliminar(int pos){
    Paciente* aux = this->leerTodos();

    if (aux == nullptr){
        return false;
    }

    FILE *p;

    p = fopen(this->getRutaCompleta().c_str(), "wb");

    if (p == nullptr){
        delete[] aux;
        return false;
    }

    const int CANTIDAD = this->cantidadRegistros();

    for (int i = 0; i < CANTIDAD; i++){
        if (i != pos){
            fwrite(&aux[i], sizeof(Paciente), 1, p);
        }
    }

    fclose(p);
    delete[] aux;
    return true;
}

Paciente ArchivoPaciente::leer(int pos){
    Paciente aux;

    FILE *p;

    p = fopen(this->getRutaCompleta().c_str(), "rb");

    if (p == nullptr){
        return aux;
    }

    fseek(p, pos * sizeof(Paciente), SEEK_SET);

    fread(&aux, sizeof(Paciente), 1, p);

    fclose(p);

    return aux;
}

/// @return Vector de Paciente. NULL si no hay registros o no se pudo abrir el archivo.
Paciente* ArchivoPaciente::leerTodos(){
    FILE *p;

    p = fopen(this->getRutaCompleta().c_str(), "rb");

    if (p == nullptr){
        return nullptr;
    }

    const int cantidad = this->cantidadRegistros();

    if (cantidad == 0){
        fclose(p);
        return nullptr;
    }

    Paciente* aux = new Paciente[cantidad];

    fread(aux, sizeof(Paciente), cantidad, p);

    fclose(p);

    return aux;
}

int ArchivoPaciente::cantidadRegistros(){
    FILE *p;

    p = fopen(this->getRutaCompleta().c_str(), "rb");

    if (p == nullptr){
        return 0;
    }

    fseek(p, 0, SEEK_END);

    const int BYTES = ftell(p);

    fclose(p);

    return BYTES / sizeof(Paciente);
}

int ArchivoPaciente::getPos(int id){
    FILE *pFile;
    Paciente registro;

    const int tamanioPaciente = sizeof(Paciente);
    int pos = -1;

    pFile = fopen(this->getRutaCompleta().c_str(), "rb");

    if(pFile == nullptr){
        return -1;  
    }
    
    while(fread(&registro, tamanioPaciente, 1, pFile)) {
        if (registro.getDNI() == id) {
            pos = ftell(pFile) / tamanioPaciente - 1;
            break;
        }
    }
    
    fclose(pFile);
    
    return pos;
}

Paciente* ArchivoPaciente::desdeCSV(std::string nombreArchivo) {
    std::ifstream archivo(nombreArchivo);
    std::string registro;
    std::string atributos[8];
    

    if (!archivo.is_open()) {
        std::cout << "Error: No se pudo abrir el archivo " << nombreArchivo << std::endl;
        return nullptr;
    }

    // Leer el archivo registro por registro solo para saber la cantidad
    int cantidadRegistros = 0;
    while (std::getline(archivo, registro)) {
        cantidadRegistros++;
    }

    // Rebobinar
    archivo.clear(); // Limpia las banderas de estado (como EOF)
    archivo.seekg(0, std::ios::beg); // Mueve el cursor al byte 0 (el inicio)

    const int CANTIDAD = cantidadRegistros;
    Paciente* pacientes = new Paciente[CANTIDAD];

    Persona auxPersona;
    int auxDni;
    std::string auxNombre;
    std::string auxApellido;
    int auxTelefono;
    std::string auxEmail;
    Fecha auxFechaNacimiento;
    bool auxEliminado;
    int auxCodigoObraSocial;

    ManagerFecha mFecha;

    int contador = 0;

    while (std::getline(archivo, registro)) {
        // Crear un stringstream a partir del registro para poder
        // leer todo el texto con un delimimtador
        std::stringstream ss(registro);

        for (int i = 0; i < 8; i ++) {
            std::getline(ss, atributos[i], ',');
        }

        // Interpretar atributos desde string a lo que corresponda
        auxDni = std::stoi(atributos[0]);
        auxNombre = atributos[1];
        auxApellido = atributos[2];
        auxTelefono = std::stoi(atributos[3]);
        auxEmail = atributos[4];
        auxFechaNacimiento = mFecha.desdeString(atributos[5]);
        auxEliminado = atributos[6] == "SI";
        auxCodigoObraSocial = std::stoi(atributos[7]);

        // Cargar paciente
        auxPersona = Persona(auxDni, auxNombre.c_str(), auxApellido.c_str(), auxTelefono, auxEmail.c_str(), auxFechaNacimiento, auxEliminado);
        pacientes[contador] = Paciente(auxPersona, auxCodigoObraSocial);
        pacientes[contador].setEliminado(auxEliminado);
        contador++;
    }

    archivo.close();
    return pacientes;
}

