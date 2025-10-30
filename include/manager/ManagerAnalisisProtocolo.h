#pragma once
#include "archivo/ArchivoAnalisisProtocolo.h"


class ManagerAnalisisProtocolo{
    private:
        ArchivoAnalisisProtocolo _repo;

    public:
        ManagerAnalisisProtocolo();

        bool cargar(int idProtocolo);
        void mostrar(AnalisisProtocolo analisisProtocolo);
        void mostrarTodos();
        bool eliminar(AnalisisProtocolo analisisProtocolo);
        bool actualizar(AnalisisProtocolo analisisProtocolo);

        ArchivoAnalisisProtocolo getRepositorio();
};
