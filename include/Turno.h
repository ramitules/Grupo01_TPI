#pragma once
#include "utils/Fecha.h"
#include "utils/Hora.h"


class Turno{
    private:
        int _id;
        int _dniPaciente;
        int _idAnalisis;
        Fecha _fechaAtencion;
        Hora _horaAtencion;
        float _importe;

    public:
        Turno();
        Turno(int dniPaciente, int idAnalisis, Fecha fechaAtencion, Hora horaAtencion, float importe);
        Turno(int id, int dniPaciente, int idAnalisis, Fecha fechaAtencion, Hora horaAtencion, float importe);

    // SETTERS
        void set_dniPaciente(int dniPaciente);
        void set_idAnalisis(int idAnalisis);
        void set_fechaAtencion(Fecha fechaAtencion);
        void set_horaAtencion(Hora horaAtencion);
        void set_importe(float importe);
    // GETTERS
        int get_id();
        int get_dniPaciente();
        int get_idAnalisis();
        Fecha get_fechaAtencion();
        Hora get_horaAtencion();
        float get_importe();
    };

    //mostrar turno
        void mostrarTurno();