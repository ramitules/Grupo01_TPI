#pragma once
#include "utils/Fecha.h"
#include <iostream>


class ManagerFecha{
    public:
        ManagerFecha();

        Fecha cargar();
        std::string mostrar(Fecha fecha);
};
