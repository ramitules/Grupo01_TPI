#pragma once
#include <iostream>
#include "csv/CSV.h"
#include "Turno.h"


class CSVTurno: public ArchivoCSV{
    private:
        std::string _ruta;

    public:
        CSVTurno(const std::string& ruta);

        void guardar(Turno turno);
        void guardarTodos();
        
        Turno leerRegistro(int nroRegistro);
        Turno* leerTodo();
};
