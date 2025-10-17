#pragma once
#include "Persona.h"


class ManagerPersona{
    public:
        ManagerPersona();

        Persona cargar();
        void mostrar(Persona persona);
};
