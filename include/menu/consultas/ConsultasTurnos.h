#pragma once
#include "../Menu.h"


class ConsultasTurnos: public Menu {
    public:
        ConsultasTurnos();

        void ejecutarOpcion() override;
        void mostrarOpciones() override;
};
