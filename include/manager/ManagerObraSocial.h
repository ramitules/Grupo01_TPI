#pragma once
#include "archivo/ArchivoObraSocial.h"


class ManagerObraSocial{
    private:
        ArchivoObraSocial _repo;

    public:
        ManagerObraSocial();

        bool cargar();
        void mostrar(ObraSocial obraSocial);
        void mostrarTodos(bool claveValor = false);
        bool eliminar(ObraSocial obraSocial);
        bool actualizar(ObraSocial obraSocial);

        ArchivoObraSocial getRepositorio();
};
