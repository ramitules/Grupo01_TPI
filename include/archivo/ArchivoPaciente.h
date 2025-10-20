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

        int cantidadRegistros();
};
