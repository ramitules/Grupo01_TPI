#include "archivo/ArchivoTurno.h"
#include <iostream>


ArchivoTurno::ArchivoTurno(): Archivo("turno.dat", "database") {};

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
