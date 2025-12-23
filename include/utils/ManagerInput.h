#pragma once
#include "utils/Fecha.h"
#include <iostream>

class ManagerInput{
    public:
        ManagerInput();
        bool ingresarNombre(std::string &nombre, std::string mensaje = "Ingresar Nombre: ");
        int ingresarDni(std::string mensaje = "Ingresar Dni: ");

        //Tipo de analisis
        bool ingresarTiempoResultado(int &tiempoResultado, std::string mensaje = "Ingresar Tiempo Resultado: ");
        bool ingresarPrecio(float &precio, std::string mensaje = "Ingresar Precio: ");
};