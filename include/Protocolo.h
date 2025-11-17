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
        char _observaciones[255];
        bool _estado;
        bool _eliminado;

    public:
        Protocolo();
        Protocolo(int id, int idTurno, int dniEnfermero, int sala, const char observaciones[]);

        //GETTERS
        int getId();
        int getIdTurno();
        int getDniEnfermero();
        int getSala();
        const char* getObservaciones();
        bool getEstado();
        Enfermero getEnfermero();
        Turno getTurno();
        bool getEliminado();

        //SETTERS
        void setId(int id);
        void setIdTurno(int idTurno);
        void setDniEnfermero(int dniEnfermero);
        void setSala(int sala);
        void setObservaciones(const char observaciones[]);
        void setEstado(bool estado);
        void setEliminado(bool eliminado);
};
