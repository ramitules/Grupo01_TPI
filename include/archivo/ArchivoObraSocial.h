#pragma once
#include "archivo/Archivo.h"
#include "ObraSocial.h"


class ArchivoObraSocial: public Archivo {
    public:
        ArchivoObraSocial();
        
        int getPos(int id);

        ObraSocial leer(int pos);
        ObraSocial* leerTodos();

        bool guardar(ObraSocial obraSocial);
        bool guardarVarios(ObraSocial* obrasSociales, int cantidad);
        bool modificar(ObraSocial obraSocial, int pos);
        bool eliminar(int pos);

        int cantidadRegistros();
};
