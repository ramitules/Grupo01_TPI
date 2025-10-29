#pragma once
#include "archivo/ArchivoProtocolo.h"
#include "Protocolo.h"


class ManagerProtocolo{
    private:
        ArchivoProtocolo _repo;

    public:
        ManagerProtocolo();

        bool cargar();
        void mostrar(Protocolo protocolo);
        void mostrarTodos();
        bool eliminar(Protocolo protocolo);
        bool actualizar(Protocolo protocolo);
};
