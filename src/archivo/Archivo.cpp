#include "archivo/Archivo.h"


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
