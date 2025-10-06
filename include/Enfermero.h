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
        void set_habilitado(bool habilitado);
        void set_horarioAtencion(Hora horarioAtencion);
        void set_horasDisponible(int horasDisponible);
        void set_acumuladoHoras(int acumuladoHoras);
        void set_sueldoHora(float sueldoHora);


        //GETTERS
        bool get_habilitado();
        Hora get_horarioAtencion();
        int get_horasDisponible();
        int get_acumuladoHoras();
        float get_sueldoHora();
        
        
        
        void mostrarDatosEnfermero();




    };
