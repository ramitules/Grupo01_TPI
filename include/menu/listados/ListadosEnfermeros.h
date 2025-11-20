#pragma once
#include "MenuListados.h"


class ListadosEnfermeros: public Menu {
    public:
        ListadosEnfermeros();

        void ejecutarOpcion() override;
        void mostrarOpciones() override;
};
