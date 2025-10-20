#include "archivo/ArchivoObraSocial.h"
#include <iostream>


ArchivoObraSocial::ArchivoObraSocial(): Archivo("obraSocial.dat", "base_de_datos") {};

bool ArchivoObraSocial::guardar(ObraSocial obraSocial){
    FILE *p;

    p = fopen(this->getRutaCompleta().c_str(), "ab");

    if (p == nullptr){
        return false;
    }

    bool ok = fwrite(&obraSocial, sizeof(ObraSocial), 1, p);

    fclose(p);

    return ok;
}

bool ArchivoObraSocial::modificar(ObraSocial obraSocial, int pos){
    FILE *p;

    p = fopen(this->getRutaCompleta().c_str(), "rb+");

    if (p == nullptr){
        return false;
    }

    fseek(p, pos * sizeof(ObraSocial), SEEK_SET);

    bool ok = fwrite(&obraSocial, sizeof(ObraSocial), 1, p);

    fclose(p);

    return ok;
}

bool ArchivoObraSocial::eliminar(int pos){
    ObraSocial* aux = this->leerTodos();

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
            fwrite(&aux[i], sizeof(ObraSocial), 1, p);
        }
    }

    fclose(p);
    delete[] aux;
    return true;
}

ObraSocial ArchivoObraSocial::leer(int pos){
    ObraSocial aux;

    FILE *p;

    p = fopen(this->getRutaCompleta().c_str(), "rb");

    if (p == nullptr){
        return aux;
    }

    fseek(p, pos * sizeof(ObraSocial), SEEK_SET);

    fread(&aux, sizeof(ObraSocial), 1, p);

    fclose(p);

    return aux;
}

/// @return Vector de ObraSocial. NULL si no hay registros o no se pudo abrir el archivo.
ObraSocial* ArchivoObraSocial::leerTodos(){
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

    ObraSocial* aux = new ObraSocial[cantidad];

    fread(aux, sizeof(ObraSocial), cantidad, p);

    fclose(p);

    return aux;
}

int ArchivoObraSocial::cantidadRegistros(){
    FILE *p;

    p = fopen(this->getRutaCompleta().c_str(), "rb");

    if (p == nullptr){
        return 0;
    }

    fseek(p, 0, SEEK_END);

    const int BYTES = ftell(p);

    fclose(p);

    return BYTES / sizeof(ObraSocial);
}

int ArchivoObraSocial::getPos(int id){
    FILE *pFile;
    ObraSocial registro;

    const int tamanioObraSocial = sizeof(ObraSocial);
    int pos = -1;

    pFile = fopen(this->getRutaCompleta().c_str(), "rb");

    if(pFile == nullptr){
        return -1;  
    }
    
    while(fread(&registro, tamanioObraSocial, 1, pFile)) {
        if (registro.getID() == id) {
            pos = ftell(pFile) / tamanioObraSocial - 1;
            break;
        }
    }
    
    fclose(pFile);
    
    return pos;
}
