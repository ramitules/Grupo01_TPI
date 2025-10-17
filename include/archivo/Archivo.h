#pragma once
#include <iostream>


class Archivo{
    protected:
        std::string _nombreArchivo;
        std::string _rutaArchivo;

    public:
        Archivo(std::string nombreArchivo, std::string rutaArchivo);

        std::string getNombreArchivo();
        std::string getRutaArchivo();
        std::string getRutaCompleta();

        void setNombreArchivo(std::string nombreArchivo);
        void setRutaArchivo(std::string rutaArchivo);
};
