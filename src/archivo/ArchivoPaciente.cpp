#include "archivo/ArchivoPaciente.h"
#include <iostream>


ArchivoPaciente::ArchivoPaciente(): Archivo("paciente.dat", "database") {};

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
