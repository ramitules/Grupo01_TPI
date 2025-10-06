#pragma once
#include "Menu.h"


class MenuEnfermero: public Menu {
    public:
        MenuEnfermero();

        void ejecutarOpcion() override;
};
