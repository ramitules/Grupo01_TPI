#pragma once
#include "archivo/ArchivoTipoAnalisis.h"


class ManagerTipoAnalisis{
    private:
        ArchivoTipoAnalisis _repo;

    public:
        ManagerTipoAnalisis();

        bool cargar();
        void mostrar(TipoAnalisis tipoAnalisis);
        void mostrarTodos();
        bool eliminar(TipoAnalisis tipoAnalisis);
        bool actualizar(TipoAnalisis tipoAnalisis);
};
