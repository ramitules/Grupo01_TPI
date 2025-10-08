#pragma once
#include "../Menu.h"


class MenuListados: public Menu {
    public:
        MenuListados();

        void ejecutarOpcion() override;
};
