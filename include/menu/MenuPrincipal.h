#pragma once
#include "Menu.h"


class MenuPrincipal: public Menu {
    public:
        MenuPrincipal();
        
        void ejecutarOpcion() override;
};
