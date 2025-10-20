#pragma once
#include <iostream>
#include "archivo/Archivo.h"
#include "TipoAnalisis.h"


class ArchivoTipoAnalisis: public Archivo {
    public:
        ArchivoTipoAnalisis();
        
        int getPos(int id);

        TipoAnalisis leer(int pos);
        TipoAnalisis* leerTodos();

        bool guardar(TipoAnalisis tipoAnalisis);
        bool modificar(TipoAnalisis tipoAnalisis, int pos);
        bool eliminar(int pos);

        int cantidadRegistros();
};
