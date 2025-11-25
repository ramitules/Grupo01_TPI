#pragma once
#include "Enfermero.h"
#include "Turno.h"
#include "archivo/ArchivoEnfermero.h"
#include "archivo/ArchivoTurno.h"
#include <cstring>

class Protocolo{
    private:
        int _id;
        int _idTurno;
        int _dniEnfermero;
        int _sala;
        bool _estado;
        bool _analisis;
        char _observaciones[255];
        bool _eliminado;

    public:
        Protocolo();
        Protocolo(int id, int idTurno, int dniEnfermero, int sala, bool estado, bool analisis, const char observaciones[]);

        //GETTERS
        int getId();
        int getIdTurno();
        int getDniEnfermero();
        int getSala();
        const char* getObservaciones();
        bool getEstado();
        bool getAnalisis();
        Enfermero getEnfermero();
        Turno getTurno();
        bool getEliminado();

        //SETTERS
        void setId(int id);
        void setIdTurno(int idTurno);
        void setDniEnfermero(int dniEnfermero);
        void setSala(int sala);
        void setAnalisis(bool analisis);
        void setEstado(bool estado);
        void setObservaciones(const char observaciones[]);
        void setEliminado(bool eliminado);
};
