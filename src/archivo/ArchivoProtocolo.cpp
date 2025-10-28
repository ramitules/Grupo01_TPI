#include "archivo/ArchivoProtocolo.h"

ArchivoProtocolo::ArchivoProtocolo(): Archivo("archivoProtocolo.dat", "base_de_datos") {
};

bool ArchivoProtocolo::guardar(Protocolo protocolo){
    FILE *p;

    p = fopen(this->getRutaCompleta().c_str(), "ab");

    if (p == nullptr){
        return false;
    }

    bool ok = fwrite(&protocolo, sizeof(Protocolo), 1, p);

    fclose(p);

    return ok;
}

bool ArchivoProtocolo::modificar(Protocolo protocolo, int pos){
    FILE *p;

    p = fopen(this->getRutaCompleta().c_str(), "rb+");

    if (p == nullptr){
        return false;
    }

    fseek(p, pos * sizeof(Protocolo), SEEK_SET);

    bool ok = fwrite(&protocolo, sizeof(Protocolo), 1, p);

    fclose(p);

    return ok;
}

bool ArchivoProtocolo::eliminar(int pos){
    Protocolo* aux = this->leerTodos();

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
            fwrite(&aux[i], sizeof(Protocolo), 1, p);
        }
    }

    fclose(p);
    delete[] aux;
    return true;
}

Protocolo ArchivoProtocolo::leer(int pos){
    Protocolo aux;

    FILE *p;

    p = fopen(this->getRutaCompleta().c_str(), "rb");

    if (p == nullptr){
        return aux;
    }

    fseek(p, pos * sizeof(Protocolo), SEEK_SET);

    fread(&aux, sizeof(Protocolo), 1, p);

    fclose(p);

    return aux;
}

/// @return Vector de Protocolo. NULL si no hay registros o no se pudo abrir el archivo.
Protocolo* ArchivoProtocolo::leerTodos(){
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

    Protocolo* aux = new Protocolo[cantidad];

    fread(aux, sizeof(Protocolo), cantidad, p);

    fclose(p);

    return aux;
}

int ArchivoProtocolo::cantidadRegistros(){
    FILE *p;

    p = fopen(this->getRutaCompleta().c_str(), "rb");

    if (p == nullptr){
        return 0;
    }

    fseek(p, 0, SEEK_END);

    const int BYTES = ftell(p);

    fclose(p);

    return BYTES / sizeof(Protocolo);
}

int ArchivoProtocolo::getPos(int id){
    FILE *pFile;
    Protocolo registro;

    const int tamanioProtocolo = sizeof(Protocolo);
    int pos = -1;

    pFile = fopen(this->getRutaCompleta().c_str(), "rb");

    if(pFile == nullptr){
        return -1;  
    }
    
    while(fread(&registro, tamanioProtocolo, 1, pFile)) {
        if (registro.getId() == id) {
            pos = ftell(pFile) / tamanioProtocolo - 1;
            break;
        }
    }
    
    fclose(pFile);
    
    return pos;
}
