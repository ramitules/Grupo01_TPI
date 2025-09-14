#pragma once

/// @brief Clase que se encarga de manejar el ID autoincremental utilizado en cada clase.
class Secuencia{
    private:
        // Identificador único de la secuencia
        int _id;
        // Nombre del objeto al que pertenece la secuencia (ejemplo: "Turno")
        char _objeto[50];
        // Último ID utilizado en la secuencia
        int _id_actual;

    public:
        Secuencia();
        Secuencia(const char objeto[], int id_actual);
        Secuencia(int id, const char objeto[], int id_actual);
};
