#pragma once


class TipoAnalisis{
    private:
        int _id;
        char _nombreAnalisis[255];
        float _precio;

    public:
        TipoAnalisis();
        TipoAnalisis(int id, const char nombreAnalisis[], float precio);

        // SETTERS
        void setNombreAnalisis(const char nombreAnalisis[]);
        void setPrecio(float precio);
        void setID(int id);

        // GETTERS
        int getID();
        const char* getNombreAnalisis();
        float getPrecio();
};