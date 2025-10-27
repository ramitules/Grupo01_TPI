#pragma once
#include <cstring>

class AnalisisProtocolo{
    private:
        int _idProtocolo;
        int _idTipoAnalisis;
        char _resultados[255];
        bool _eliminado;

    public:
        AnalisisProtocolo();
        AnalisisProtocolo(int idProtocolo, int idTipoAnalisis, const char resultados[]);

        //GETTERS
        int getIdProtocolo();
        int getIdTipoAnalisis();
        const char* resultado();
        bool getEliminado();

        //SETTERS
        void setIdProtocolo(int idProtocolo);
        void setIdTipoAnalisis(int idTipoAnalisis);
        void setResultados(const char resultados[]);
        void setEliminado(bool eliminado);
};
