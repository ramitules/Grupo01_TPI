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
        void set_nombreAnalisis(const char nombreAnalisis[]);
        void set_precio(float precio);
    // GETTERS
        int get_id();
        const char* get_nombreAnalisis();
        float get_precio();
};