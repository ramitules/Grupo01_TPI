#pragma once
#include "utils/Hora.h"
#include <iostream>


class ManagerHora{
    public:
        ManagerHora();

        Hora cargar();
        std::string mostrar(Hora hora);
};
