#pragma once
#include "../Menu.h"


class ConsultasPacientes: public Menu {
    public:
        ConsultasPacientes();

        void ejecutarOpcion() override;
        void mostrarOpciones() override;
};
