#pragma once
#include "archivo/ArchivoTurno.h"


class ManagerTurno{
    private:
        ArchivoTurno _repo;

    public:
        ManagerTurno();

        bool cargar();
        void mostrar(Turno turno);
        void mostrarTodos();
        bool eliminar(Turno turno);
        bool actualizar(Turno turno);

        ArchivoTurno getRepositorio();
};
