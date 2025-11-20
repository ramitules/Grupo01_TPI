#pragma once
#include "archivo/ArchivoObraSocial.h"


class ManagerObraSocial{
    private:
        ArchivoObraSocial _repo;

    public:
        ManagerObraSocial();

        bool cargar();
        void mostrarUno(ObraSocial obraSocial);
        void mostrarVarios(ObraSocial* obrasSociales, const int cantidad);
        /// @return linea separadora para cabeceras y limites superior/inferior
        std::string mostrarCabecera(const int anchoNombre, const int anchoContacto, const int anchoTelefono, const int anchoEmail);
        void mostrarTodos(bool claveValor = false);
        bool eliminar(ObraSocial obraSocial);
        bool actualizar(ObraSocial obraSocial);

        ArchivoObraSocial getRepositorio();

        void ordenadosNombre();
        void agrupadosPacientes();
};
