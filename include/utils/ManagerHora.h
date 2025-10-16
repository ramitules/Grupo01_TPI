#pragma once
#include "utils/Hora.h"


class ManagerHora{
    public:
        ManagerHora();

        Hora cargar();
        std::string mostrar(Hora hora);
};
