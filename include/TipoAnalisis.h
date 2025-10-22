#pragma once


class TipoAnalisis{
    private:
        int _id;
        char _nombreAnalisis[255];
        float _precio;
        bool _eliminado;

    public:
        TipoAnalisis();
        TipoAnalisis(int id, const char nombreAnalisis[], float precio);

        // SETTERS
        void setNombreAnalisis(const char nombreAnalisis[]);
        void setPrecio(float precio);
        void setID(int id);
        void setEliminado(bool eliminado);

        // GETTERS
        int getID();
        const char* getNombreAnalisis();
        float getPrecio();
        bool getEliminado();
};