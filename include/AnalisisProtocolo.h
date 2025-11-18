#pragma once
#include "Protocolo.h"
#include <cstring>

#include "TipoAnalisis.h"

class AnalisisProtocolo{
    private:
        int _idProtocolo;
        int _idTipoAnalisis;
        float _precioSolicitud;
        char _resultados[255];
        bool _eliminado; //chequear en diagrama

    public:
        AnalisisProtocolo();
        AnalisisProtocolo(int idProtocolo, int idTipoAnalisis,float precioSolicitud, const char resultados[]);

        //GETTERS
        int getIdProtocolo();
        int getIdTipoAnalisis();
        float getPrecioSolicitud();
        const char* getResultado();
        Protocolo getProtocolo();
        TipoAnalisis getTipoAnalisis();
        bool getEliminado(); //chequear en diagrama

        //SETTERS
        void setIdProtocolo(int idProtocolo);
        void setIdTipoAnalisis(int idTipoAnalisis);
        void setPrecioSolicitud(float precioSolicitud);
        void setResultados(const char resultados[]);
        void setEliminado(bool eliminado); //chequear en diagrama
};
