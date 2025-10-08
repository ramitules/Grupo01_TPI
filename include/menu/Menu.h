#pragma once
#include <string>


class Menu{
    protected:
        int _opcionSeleccionada;
        int _cantidadOpciones;
        // Indica si la opcion "0" es para salir. False = "Volver"
        bool _salir;
        std::string _nombreMenu;
        std::string* _opciones;

    public:
        Menu(int cantidadOpciones, std::string nombreMenu);
        virtual ~Menu();
        
        void setNombreMenu(std::string nombre);
        void setCantidadOpciones(int cantidad);
        void setVectorOpciones(std::string* opciones);
        void setOpcionSeleccionada(int opcion);
        void setSalir(bool salir);

        std::string getNombreMenu();

        void seleccionarOpcion();
        // Polimorfismo para tener diferentes vistas del menu
        virtual void mostrarOpciones();
        // Polimorfismo para tener diferentes comportamientos en
        // el metodo que ejecuta una opcion segun que objeto lo use
        virtual void ejecutarOpcion();
        void buclePrincipal();
};
