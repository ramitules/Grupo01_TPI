#pragma once
#include <iostream>
#include "csv/CSV.h"
#include "Protocolo.h"


class CSVProtocolo: public ArchivoCSV{
    private:
        std::string _ruta;

    public:
        CSVProtocolo(const std::string& ruta);

        void guardar(Protocolo protocolo);
        void guardarTodos(Protocolo* protocolos, int cantidad);
        
        Protocolo leerRegistro(int nroRegistro);
        Protocolo* leerTodo();
};
