#pragma once


class TipoAnalisis{
    private:
        int _id;
        char _nombreAnalisis[255];
        float _precio;
        int _tiempoResultado;
        bool _eliminado;

    public:
        TipoAnalisis();
        TipoAnalisis(int id, const char nombreAnalisis[], int tiempoResultado, float precio);

        // SETTERS
        void setID(int id);
        void setNombreAnalisis(const char nombreAnalisis[]);
        void setTiempoResultado(int tiempoResultado);
        void setPrecio(float precio);

        void setEliminado(bool eliminado);

        // GETTERS
        int getID();
        const char* getNombreAnalisis();
        float getPrecio();
        int getTiempoResultado();
        bool getEliminado();
};