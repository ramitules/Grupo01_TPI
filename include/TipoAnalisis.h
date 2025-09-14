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
};
