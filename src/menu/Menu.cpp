#include "menu/Menu.h"
#include <iostream>


/// @brief Constructor por defecto con todos los parametros necesarios
/// @param cantidadOpciones se utilizara para crear el vector de opciones.
/// Notese que la opcion "0. Salir" NO se debe incluir en la cantidad de opciones.
/// @param nombreMenu nombre que tendra el titulo de este menu
Menu::Menu(int cantidadOpciones, std::string nombreMenu){
    setCantidadOpciones(cantidadOpciones);
    setOpcionSeleccionada(99);
    setNombreMenu(nombreMenu);
    setSalir(true);
    _opciones = nullptr;
}

Menu::~Menu(){
    if (_opciones != nullptr) {
        delete[] _opciones;
    }
}

/// @brief ciclo que muestra por pantalla las opciones y le permite al usuario
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
    _cantidadOpciones = cantidad;
}

void Menu::setNombreMenu(std::string nombre){
    _nombreMenu = nombre;
}

void Menu::setOpcionSeleccionada(int opcion){
    _opcionSeleccionada = opcion;
}

std::string Menu::getNombreMenu(){ return _nombreMenu; }


/// @brief bucle para seleccionar una opcion. No permite salida hasta que
/// se encuentre dentro de los parametros
void Menu::seleccionarOpcion(){
    int opcion = 99;

    while (opcion < 0 || opcion > _cantidadOpciones){
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;
    }

    setOpcionSeleccionada(opcion);
}

/// @brief Cada submenu tendra su propia logica
void Menu::ejecutarOpcion(){};


/// @brief Recorre las opciones y las muestra por pantalla, una debajo de la otra
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

/// @brief Se utiliza memoria dinamica para crear vector de strings.
/// En caso de que no se pueda asignar memoria, el puntero _opciones
/// permanecera nulo.
/// @param opciones vector de opciones. Solo se leera y asignara la cantidad
/// propuesta en "cantidadOpciones".
void Menu::setVectorOpciones(std::string* opciones){
    // Chequear que no haya nada en el atributo "_opciones"
    if (_opciones != nullptr) {
        delete[] _opciones;
    }

    // Solicitar memoria para vector de strings
    std::string *vOpciones = new std::string[_cantidadOpciones];

    if (vOpciones != nullptr) {
        // Se le puede asignar valores
        for (int i=0; i < _cantidadOpciones; i++) {
            if (opciones == nullptr) {
                vOpciones[i] = "";
            } else {
                vOpciones[i] = opciones[i];
            }
        }
    } else {
        // Dejar puntero nulo
        std::cout << "Error al asignarle memoria a las opciones del menu";
    }
    
    _opciones = vOpciones;
}
