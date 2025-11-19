#pragma once
#include <iostream>
#include "csv/CSV.h"
#include "AnalisisProtocolo.h"


class CSVAnalisisProtocolo: public ArchivoCSV{
    private:
        std::string _ruta;

    public:
        CSVAnalisisProtocolo(const std::string& ruta);

        void guardar(AnalisisProtocolo analisisProtocolo);
        void guardarTodos(AnalisisProtocolo* analisisProtocolos, int cantidad);
        
        AnalisisProtocolo leerRegistro(int nroRegistro);
        AnalisisProtocolo* leerTodo();
};
