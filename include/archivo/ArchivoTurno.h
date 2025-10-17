#pragma once
#include <iostream>
#include "archivo/Archivo.h"
#include "Turno.h"


class ArchivoTurno: public Archivo {
    public:
        ArchivoTurno();
        
        int getPos(int id);

        Turno leer(int pos);
        Turno* leerTodos();

        bool guardar(Turno turno);
        bool modificar(Turno turno, int pos);
        bool eliminar(int pos);

        int cantidadRegistros();
};
