#pragma once
#include "archivo/ArchivoTipoAnalisis.h"


class ManagerTipoAnalisis{
    private:
        ArchivoTipoAnalisis _repo;

    public:
        ManagerTipoAnalisis();

        TipoAnalisis seleccionar();
        bool cargar();
        void mostrar(TipoAnalisis tipoAnalisis);
        bool mostrarTodos();
        bool eliminar(TipoAnalisis tipoAnalisis);
        bool actualizar(TipoAnalisis tipoAnalisis);
};
