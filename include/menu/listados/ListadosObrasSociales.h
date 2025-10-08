#pragma once
#include "MenuListados.h"


class ListadosObrasSociales: public Menu {
    public:
        ListadosObrasSociales();

        void ejecutarOpcion() override;
        void mostrarOpciones() override;
};
