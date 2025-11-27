#pragma once
#include "archivo/ArchivoAnalisisProtocolo.h"

class ManagerAnalisisProtocolo{
    private:
        ArchivoAnalisisProtocolo _repo;

    public:
        ManagerAnalisisProtocolo();

        bool comprobar(int idProtocolo = -1);
        bool cargar(int idProtocolo);
        std::string mostrarCabecera(int anchoID, int anchoTipoAnalisis, int anchoPrecioSoli, int anchoResultados);
        void mostrarUno(AnalisisProtocolo analisisProtocolo);
        void mostrarVarios(AnalisisProtocolo* analisisProtocolos, const int cantidad);
        void mostrarTodos(int idProtocolo);

        ArchivoAnalisisProtocolo getRepositorio();
};
