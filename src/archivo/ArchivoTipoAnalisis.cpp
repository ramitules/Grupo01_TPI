#include "archivo/ArchivoTipoAnalisis.h"
#include <iostream>


ArchivoTipoAnalisis::ArchivoTipoAnalisis(): Archivo("tipoAnalisis.dat", "database") {};

bool ArchivoTipoAnalisis::guardar(TipoAnalisis tipoAnalisis){
    FILE *p;

    p = fopen(this->getRutaCompleta().c_str(), "ab");

    if (p == nullptr){
        return false;
    }

    bool ok = fwrite(&tipoAnalisis, sizeof(TipoAnalisis), 1, p);

    fclose(p);

    return ok;
}

bool ArchivoTipoAnalisis::modificar(TipoAnalisis tipoAnalisis, int pos){
    FILE *p;

    p = fopen(this->getRutaCompleta().c_str(), "rb+");

    if (p == nullptr){
        return false;
    }

    fseek(p, pos * sizeof(TipoAnalisis), SEEK_SET);

    bool ok = fwrite(&tipoAnalisis, sizeof(TipoAnalisis), 1, p);

    fclose(p);

    return ok;
}

bool ArchivoTipoAnalisis::eliminar(int pos){
    TipoAnalisis* aux = this->leerTodos();

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
            fwrite(&aux[i], sizeof(TipoAnalisis), 1, p);
        }
    }

    fclose(p);
    delete[] aux;
    return true;
}

TipoAnalisis ArchivoTipoAnalisis::leer(int pos){
    TipoAnalisis aux;

    FILE *p;

    p = fopen(this->getRutaCompleta().c_str(), "rb");

    if (p == nullptr){
        return aux;
    }

    fseek(p, pos * sizeof(TipoAnalisis), SEEK_SET);

    fread(&aux, sizeof(TipoAnalisis), 1, p);

    fclose(p);

    return aux;
}

/// @return Vector de TipoAnalisis. NULL si no hay registros o no se pudo abrir el archivo.
TipoAnalisis* ArchivoTipoAnalisis::leerTodos(){
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

    TipoAnalisis* aux = new TipoAnalisis[cantidad];

    fread(aux, sizeof(TipoAnalisis), cantidad, p);

    fclose(p);

    return aux;
}

int ArchivoTipoAnalisis::cantidadRegistros(){
    FILE *p;

    p = fopen(this->getRutaCompleta().c_str(), "rb");

    if (p == nullptr){
        return 0;
    }

    fseek(p, 0, SEEK_END);

    const int BYTES = ftell(p);

    fclose(p);

    return BYTES / sizeof(TipoAnalisis);
}

int ArchivoTipoAnalisis::getPos(int id){
    FILE *pFile;
    TipoAnalisis registro;

    const int tamanioTipoAnalisis = sizeof(TipoAnalisis);
    int pos = -1;

    pFile = fopen(this->getRutaCompleta().c_str(), "rb");

    if(pFile == nullptr){
        return -1;  
    }
    
    while(fread(&registro, tamanioTipoAnalisis, 1, pFile)) {
        if (registro.getID() == id) {
            pos = ftell(pFile) / tamanioTipoAnalisis - 1;
            break;
        }
    }
    
    fclose(pFile);
    
    return pos;
}
