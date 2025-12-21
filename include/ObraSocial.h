#pragma once


class ObraSocial{
    private:
        int _id;
        char _nombre[50];
        char _nombreContacto[50];
        int _telefono;
        char _email[110];
        int _cobertura;
        bool _eliminado;
        
    public:
        ObraSocial();
        ObraSocial(int id, const char nombre[], const char nombreContacto[], int telefono, const char email[], int cobertura);

        //SETTERS
        void setID(int id);
        void setNombre(const char nombre[]);
        void setNombreContacto(const char nombreContacto[]);
        void setTelefono(int telefono);
        void setEmail(const char email[]);
        void setCobertura(int cobertura);
        void setEliminado(bool eliminado);

        //GETTERS
        int getID();
        const char* getNombre();
        const char* getNombreContacto();
        int getTelefono();
        const char* getEmail();
        int getCobertura();
        bool getEliminado();
};
