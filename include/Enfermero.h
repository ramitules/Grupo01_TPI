#pragma once
#include "utils/Hora.h"
#include "Persona.h"


class Enfermero: public Persona{
    private:
        bool _habilitado;
        // A partir de que hora esta disponible este enferemero
        Hora _horarioAtencion;
        // Cantidad de horas que puede trabajar
        int _horasDisponible;
        int _acumuladoHoras;
        float _sueldoHora;

    public:
        Enfermero();

        //SETTERS
        void setHabilitado(bool habilitado);
        void setHorarioAtencion(Hora horarioAtencion);
        void setHorasDisponibles(int horasDisponible);
        void setAcumuladoHoras(int acumuladoHoras);
        void setSueldoHora(float sueldoHora);

        //GETTERS
        bool getHabilitado();
        Hora getHorarioAtencion();
        int getHorasDisponibles();
        int getAcumuladoHoras();
        float getSueldoHora();
        
        void mostrarDatosEnfermero();
    };
