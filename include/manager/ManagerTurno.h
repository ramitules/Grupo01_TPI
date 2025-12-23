#pragma once
#include "archivo/ArchivoTurno.h"
#include "AnalisisProtocolo.h"


class ManagerTurno{
    private:
        ArchivoTurno _repo;

    public:
        ManagerTurno();

        bool comprobar(int idTurno);
        Turno seleccionar(int idTurno);

        void cargar();
        void mostrarUno(Turno turno);
        void mostrarVarios(Turno* turnos, const int cantidad);
        /// @return linea separadora para cabeceras y limites superior/inferior
        std::string mostrarCabecera(const int anchoPaciente, const int anchoFecha, const int anchoImporte, const int anchoObraSocial, const int estado);
        void mostrarTodos();
        bool eliminar(Turno turno);
        bool actualizar(Turno turno);
        bool actualizarImporte(AnalisisProtocolo analisisProtocolo);

        Protocolo buscarProtocolo (int idTurno);

        // Ordena todos los turnos existentes y los muestra por pantalla
        void ordenadosFecha();
        // Ordena los pacientes alfabeticamente y agrupa sus turnos, mostrandolos por pantalla
        void agrupadosPaciente();
        // Busca turnos pidiendo un rango de fechas
        void busquedaFecha();
        // Busca turnos pidiendo los datos de un paciente
        void busquedaPaciente();

        void actualizarImportes();
        void actualizarImportesSeleccionados();

        ArchivoTurno getRepositorio();
};
