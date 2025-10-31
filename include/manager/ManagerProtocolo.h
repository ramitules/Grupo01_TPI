#pragma once
#include "archivo/ArchivoProtocolo.h"
#include "Protocolo.h"


class ManagerProtocolo{
    private:
        ArchivoProtocolo _repo;

    public:
        ManagerProtocolo();

        bool cargar(int idTurno);
        void mostrar(Protocolo protocolo);
        void mostrarTodos();
        bool eliminar(Protocolo protocolo);
        bool actualizar(Protocolo protocolo);
};
