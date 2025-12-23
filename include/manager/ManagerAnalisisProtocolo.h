#pragma once
#include "archivo/ArchivoAnalisisProtocolo.h"

class ManagerAnalisisProtocolo{
    private:
        ArchivoAnalisisProtocolo _repo;

    public:
        ManagerAnalisisProtocolo();

        bool comprobar(int idProtocolo, int idTipoAnalisis);
        bool cargar(int idProtocolo);
        void mostrarTodos(int idProtocolo);

        AnalisisProtocolo* seleccionarAnalisis(int idProtocolo);
        ArchivoAnalisisProtocolo getRepositorio();
};
