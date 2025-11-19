#pragma once
#include <iostream>
#include "csv/CSV.h"
#include "ObraSocial.h"


class CSVObraSocial: public ArchivoCSV{
    private:
        std::string _ruta;

    public:
        CSVObraSocial(const std::string& ruta);

        void guardar(ObraSocial obraSocial);
        void guardarTodos(ObraSocial* obraSocials, int cantidad);
        
        ObraSocial leerRegistro(int nroRegistro);
        ObraSocial* leerTodo();
};
