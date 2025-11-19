#pragma once
#include <iostream>
#include "csv/CSV.h"
#include "Enfermero.h"


class CSVEnfermero: public ArchivoCSV{
    private:
        std::string _ruta;

    public:
        CSVEnfermero(const std::string& ruta);

        void guardar(Enfermero enfermero);
        void guardarTodos();
        
        Enfermero leerRegistro(int nroRegistro);
        Enfermero* leerTodo();
};
