#include "menu/Menu.h"
#include <iostream>


/// Constructor por defecto con todos los parametros necesarios
/// @param cantidadOpciones se utilizara para crear el vector de opciones.
/// Notese que la opcion "0. Salir" NO se debe incluir en la cantidad de opciones.
/// @param nombreMenu nombre que tendra el titulo de este menu
Menu::Menu(int cantidadOpciones, std::string nombreMenu){
    setCantidadOpciones(cantidadOpciones);
    setOpcionSeleccionada(99);
    setNombreMenu(nombreMenu);
    setSalir(true);
    setVectorOpciones();
}

/// ciclo que muestra por pantalla las opciones y le permite al usuario
/// seleccionar la deseada. Antes de salir, deja "opcionSeleccionada" en 99.
void Menu::buclePrincipal(){
    do{
        system("cls");
        mostrarOpciones();
        seleccionarOpcion();
        system("cls");
        ejecutarOpcion();
        system("cls");
    } while (_opcionSeleccionada != 0);

    setOpcionSeleccionada(99);
}

void Menu::setSalir(bool salir){ _salir = salir; }

void Menu::setCantidadOpciones(int cantidad = 1){
    if (cantidad > 10) {
        std::cout << "No se puede asignar mas de 10 opciones a un menu.\n";
        cantidad = 1;
    }

    _cantidadOpciones = cantidad;
}

void Menu::setNombreMenu(std::string nombre){
    _nombreMenu = nombre;
}

void Menu::setOpcionSeleccionada(int opcion){
    _opcionSeleccionada = opcion;
}

std::string Menu::getNombreMenu(){ return _nombreMenu; }


/// bucle para seleccionar una opcion. No permite salida hasta que
/// se encuentre dentro de los parametros
void Menu::seleccionarOpcion(){
    int opcion = 99;

    while (opcion < 0 || opcion > _cantidadOpciones){
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;
    }

    setOpcionSeleccionada(opcion);
}

/// Cada submenu tendra su propia logica
void Menu::ejecutarOpcion(){};


/// Recorre las opciones y las muestra por pantalla, una debajo de la otra
/// estilo "x. opcion"
void Menu::mostrarOpciones(){
    std::cout << getNombreMenu() << "\n";
    std::cout << "==============================\n";

    for (int i = 1; i < _cantidadOpciones + 1; i++) {
        std::cout << i << ". " << _opciones[i - 1] << "\n";
    }

    std::cout << "------------------------------\n";

    if (_salir) {
        std::cout << "0. Salir\n";
    } else {
        std::cout << "0. Volver\n";
    }
}

/// Inicializador de vector de opciones
/// @param opciones vector de opciones. Solo se leera y asignara la cantidad
/// propuesta en "cantidadOpciones".
void Menu::setVectorOpciones(std::string* opciones){
    // Limpiar
    setVectorOpciones();

    // Asignar
    for (int i = 0; i < _cantidadOpciones; i ++) {
        _opciones[i] = opciones[i];
    }
}

/// Inicializador de vector de opciones vacio
void Menu::setVectorOpciones(){
    for (int i = 0; i < 10; i++) {
        _opciones[i].clear();
    }
}
