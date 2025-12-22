#pragma once
#include "archivo/ArchivoProtocolo.h"
#include "Protocolo.h"
#include "Turno.h"


class ManagerProtocolo{
    private:

        ArchivoProtocolo _repo;

    public:
        ManagerProtocolo();

        bool comprobar(int idProtocolo = -1);
        Protocolo seleccionar(int idProtocolo);
        Protocolo seleccionarxTurno(int idTurno);
        bool iniciar(Protocolo &protocolo);
        bool chequearTurno(Protocolo protocolo);
        bool cargarAnalisis(Protocolo protocolo);
        bool asignar(Protocolo protocolo);
        bool resultados(Protocolo protocolo);
        void mostrar(Protocolo protocolo);
        void mostrarVarios(Protocolo* protocolo, const int cantidad);
        bool mostrarTodos();
        bool finalizar(Protocolo protocolo);
        bool eliminar(Protocolo protocolo);

        ArchivoProtocolo getRepositorio();
};
