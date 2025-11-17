#pragma once
#include "utils/Hora.h"
#include <iostream>


class ManagerHora{
    public:
        ManagerHora();

        Hora desdeString(std::string& horaStr);
        Hora cargar();
        std::string mostrar(Hora hora);
};
