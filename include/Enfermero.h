#pragma once
#include "utils/Hora.h"
#include "Persona.h"


class Enfermero: public Persona{
    private:
        bool _habilitado;
        Hora _horarioAtencion;
        int _horasDisponible;
        int _acumuladoHoras;
        float _sueldoHora;

    public:
        Enfermero();
        // La clase Enfermero tendra un metodo "Cargar" en lugar de un constructor
        // para no tener tantos argumentos en la funcion
        void Cargar();

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
