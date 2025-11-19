#pragma once
#include "archivo/Archivo.h"
#include "Protocolo.h"


class ArchivoProtocolo: public Archivo {
    public:
        ArchivoProtocolo();
        
        int getPos(int id);

        Protocolo leer(int pos);
        Protocolo* leerTodos();

        bool guardar(Protocolo protocolo);
        bool guardarVarios(Protocolo* protocolos, int cantidad);
        bool modificar(Protocolo protocolo, int pos);
        bool eliminar(int pos);

        int cantidadRegistros();
};
