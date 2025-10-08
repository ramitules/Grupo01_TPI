#pragma once
#include "MenuListados.h"


class ListadosTurnos: public Menu {
    public:
        ListadosTurnos();

        void ejecutarOpcion() override;
        void mostrarOpciones() override;
};
