#include "archivo/ArchivoTurno.h"
#include "utils/ManagerFecha.h"
#include "utils/ManagerHora.h"
#include "utils/rlutil.h"
#include <fstream>
#include <sstream>
#include <iostream>


ArchivoTurno::ArchivoTurno(): Archivo("turno.dat", "base_de_datos") {};

bool ArchivoTurno::guardar(Turno turno){
    FILE *p;

    p = fopen(this->getRutaCompleta().c_str(), "ab");

    if (p == nullptr){
        return false;
    }

    bool ok = fwrite(&turno, sizeof(Turno), 1, p);

    fclose(p);

    return ok;
}

bool ArchivoTurno::modificar(Turno turno, int pos){
    FILE *p;

    p = fopen(this->getRutaCompleta().c_str(), "rb+");

    if (p == nullptr){
        return false;
    }

    fseek(p, pos * sizeof(Turno), SEEK_SET);

    bool ok = fwrite(&turno, sizeof(Turno), 1, p);

    fclose(p);

    return ok;
}

bool ArchivoTurno::eliminar(int pos){
    Turno* aux = this->leerTodos();

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
            fwrite(&aux[i], sizeof(Turno), 1, p);
        }
    }

    fclose(p);
    delete[] aux;
    return true;
}

Turno ArchivoTurno::leer(int pos){
    Turno aux;

    FILE *p;

    p = fopen(this->getRutaCompleta().c_str(), "rb");

    if (p == nullptr){
        return aux;
    }

    fseek(p, pos * sizeof(Turno), SEEK_SET);

    fread(&aux, sizeof(Turno), 1, p);

    fclose(p);

    return aux;
}

/// @return Vector de Turno. NULL si no hay registros o no se pudo abrir el archivo.
/// Se crea con memoria dinamica. Recordar eliminar!
Turno* ArchivoTurno::leerTodos(){
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

    Turno* aux = new Turno[cantidad];

    fread(aux, sizeof(Turno), cantidad, p);

    fclose(p);

    return aux;
}

int ArchivoTurno::cantidadRegistros(){
    FILE *p;

    p = fopen(this->getRutaCompleta().c_str(), "rb");

    if (p == nullptr){
        return 0;
    }

    fseek(p, 0, SEEK_END);

    const int BYTES = ftell(p);

    fclose(p);

    return BYTES / sizeof(Turno);
}

int ArchivoTurno::getPos(int id){
    FILE *pFile;
    Turno registro;

    const int tamanioTurno = sizeof(Turno);
    int pos = -1;

    pFile = fopen(this->getRutaCompleta().c_str(), "rb");

    if(pFile == nullptr){
        return -1;  
    }
    
    while(fread(&registro, tamanioTurno, 1, pFile)) {
        if (registro.getID() == id) {
            pos = ftell(pFile) / tamanioTurno - 1;
            break;
        }
    }
    
    fclose(pFile);
    
    return pos;
}

Turno* ArchivoTurno::desdeCSV(std::string nombreArchivo) {
    std::ifstream archivo(nombreArchivo);
    std::string registro;
    std::string atributos[6];  // Son 6 los atributos de un turno

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
    Turno* turnos = new Turno[CANTIDAD];
    ManagerFecha mFecha;
    ManagerHora mHora;

    int contador = 0;
    int auxID, auxDni;
    Fecha auxFecha;
    Hora auxHora;
    float auxImporte;
    bool auxElminado;

    while (std::getline(archivo, registro)) {
        // Crear un stringstream a partir del registro para poder
        // leer todo el texto con un delimimtador
        std::stringstream ss(registro);

        for (int i = 0; i < 6; i ++) {
            std::getline(ss, atributos[i], ',');
        }

        // Interpretar atributos desde string a lo que corresponda
        auxID = std::stoi(atributos[0]);
        auxDni = std::stoi(atributos[1]);
        auxFecha = mFecha.desdeString(atributos[2]);
        auxHora = mHora.desdeString(atributos[3]);
        auxImporte = std::stof(atributos[4]);
        auxElminado = atributos[5] == "SI";

        // Cargar turno
        turnos[contador] = Turno(auxID, auxDni, auxFecha, auxHora, auxImporte);
        turnos[contador].setEliminado(auxElminado);
        contador++;
    }

    archivo.close();
    return turnos;
}
