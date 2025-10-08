#pragma once
#include "MenuListados.h"


class ListadosPacientes: public Menu {
    public:
        ListadosPacientes();

        void ejecutarOpcion() override;
        void mostrarOpciones() override;
};
