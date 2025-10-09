#include "archivo/ArchivoAnalisis.h"
#include <iostream>


ArchivoAnalisis::ArchivoAnalisis(): Archivo("analisis.dat", "database") {};

bool ArchivoAnalisis::guardar(Analisis analisis){
    FILE *p;

    p = fopen(this->getRutaCompleta().c_str(), "ab");

    if (p == nullptr){
        return false;
    }

    bool ok = fwrite(&analisis, sizeof(Analisis), 1, p);

    fclose(p);

    return ok;
}

bool ArchivoAnalisis::modificar(Analisis analisis, int pos){
    FILE *p;

    p = fopen(this->getRutaCompleta().c_str(), "rb+");

    if (p == nullptr){
        return false;
    }

    fseek(p, pos * sizeof(Analisis), SEEK_SET);

    bool ok = fwrite(&analisis, sizeof(Analisis), 1, p);

    fclose(p);

    return ok;
}

bool ArchivoAnalisis::eliminar(int pos){
    Analisis* aux = this->leerTodos();

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
            fwrite(&aux[i], sizeof(Analisis), 1, p);
        }
    }

    fclose(p);
    delete[] aux;
    return true;
}

Analisis ArchivoAnalisis::leer(int pos){
    Analisis aux;

    FILE *p;

    p = fopen(this->getRutaCompleta().c_str(), "rb");

    if (p == nullptr){
        return aux;
    }

    fseek(p, pos * sizeof(Analisis), SEEK_SET);

    fread(&aux, sizeof(Analisis), 1, p);

    fclose(p);

    return aux;
}

/// @return Vector de Analisis. NULL si no hay registros o no se pudo abrir el archivo.
Analisis* ArchivoAnalisis::leerTodos(){
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

    Analisis* aux = new Analisis[cantidad];

    fread(aux, sizeof(Analisis), cantidad, p);

    fclose(p);

    return aux;
}

int ArchivoAnalisis::cantidadRegistros(){
    FILE *p;

    p = fopen(this->getRutaCompleta().c_str(), "rb");

    if (p == nullptr){
        return 0;
    }

    fseek(p, 0, SEEK_END);

    const int BYTES = ftell(p);

    fclose(p);

    return BYTES / sizeof(Analisis);
}

int ArchivoAnalisis::getPos(int id){
    FILE *pFile;
    Analisis registro;

    const int tamanioAnalisis = sizeof(Analisis);
    int pos = -1;

    pFile = fopen(this->getRutaCompleta().c_str(), "rb");

    if(pFile == nullptr){
        return -1;  
    }
    
    while(fread(&registro, tamanioAnalisis, 1, pFile)) {
        if (registro.getId() == id) {
            pos = ftell(pFile) / tamanioAnalisis - 1;
            break;
        }
    }
    
    fclose(pFile);
    
    return pos;
}
