#pragma once
#include <iostream>
#include "csv/CSV.h"
#include "TipoAnalisis.h"


class CSVTipoAnalisis: public ArchivoCSV{
    public:
        CSVTipoAnalisis();

        void guardar(TipoAnalisis tipoAnalisis);
        void guardarTodos();
        
        TipoAnalisis leerRegistro(int nroRegistro);
        TipoAnalisis* leerTodo();
};
