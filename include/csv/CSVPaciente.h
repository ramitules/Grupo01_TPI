#pragma once
#include <iostream>
#include "csv/CSV.h"
#include "Paciente.h"


class CSVPaciente: public ArchivoCSV{
    private:
        std::string _ruta;

    public:
        CSVPaciente(const std::string& ruta);

        void guardar(Paciente paciente);
        void guardarTodos();
        
        Paciente leerRegistro(int nroRegistro);
        Paciente* leerTodo();
};
