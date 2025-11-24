#pragma once
#include "archivo/ArchivoTipoAnalisis.h"


class ManagerTipoAnalisis{
    private:
        ArchivoTipoAnalisis _repo;

    public:
        ManagerTipoAnalisis();

        TipoAnalisis seleccionar(int idTipoAnalisis);
        bool comprobar(int idTipoAnalisis = -1);
        void mostrar(TipoAnalisis tipoAnalisis);
        void mostrarTodos();

        bool ingresarDatos(TipoAnalisis &tipoAnalisis, bool nuevoId = false);
        bool cargarDatos(TipoAnalisis tipoAnalisis);

        void listadoXnombre();
        void listadoXvalor();

        bool actualizar(TipoAnalisis tipoAnalisis);
        bool eliminar(TipoAnalisis tipoAnalisis);
};
