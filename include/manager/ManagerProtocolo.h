#pragma once
#include "archivo/ArchivoProtocolo.h"
#include "Protocolo.h"


class ManagerProtocolo{
    private:
        ArchivoProtocolo _repo;

    public:
        ManagerProtocolo();

        bool comprobar(int idProtocolo = -1);
        Protocolo seleccionar(int idProtocolo);
        bool iniciar(Protocolo &protocolo);
        bool chequearTurno(Protocolo protocolo);
        bool cargarAnalisis(Protocolo protocolo);
        bool asignar(Protocolo protocolo);
        void mostrar(Protocolo protocolo);
        bool mostrarTodos();
        bool finalizar(Protocolo protocolo);
        bool eliminar(Protocolo protocolo);
        ArchivoProtocolo getRepositorio();
};
