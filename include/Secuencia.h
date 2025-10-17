#pragma once

/// @brief Clase que se encarga de manejar el ID autoincremental utilizado en cada clase.
class Secuencia{
    private:
        // Identificador único de la secuencia. Comienza en 1
        int _id;
        // Nombre del objeto al que pertenece la secuencia (ejemplo: "Turno")
        char _objeto[50];
        // Último ID utilizado en la secuencia.
        int _idActual;

    public:
        // ID = 1, objeto = "ejemplo", idActual = 0
        Secuencia();
        // ID = 1, objeto = objeto, idActual = 0
        Secuencia(const char* objeto);
        Secuencia(int id, const char* objeto, int idActual);

        int getId();
        const char* getObjeto();
        int getIdActual();

        void setId(int id);
        void setObjeto(const char objeto[]);
        void setIdActual(int idActual);
};
