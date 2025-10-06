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


        //GETTERS
        int getId();
        int getIdTipoAnalisis();
        int getSala();
        int getDniPaciente();

        //SETTERS
        //void setId(int id);
        //void setIdTipoAnalisis(int idTipoAnalisis);
        // son autoincrementales?? 

        void setSala(int sala);
        void setDniPaciente(int dniPaciente);

        void mostrarAnalisis();
};
