#pragma once
#include <iostream>


class ArchivoCSV {
    protected:
        std::string _ruta;

    public:
        ArchivoCSV(const std::string ruta);

        int cantidadLineasDatos();
        bool archivoVacio();

        std::string getRuta();
};
