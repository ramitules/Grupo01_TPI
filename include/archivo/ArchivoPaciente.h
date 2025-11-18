#pragma once
#include <iostream>
#include "archivo/Archivo.h"
#include "Paciente.h"


class ArchivoPaciente: public Archivo {
    public:
        ArchivoPaciente();
        
        int getPos(int id);

        Paciente leer(int pos);
        Paciente* leerTodos();

        bool guardar(Paciente paciente);
        bool modificar(Paciente paciente, int pos);
        bool eliminar(int pos);

        /// Similar a leerTodos() solo que lee desde archivo CSV.
        /// @param nombreArchivo leera desde este nombre de archivo.
        /// @return vector de pacientes (memoria dinamica, liberar luego)
        Paciente* desdeCSV(std::string nombreArchivo);

        int cantidadRegistros();
};
