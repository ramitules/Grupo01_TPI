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

        // Chequea si existe el directorio donde se guardara la base de datos.
        // No necesita un nombre de archivo.
        bool existeRuta();
};
