#pragma once
#include "archivo/ArchivoAnalisisProtocolo.h"

class ManagerAnalisisProtocolo{
    private:
        ArchivoAnalisisProtocolo _repo;

    public:
        ManagerAnalisisProtocolo();

        bool cargar(int idProtocolo);
        bool actualizar(AnalisisProtocolo analisisProtocolo);
        void mostrar(AnalisisProtocolo analisisProtocolo);
        void mostrarTodos();
        bool eliminar(AnalisisProtocolo analisisProtocolo);


        ArchivoAnalisisProtocolo getRepositorio();
};
