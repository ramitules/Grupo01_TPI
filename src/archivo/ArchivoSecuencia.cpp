#include "archivo/ArchivoSecuencia.h"
#include <iostream>
#include <cstring>


ArchivoSecuencia::ArchivoSecuencia(): Archivo("secuencia.dat", "base_de_datos") {};

bool ArchivoSecuencia::guardar(Secuencia secuencia){
    FILE *p;

    p = fopen(this->getRutaCompleta().c_str(), "ab");

    if (p == nullptr){
        return false;
    }

    bool ok = fwrite(&secuencia, sizeof(Secuencia), 1, p);

    fclose(p);

    return ok;
}

bool ArchivoSecuencia::modificar(Secuencia secuencia, int pos){
    FILE *p;

    p = fopen(this->getRutaCompleta().c_str(), "rb+");

    if (p == nullptr){
        return false;
    }

    fseek(p, pos * sizeof(Secuencia), SEEK_SET);

    bool ok = fwrite(&secuencia, sizeof(Secuencia), 1, p);

    fclose(p);

    return ok;
}

bool ArchivoSecuencia::eliminar(int pos){
    Secuencia* aux = this->leerTodos();

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
            fwrite(&aux[i], sizeof(Secuencia), 1, p);
        }
    }

    fclose(p);
    delete[] aux;
    return true;
}

Secuencia ArchivoSecuencia::leer(int pos){
    Secuencia aux;

    FILE *p;

    p = fopen(this->getRutaCompleta().c_str(), "rb");

    if (p == nullptr){
        return aux;
    }

    fseek(p, pos * sizeof(Secuencia), SEEK_SET);

    fread(&aux, sizeof(Secuencia), 1, p);

    fclose(p);

    return aux;
}

/// @return Vector de Secuencia. NULL si no hay registros o no se pudo abrir el archivo.
Secuencia* ArchivoSecuencia::leerTodos(){
    FILE *p;

    p = fopen(this->getRutaCompleta().c_str(), "rb");

    if (p == nullptr){
        return nullptr;
    }

    const int CANTIDAD = this->cantidadRegistros();

    if (CANTIDAD == 0){
        fclose(p);
        return nullptr;
    }

    Secuencia* aux = new Secuencia[CANTIDAD];

    fread(aux, sizeof(Secuencia), CANTIDAD, p);

    fclose(p);

    return aux;
}

int ArchivoSecuencia::cantidadRegistros(){
    FILE *p;

    p = fopen(this->getRutaCompleta().c_str(), "rb");

    if (p == nullptr){
        return 0;
    }

    fseek(p, 0, SEEK_END);

    const int BYTES = ftell(p);

    fclose(p);

    return BYTES / sizeof(Secuencia);
}

int ArchivoSecuencia::getPos(int id){
    FILE *pFile;
    Secuencia registro;

    const int tamanioSecuencia = sizeof(Secuencia);
    int pos = -1;

    pFile = fopen(this->getRutaCompleta().c_str(), "rb");

    if(pFile == nullptr){
        return -1;  
    }
    
    while(fread(&registro, tamanioSecuencia, 1, pFile)) {
        if (registro.getId() == id) {
            pos = ftell(pFile) / tamanioSecuencia - 1;
            break;
        }
    }
    
    fclose(pFile);
    
    return pos;
}
