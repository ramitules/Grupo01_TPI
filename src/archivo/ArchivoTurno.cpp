#include "archivo/ArchivoTurno.h"
#include "utils/rlutil.h"
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

bool ArchivoTurno::exportarCSV(std::string turno, std::string nombreArchivo){
    std::string cabecera = "ID,DNI Paciente,Fecha atencion,Hora atencion,Importe,Eliminado?\n";
    
    FILE *pFile;

    pFile = fopen(nombreArchivo.c_str(), "w");  // Escritura de texto, no binario

    if (pFile == nullptr){
        return false;
    }

    if (fprintf(pFile, cabecera.c_str())) {
        if (fprintf(pFile, turno.c_str())) {
            fclose(pFile);
            return true;
        }
    }

    fclose(pFile);

    return false;
}

Turno* ArchivoTurno::desdeCSV(std::string nombreArchivo) {
    // PENDIENTE
}
