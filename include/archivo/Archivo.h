#pragma once
#include <iostream>
#include <sys/stat.h>


class Archivo{
    protected:
        std::string _nombreArchivo;
        std::string _rutaArchivo;

    public:
        Archivo(std::string nombreArchivo, std::string rutaArchivo);

        std::string getNombreArchivo();
        std::string getRutaArchivo();
        std::string getRutaCompleta();

        void setNombreArchivo(std::string nombreArchivo);
        void setRutaArchivo(std::string rutaArchivo);

        // Guarda un objeto en un archivo CSV.
        /// @param objeto todos los atributos del objeto a guardar, separados por coma.
        /// Puede aceptar una cantidad indefinida de objetos, pero deben estar todos unidos por
        /// un salto de linea '\\n' y sus atributos separados por coma.
        /// @param nombreArchivo el nuevo archivo CSV tendra este nombre.
        /// @param cabeceras incluye titulos a cada columna.
        bool exportarCSV(std::string objeto, std::string nombreArchivo, std::string cabeceras);

        // Chequea si existe el directorio donde se guardara la base de datos.
        // No necesita un nombre de archivo.
        bool existeRuta();
};
