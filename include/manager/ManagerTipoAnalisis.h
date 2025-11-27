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
        std::string mostrarCabecera(int anchoID, int anchoNombreAnalisis, int anchoPrecio, int anchoTiempo);
        void mostrarVarios(TipoAnalisis* tipoAnalisis, const int cantidad);
        void mostrarUno(TipoAnalisis tipoAnalisis);
        bool mostrarTodos();
        void mostrar(TipoAnalisis tipoAnalisis);
        void listadoXnombre();
        void listadoXvalor();
        bool eliminar(TipoAnalisis tipoAnalisis);
        bool actualizar(TipoAnalisis tipoAnalisis);
        ArchivoTipoAnalisis getRepositorio();
};
