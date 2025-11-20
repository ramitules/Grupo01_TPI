
#pragma once
#include "archivo/ArchivoEnfermero.h"


class ManagerEnfermero{
    private:
        ArchivoEnfermero _repo;

    public:
        ManagerEnfermero();

        bool comprobar(int dniEnfermero = -1);
        Enfermero seleccionar(int dniEnfermero);

        bool cargar(int dniEnfermero = 0);
        void mostarUno(Enfermero enfermero);
        void mostrarVarios(Enfermero* enfermeros, const int cantidad);
        /// @return linea separadora para cabeceras y limites superior/inferior
        std::string mostrarCabecera(
            const int anchoDNI, 
            const int anchoNombre, 
            const int anchoApellido, 
            const int anchoTelefono, 
            const int anchoEmail,
            const int anchoFecha
        );
        void mostrarTodos();
        bool eliminar(Enfermero& enfermero);
        bool actualizar(Enfermero& enfermero);

        void ordenadosApellido();
        void ordenadosDNI();
        void ordenadosAntiguedad();
        ArchivoEnfermero getRepositorio();
};
