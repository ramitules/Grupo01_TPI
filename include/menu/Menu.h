#pragma once
#include <string>


class Menu{
    private:
        int opcionSeleccionada;
        int cantidadOpciones;
        std::string *opciones;

    public:
        Menu();
        void buclePrincipal();
};
