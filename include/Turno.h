#pragma once
#include "utils/Fecha.h"
#include "utils/Hora.h"
#include "Paciente.h"


class Turno{
    private:
        int _id;
        int _dniPaciente;
        Fecha _fechaAtencion;
        Hora _horaAtencion;
        float _importe;
        bool _eliminado;

    public:
        Turno();
        Turno(int id, int dniPaciente, Fecha fechaAtencion, Hora horaAtencion, float importe);

        // SETTERS
        void setID(int id);
        void setDniPaciente(int dniPaciente);
        void setFechaAtencion(Fecha fechaAtencion);
        void setHoraAtencion(Hora horaAtencion);
        void setImporte(float importe);
        void setEliminado(bool eliminado);

        // GETTERS
        int getID();
        int getDniPaciente();
        float getImporte();
        Fecha getFechaAtencion();
        Hora getHoraAtencion();
        Paciente getPaciente();
        bool getEliminado();
    };
