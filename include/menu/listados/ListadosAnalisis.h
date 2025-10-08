#pragma once
#include "MenuListados.h"


class ListadosAnalisis: public Menu {
    public:
        ListadosAnalisis();

        void ejecutarOpcion() override;
        void mostrarOpciones() override;
};
