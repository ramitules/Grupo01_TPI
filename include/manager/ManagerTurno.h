#pragma once
#include "archivo/ArchivoTurno.h"


class ManagerTurno{
    private:
        ArchivoTurno _repo;

    public:
        ManagerTurno();

        bool cargar();
        void mostrar(Turno turno);
        void mostrarTodos();
        bool eliminar(Turno turno);
        bool actualizar(Turno turno);

        // Ordena todos los turnos existentes y los muestra por pantalla
        void ordenadosFecha();
        // Ordena los pacientes alfabeticamente y agrupa sus turnos, mostrandolos por pantalla
        void agrupadosPaciente();
        // Busca turnos pidiendo un rango de fechas
        void busquedaFecha();
        // Busca turnos pidiendo los datos de un paciente
        void busquedaPaciente();
        
        ArchivoTurno getRepositorio();
};
