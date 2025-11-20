#pragma once
#include <iostream>
#include "csv/CSV.h"
#include "Paciente.h"


class CSVPaciente: public ArchivoCSV{
    public:
        CSVPaciente();

        void guardar(Paciente paciente);
        void guardarTodos();
        
        Paciente leerRegistro(int nroRegistro);
        Paciente* leerTodo();
};
