#pragma once
#include <iostream>
#include "csv/CSV.h"
#include "Protocolo.h"


class CSVProtocolo: public ArchivoCSV{
    public:
        CSVProtocolo();

        void guardar(Protocolo protocolo);
        void guardarTodos();
        
        Protocolo leerRegistro(int nroRegistro);
        Protocolo* leerTodo();
};
