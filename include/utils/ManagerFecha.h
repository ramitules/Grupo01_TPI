#pragma once
#include "utils/Fecha.h"


class ManagerFecha{
    public:
        ManagerFecha();

        Fecha cargar();
        std::string mostrar(Fecha fecha);
};
