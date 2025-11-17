#pragma once
#include "archivo/ArchivoProtocolo.h"
#include "Protocolo.h"


class ManagerProtocolo{
    private:
        ArchivoProtocolo _repo;

    public:
        ManagerProtocolo();

        bool iniciar(int idTurno);
        bool cargarAnalisis(Protocolo protocolo);
        bool asignar(Protocolo protocolo);
        void mostrar(Protocolo protocolo);
        bool mostrarTodos();
        bool comprobarProtocolo(int idProtocolo);
        Protocolo seleccionarProtocolo(int idProtocolo);
        bool eliminar(Protocolo protocolo);
        bool actualizar(Protocolo protocolo);
};
