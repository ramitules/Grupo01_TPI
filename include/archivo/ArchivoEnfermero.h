#pragma once
#include <iostream>
#include "archivo/Archivo.h"
#include "Enfermero.h"


class ArchivoEnfermero: public Archivo {
    public:
        ArchivoEnfermero();
        
        int getPos(int id);

        Enfermero leer(int pos);
        Enfermero* leerTodos();

        bool guardar(Enfermero enfermero);
        bool modificar(Enfermero enfermero, int pos);
        bool eliminar(int pos);

        int cantidadRegistros();
};
