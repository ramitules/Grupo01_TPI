#pragma once
#include "archivo/ArchivoTipoAnalisis.h"


class ManagerTipoAnalisis{
    private:
        ArchivoTipoAnalisis _repo;

    public:
        ManagerTipoAnalisis();

        TipoAnalisis seleccionar(int idTipoAnalisis);
        bool comprobar(int idTipoAnalisis = -1);
        bool cargar();
        void mostrar(TipoAnalisis tipoAnalisis);
        bool mostrarTodos();
        void listadoXnombre();
        void listadoXvalor();
        bool eliminar(TipoAnalisis tipoAnalisis);
        bool actualizar(TipoAnalisis tipoAnalisis);
};
