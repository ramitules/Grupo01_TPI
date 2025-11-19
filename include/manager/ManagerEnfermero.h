
#pragma once
#include "archivo/ArchivoEnfermero.h"


class ManagerEnfermero{
    private:
        ArchivoEnfermero _repo;

    public:
        ManagerEnfermero();

        bool comprobar(int dniEnfermero = -1);
        Enfermero seleccionar(int dniEnfermero);
        bool cargar();
        void mostrar(Enfermero enfermero);
        void mostrarTodos();
        bool eliminar(Enfermero enfermero);
        bool actualizar(Enfermero enfermero);
};
