#include "archivo/ArchivoEnfermero.h"
#include <iostream>


ArchivoEnfermero::ArchivoEnfermero(): Archivo("enfermero.dat", "ruta/enfermero") {};

bool ArchivoEnfermero::guardar(Enfermero enfermero){
    FILE *p;

    p = fopen(this->getRutaCompleta().c_str(), "ab");

    if (p == nullptr){
        return false;
    }

    bool ok = fwrite(&enfermero, sizeof(Enfermero), 1, p);

    fclose(p);

    return ok;
}

bool ArchivoEnfermero::modificar(Enfermero enfermero, int pos){
    FILE *p;

    p = fopen(this->getRutaCompleta().c_str(), "rb+");

    if (p == nullptr){
        return false;
    }

    fseek(p, pos * sizeof(Enfermero), SEEK_SET);

    bool ok = fwrite(&enfermero, sizeof(Enfermero), 1, p);

    fclose(p);

    return ok;
}

bool ArchivoEnfermero::eliminar(int pos){
    Enfermero* aux = this->leerTodos();

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
            fwrite(&aux[i], sizeof(Enfermero), 1, p);
        }
    }

    fclose(p);
    delete[] aux;
    return true;
}

Enfermero ArchivoEnfermero::leer(int pos){
    Enfermero aux;

    FILE *p;

    p = fopen(this->getRutaCompleta().c_str(), "rb");

    if (p == nullptr){
        return aux;
    }

    fseek(p, pos * sizeof(Enfermero), SEEK_SET);

    fread(&aux, sizeof(Enfermero), 1, p);

    fclose(p);

    return aux;
}

/// @return Vector de Enfermero. NULL si no hay registros o no se pudo abrir el archivo.
Enfermero* ArchivoEnfermero::leerTodos(){
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

    Enfermero* aux = new Enfermero[cantidad];

    fread(aux, sizeof(Enfermero), cantidad, p);

    fclose(p);

    return aux;
}

int ArchivoEnfermero::cantidadRegistros(){
    FILE *p;

    p = fopen(this->getRutaCompleta().c_str(), "rb");

    if (p == nullptr){
        return 0;
    }

    fseek(p, 0, SEEK_END);

    const int BYTES = ftell(p);

    fclose(p);

    return BYTES / sizeof(Enfermero);
}

int ArchivoEnfermero::getPos(int dni){
    FILE *pFile;
    Enfermero registro;

    const int tamanioEnfermero = sizeof(Enfermero);
    int pos = -1;

    pFile = fopen(this->getRutaCompleta().c_str(), "rb");

    if(pFile == nullptr){
        return -1;  
    }
    
    while(fread(&registro, tamanioEnfermero, 1, pFile)) {
        if (registro.getDNI() == dni) {
            pos = ftell(pFile) / tamanioEnfermero - 1;
            break;
        }
    }
    
    fclose(pFile);
    
    return pos;
}
