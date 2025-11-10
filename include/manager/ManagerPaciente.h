#pragma once
#include "archivo/ArchivoPaciente.h"


class ManagerPaciente{
    private:
        ArchivoPaciente _repo;

    public:
        ManagerPaciente();

        bool cargar();
        void mostrar(Paciente paciente);
        void mostrarTodos();
        bool eliminar(Paciente& paciente);
        bool actualizar(Paciente& paciente);

        void ordenadosApellido();
        void ordenadosDNI();
        void ordenadosEdad();
        void ordenadosObraSocial();

        ArchivoPaciente getRepositorio();
};
