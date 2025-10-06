#pragma once
#include "utils/Fecha.h"


class Persona{
    protected:
        int _dni;
        char _nombre[50];
        char _apellido[50];
        int _telefono;
        char _email[110];
        Fecha _fechaNacimiento;
        bool _eliminado;

    public:
        Persona();
        Persona(int dni, const char nombre[], const char apellido[], int telefono, const char email[], Fecha fechaNacimiento, bool eliminado);

        //SETTERS
        void set_dni(int dni);
        void set_nombre(const char nombre[]);
        void set_apellido(const char apellido[]);
        void set_telefono(int telefono);
        void set_email(const char email[]);
        void set_fechaNacimiento(Fecha fechaNacimiento);
        void set_eliminado(bool eliminado);

        //GETTERS
        int get_dni();
        const char* get_nombre();   
        const char* get_apellido();
        int get_telefono();
        const char* get_email();
        Fecha get_fechaNacimiento();
        bool get_eliminado();


        void mostrarDatosPersona();


    };



