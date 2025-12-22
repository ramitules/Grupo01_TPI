#pragma once
#include "archivo/ArchivoPaciente.h"


class ManagerPaciente{
    private:
        ArchivoPaciente _repo;

    public:
        ManagerPaciente();

        Paciente seleccionar(int dniPaciente);
        bool cargar(int dniPaciente = 0);
        void mostrarUno(Paciente paciente);
        void mostrarVarios(Paciente* pacientes, const int cantidad);
        /// @return linea separadora para cabeceras y limites superior/inferior
        std::string mostrarCabecera(
            const int anchoDNI, 
            const int anchoNombre, 
            const int anchoApellido, 
            const int anchoTelefono, 
            const int anchoEmail,
            const int anchoFechaNacimiento, 
            const int anchoObraSocial
        );
        void mostrarTodos();
        bool eliminar(Paciente& paciente);
        bool actualizar(Paciente& paciente);

        void ordenadosApellido();
        void ordenadosDNI();
        void ordenadosEdad();
        void ordenadosObraSocial();

        void busquedaDNI();
        void busquedaNombreCompleto();
        void busquedaObraSocial();

        ArchivoPaciente getRepositorio();
};
