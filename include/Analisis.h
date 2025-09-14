#pragma once


class Analisis {
    private:
        int _id;
        int _idTipoAnalisis;
        int _sala;
        int _dniPaciente;

    public:
        Analisis();
        Analisis(int idTipoAnalisis, int sala, int dniPaciente);
        Analisis(int id, int idTipoAnalisis, int sala, int dniPaciente);
};
