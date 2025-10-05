#pragma once
#include "Menu.h"


class MenuTurno: public Menu {
    public:
        MenuTurno();

        void ejecutarOpcion() override;
};
