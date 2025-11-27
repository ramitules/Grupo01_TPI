#pragma once
#include "archivo/ArchivoAnalisisProtocolo.h"

class ManagerAnalisisProtocolo{
    private:
        ArchivoAnalisisProtocolo _repo;

    public:
        ManagerAnalisisProtocolo();

        bool comprobar(int idProtocolo = -1, int idTipoAnalisis = -1);
        bool cargar(int idProtocolo);
        void mostrarTodos(int idProtocolo);

        ArchivoAnalisisProtocolo getRepositorio();
};
