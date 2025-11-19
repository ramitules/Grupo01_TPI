#pragma once
#include <iostream>
#include "csv/CSV.h"
#include "TipoAnalisis.h"


class CSVTipoAnalisis: public ArchivoCSV{
    private:
        std::string _ruta;

    public:
        CSVTipoAnalisis(const std::string& ruta);

        void guardar(TipoAnalisis tipoAnalisis);
        void guardarTodos(TipoAnalisis* tiposAnalisis, int cantidad);
        
        TipoAnalisis leerRegistro(int nroRegistro);
        TipoAnalisis* leerTodo();
};
