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
        void setDNI(int dni);
        void setNombre(const char nombre[]);
        void setApellido(const char apellido[]);
        void setTelefono(int telefono);
        void setEmail(const char email[]);
        void setFechaNacimiento(Fecha fechaNacimiento);
        void setEliminado(bool eliminado);

        //GETTERS
        int getDNI();
        const char* getNombre();   
        const char* getApellido();
        int getTelefono();
        const char* getEmail();
        Fecha getFechaNacimiento();
        bool getEliminado();
    };
