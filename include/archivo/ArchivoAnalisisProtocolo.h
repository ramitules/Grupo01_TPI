#pragma once
#include "archivo/Archivo.h"
#include "AnalisisProtocolo.h"


class ArchivoAnalisisProtocolo: public Archivo {
    public:
        ArchivoAnalisisProtocolo();
        
        int getPos(int id);

        AnalisisProtocolo leer(int pos);
        AnalisisProtocolo* leerTodos();

        bool guardar(AnalisisProtocolo analisisProtocolo);
        bool guardarVarios(AnalisisProtocolo* analisisProtocolos, int cantidad);
        bool modificar(AnalisisProtocolo analisisProtocolo, int pos);
        bool eliminar(int pos);

        int cantidadRegistros();
};
