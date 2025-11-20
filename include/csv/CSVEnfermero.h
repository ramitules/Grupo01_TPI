#pragma once
#include <iostream>
#include "csv/CSV.h"
#include "Enfermero.h"


class CSVEnfermero: public ArchivoCSV{
    public:
        CSVEnfermero();

        void guardar(Enfermero enfermero);
        void guardarTodos();
        
        Enfermero leerRegistro(int nroRegistro);
        Enfermero* leerTodo();
};
