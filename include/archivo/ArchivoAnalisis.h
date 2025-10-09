#pragma once
#include <iostream>
#include "archivo/Archivo.h"
#include "Analisis.h"


class ArchivoAnalisis: public Archivo {
    public:
        ArchivoAnalisis(std::string nombreArchivo, std::string rutaArchivo);
        
        int buscarID(int id);

        Analisis leer(int pos);
        Analisis* leerTodos();

        bool guardar(Analisis analisis);
        bool modificar(Analisis analisis, int pos);
        bool eliminar(int pos);

        int cantidadRegistros();
};
