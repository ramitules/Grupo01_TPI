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

        // Guarda un turno en un archivo CSV. Genera cabeceras automaticamente.
        /// @param turno todos los atributos del turno a guardar, separados por coma.
        /// Puede aceptar una cantidad indefinida de turnos, pero deben estar todos unidos por
        /// un salto de linea '\\n' y sus atributos separados por coma.
        /// @param nombreArchivo el nuevo archivo CSV tendra este nombre
        bool exportarCSV(std::string turno, std::string nombreArchivo);

        /// Similar a leerTodos() solo que lee desde archivo CSV.
        /// @param nombreArchivo leera desde este nombre de archivo.
        /// @return vector de turnos (memoria dinamica, liberar luego)
        Turno* desdeCSV(std::string nombreArchivo);

        int cantidadRegistros();
};
