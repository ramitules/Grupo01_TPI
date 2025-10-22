#pragma once
#include "utils/Fecha.h"
#include "utils/Hora.h"
#include "Paciente.h"
#include "Analisis.h"


class Turno{
    private:
        int _id;
        int _dniPaciente;
        int _idAnalisis;
        Fecha _fechaAtencion;
        Hora _horaAtencion;
        float _importe;
        bool _eliminado;

    public:
        Turno();
        Turno(int id, int dniPaciente, int idAnalisis, Fecha fechaAtencion, Hora horaAtencion, float importe);

        // SETTERS
        void setID(int id);
        void setDniPaciente(int dniPaciente);
        void setIdAnalisis(int idAnalisis);
        void setFechaAtencion(Fecha fechaAtencion);
        void setHoraAtencion(Hora horaAtencion);
        void setImporte(float importe);
        void setEliminado(bool eliminado);

        // GETTERS
        int getID();
        int getDniPaciente();
        int getIdAnalisis();
        float getImporte();
        Fecha getFechaAtencion();
        Hora getHoraAtencion();
        Paciente getPaciente();
        Analisis getAnalisis();
        bool getEliminado();
    };
