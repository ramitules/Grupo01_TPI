#pragma once
#include "archivo/ArchivoEnfermero.h"


class ManagerEnfermero{
    private:
        ArchivoEnfermero _repo;

    public:
        ManagerEnfermero();

        bool cargar();
        void mostrar(Enfermero enfermero);
        void mostrarTodos();
        bool eliminar(Enfermero enfermero);
        bool actualizar(Enfermero enfermero);
};
