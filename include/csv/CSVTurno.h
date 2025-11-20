#pragma once
#include <iostream>
#include "csv/CSV.h"
#include "Turno.h"


class CSVTurno: public ArchivoCSV{
    public:
        CSVTurno();

        void guardar(Turno turno);
        void guardarTodos();
        
        Turno leerRegistro(int nroRegistro);
        Turno* leerTodo();
};
