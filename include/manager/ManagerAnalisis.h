#pragma once
#include "archivo/ArchivoAnalisis.h"


class ManagerAnalisis{
    private:
        ArchivoAnalisis _repo;

    public:
        ManagerAnalisis();

        bool cargar();
        void mostrar(Analisis analisis);
        void mostrarTodos();
        bool eliminar(Analisis analisis);
        bool actualizar(Analisis analisis);
};
