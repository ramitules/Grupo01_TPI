#pragma once
#include <iostream>
#include "archivo/Archivo.h"
#include "Secuencia.h"


class ArchivoSecuencia: public Archivo {
    public:
        ArchivoSecuencia();
        
        int getPos(int id);

        Secuencia leer(int pos);
        Secuencia* leerTodos();

        bool guardar(Secuencia secuencia);
        bool modificar(Secuencia secuencia, int pos);
        bool eliminar(int pos);

        int cantidadRegistros();
};
