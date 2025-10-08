#pragma once
#include "../Menu.h"


class ConsultasAnalisis: public Menu {
    public:
        ConsultasAnalisis();

        void ejecutarOpcion() override;
        void mostrarOpciones() override;
};
