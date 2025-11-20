#pragma once
#include "Persona.h"


class ManagerPersona{
    public:
        ManagerPersona();

        Persona cargar(int dni = 0);
        // En este caso, el metodo "actualizar" modifica el propio objeto.
        // Se aplicara polimorfismo siguiendo el principio de sustitucion de Liskov.
        void actualizar(Persona& persona);
        bool eliminar(Persona& persona);
        void mostrar(Persona persona);
};
