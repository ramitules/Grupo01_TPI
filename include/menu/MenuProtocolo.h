#pragma once
#include "Menu.h"


class MenuProtocolo: public Menu {
    public:
        MenuProtocolo();

        void ejecutarOpcion() override;
};
