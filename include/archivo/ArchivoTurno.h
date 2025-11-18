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

        /// Similar a leerTodos() solo que lee desde archivo CSV.
        /// @param nombreArchivo leera desde este nombre de archivo.
        /// @return vector de turnos (memoria dinamica, liberar luego)
        Turno* desdeCSV(std::string nombreArchivo);

        int cantidadRegistros();
};
