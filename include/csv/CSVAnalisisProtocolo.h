#pragma once
#include <iostream>
#include "csv/CSV.h"
#include "AnalisisProtocolo.h"


class CSVAnalisisProtocolo: public ArchivoCSV{
    public:
        CSVAnalisisProtocolo();

        void guardar(AnalisisProtocolo analisisProtocolo);
        void guardarTodos();
        
        AnalisisProtocolo leerRegistro(int nroRegistro);
        AnalisisProtocolo* leerTodo();
};
