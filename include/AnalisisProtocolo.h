#pragma once
#include <cstring>

#include "TipoAnalisis.h"

class AnalisisProtocolo{
    private:
        int _idProtocolo;
        int _idTipoAnalisis;
        char _resultados[255];
        bool _eliminado; //chequear en diagrama

    public:
        AnalisisProtocolo();
        AnalisisProtocolo(int idProtocolo, int idTipoAnalisis, const char resultados[]);

        //GETTERS
        int getIdProtocolo();
        int getIdTipoAnalisis();
        const char* getResultado();
        Protocolo getProtocolo();
        TipoAnalisis getTipoAnalisis();
        bool getEliminado(); //chequear en diagrama

        //SETTERS
        void setIdProtocolo(int idProtocolo);
        void setIdTipoAnalisis(int idTipoAnalisis);
        void setResultados(const char resultados[]);
        void setEliminado(bool eliminado); //chequear en diagrama
};
