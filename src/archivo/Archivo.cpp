#include "archivo/Archivo.h"
#include <sys/stat.h>


Archivo::Archivo(std::string nombreArchivo, std::string rutaArchivo): _nombreArchivo(nombreArchivo), _rutaArchivo(rutaArchivo) {};

std::string Archivo::getNombreArchivo() {
    return _nombreArchivo;
}

std::string Archivo::getRutaArchivo() {
    return _rutaArchivo;
}

void Archivo::setNombreArchivo(std::string nombreArchivo) {
    _nombreArchivo = nombreArchivo;
}

void Archivo::setRutaArchivo(std::string rutaArchivo) {
    _rutaArchivo = rutaArchivo;
}

std::string Archivo::getRutaCompleta(){
    return this->getRutaArchivo() + "/" + this->getNombreArchivo();
}

bool Archivo::existeRuta(){
    struct stat buffer;
    
    // stat() intenta obtener información sobre el archivo/directorio.
    // Retorna 0 si tiene éxito, -1 si falla (no existe).
    return stat(this->getRutaArchivo().c_str(), &buffer) == 0;
}

bool exportarCSV(std::string objeto, std::string nombreArchivo, std::string cabeceras){
    FILE *pFile;

    pFile = fopen(nombreArchivo.c_str(), "w");  // Escritura de texto, no binario

    if (pFile == nullptr){
        return false;
    }

    if (fprintf(pFile, cabeceras.c_str())) {  // Escribir texto
        if (fprintf(pFile, objeto.c_str())) {
            fclose(pFile);
            return true;
        }
    }

    fclose(pFile);

    return false;
}
