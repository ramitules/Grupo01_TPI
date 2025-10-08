#pragma once


class TipoAnalisis{
    private:
        int _id;
        char _nombreAnalisis[255];
        float _precio;

    public:
        TipoAnalisis();
        TipoAnalisis(const char nombreAnalisis[], float precio);
        TipoAnalisis(int id, const char nombreAnalisis[], float precio);

        // SETTERS
        void setNombreAnalisis(const char nombreAnalisis[]);
        void setPrecio(float precio);

        // GETTERS
        int getID();
        const char* getNombreAnalisis();
        float getPrecio();
};