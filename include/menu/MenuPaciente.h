#pragma once
#include "Menu.h"


class MenuPaciente: public Menu {
    public:
        MenuPaciente();

        void ejecutarOpcion() override;
};
