#include "archivo/ArchivoAnalisisProtocolo.h"

ArchivoAnalisisProtocolo::ArchivoAnalisisProtocolo(): Archivo("archivoAnalisisProtocolo.dat", "base_de_datos") {
};

bool ArchivoAnalisisProtocolo::guardar(AnalisisProtocolo analisisProtocolo){
    FILE *p;

    p = fopen(this->getRutaCompleta().c_str(), "ab");

    if (p == nullptr){
        return false;
    }

    bool ok = fwrite(&analisisProtocolo, sizeof(AnalisisProtocolo), 1, p);

    fclose(p);

    return ok;
}

bool ArchivoAnalisisProtocolo::modificar(AnalisisProtocolo analisisProtocolo, int pos){
    FILE *p;

    p = fopen(this->getRutaCompleta().c_str(), "rb+");

    if (p == nullptr){
        return false;
    }

    fseek(p, pos * sizeof(AnalisisProtocolo), SEEK_SET);

    bool ok = fwrite(&analisisProtocolo, sizeof(AnalisisProtocolo), 1, p);

    fclose(p);

    return ok;
}

bool ArchivoAnalisisProtocolo::eliminar(int pos){
    AnalisisProtocolo* aux = this->leerTodos();

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
            fwrite(&aux[i], sizeof(AnalisisProtocolo), 1, p);
        }
    }

    fclose(p);
    delete[] aux;
    return true;
}

AnalisisProtocolo ArchivoAnalisisProtocolo::leer(int pos){
    AnalisisProtocolo aux;

    FILE *p;

    p = fopen(this->getRutaCompleta().c_str(), "rb");

    if (p == nullptr){
        return aux;
    }

    fseek(p, pos * sizeof(AnalisisProtocolo), SEEK_SET);

    fread(&aux, sizeof(AnalisisProtocolo), 1, p);

    fclose(p);

    return aux;
}

/// @return Vector de AnalisisProtocolo. NULL si no hay registros o no se pudo abrir el archivo.
AnalisisProtocolo* ArchivoAnalisisProtocolo::leerTodos(){
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

    AnalisisProtocolo* aux = new AnalisisProtocolo[cantidad];

    fread(aux, sizeof(AnalisisProtocolo), cantidad, p);

    fclose(p);

    return aux;
}

int ArchivoAnalisisProtocolo::cantidadRegistros(){
    FILE *p;

    p = fopen(this->getRutaCompleta().c_str(), "rb");

    if (p == nullptr){
        return 0;
    }

    fseek(p, 0, SEEK_END);

    const int BYTES = ftell(p);

    fclose(p);

    return BYTES / sizeof(AnalisisProtocolo);
}

int ArchivoAnalisisProtocolo::getPos(int id){
    FILE *pFile;
    AnalisisProtocolo registro;

    const int tamanioAnalisisProtocolo = sizeof(AnalisisProtocolo);
    int pos = -1;

    pFile = fopen(this->getRutaCompleta().c_str(), "rb");

    if(pFile == nullptr){
        return -1;  
    }
    
    while(fread(&registro, tamanioAnalisisProtocolo, 1, pFile)) {
        if (registro.getIdProtocolo() == id) {
            pos = ftell(pFile) / tamanioAnalisisProtocolo - 1;
            break;
        }
    }
    
    fclose(pFile);
    
    return pos;
}
