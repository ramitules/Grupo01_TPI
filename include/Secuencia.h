#pragma once

/// @brief Clase que se encarga de manejar el ID autoincremental utilizado en cada clase.
class Secuencia{
    private:
        // Identificador único de la secuencia
        int _id;
        // Nombre del objeto al que pertenece la secuencia (ejemplo: "Turno")
        char _objeto[50];
        // Último ID utilizado en la secuencia
        int _idActual;

    public:
        Secuencia();
        Secuencia(int id, const char objeto[], int idActual);

        int getId();
        const char* getObjeto();
        int getIdActual();

        void setId(int id);
        void setObjeto(const char objeto[]);
        void setIdActual(int idActual);
};
