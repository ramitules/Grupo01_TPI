#pragma once
#include "TipoAnalisis.h"
#include "Paciente.h"


class Analisis {
    private:
        int _id;
        int _idTipoAnalisis;
        int _sala;
        int _dniPaciente;
        bool _eliminado;

    public:
        Analisis();
        Analisis(int id, int idTipoAnalisis, int sala, int dniPaciente);

        //GETTERS
        int getId();
        int getIdTipoAnalisis();
        int getSala();
        int getDniPaciente();
        TipoAnalisis getTipoAnalisis();
        Paciente getPaciente();
        bool getEliminado();

        //SETTERS
        void setId(int id);
        void setIdTipoAnalisis(int idTipoAnalisis);
        void setSala(int sala);
        void setDniPaciente(int dniPaciente);
        void setEliminado(bool eliminado);
};
