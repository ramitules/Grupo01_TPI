#pragma once
#include <iostream>


class ArchivoCSV {
    private:
        std::string _ruta;

    public:
        ArchivoCSV(const std::string& ruta);

        int cantidadLineasDatos();
        bool archivoVacio();
};
