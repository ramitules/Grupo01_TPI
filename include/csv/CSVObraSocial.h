#pragma once
#include <iostream>
#include "csv/CSV.h"
#include "ObraSocial.h"


class CSVObraSocial: public ArchivoCSV{
    public:
        CSVObraSocial();

        void guardar(ObraSocial obraSocial);
        void guardarTodos();
        
        ObraSocial leerRegistro(int nroRegistro);
        ObraSocial* leerTodo();
};
