#pragma once
#include <string>


class Menu{
    protected:
        int _opcionSeleccionada;
        int _cantidadOpciones;
        std::string _nombreMenu;
        std::string *_opciones;

    public:
        Menu(int cantidadOpciones, std::string opciones[], std::string nombreMenu);
        
        void setNombreMenu(std::string nombre = "Menu");
        void setCantidadOpciones(int cantidad = 1);
        void setVectorOpciones(std::string opciones[]);
        void setOpcionSeleccionada(int opcion = 99);

        std::string getNombreMenu();

        void seleccionarOpcion();
        void mostrarOpciones();
        void ejecutarOpcion();
        void buclePrincipal();
};
