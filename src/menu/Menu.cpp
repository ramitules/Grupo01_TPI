#include "menu/Menu.h"
#include <iostream>


Menu::Menu(int cantidadOpciones, std::string opciones[], std::string nombreMenu){
    setCantidadOpciones(cantidadOpciones);
    setOpcionSeleccionada();
    setVectorOpciones(opciones);
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

    setOpcionSeleccionada();
}

void Menu::setCantidadOpciones(int cantidad){
    _cantidadOpciones = cantidad;
}

void Menu::setNombreMenu(std::string nombre = "Menu"){
    _nombreMenu = nombre;
}

void Menu::setOpcionSeleccionada(int opcion = 99){
    _opcionSeleccionada = opcion;
}

std::string Menu::getNombreMenu(){ return _nombreMenu; }

void Menu::ejecutarOpcion(){
    switch (_opcionSeleccionada) {
        case 1:
            break;

        case 2:
            break;

        case 3:
            break;

        case 0:
            return;

        default:
            std::cout << "Intente nuevamente\n";
            break;
    }
}

/// @brief bucle para seleccionar una opcion. No permite salida hasta que
/// se encuentre dentro de los parametros
void Menu::seleccionarOpcion(){
    int opcion = 99;

    while (opcion < 0 && opcion > _cantidadOpciones){
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;
    }

    setOpcionSeleccionada(opcion);
}

/// @brief Recorre las opciones y las muestra por pantalla, una debajo de la otra
/// estilo "x. opcion". Finaliza con "0. Salir".
void Menu::mostrarOpciones(){
    std::cout << getNombreMenu << "\n";
    std::cout << "==============================\n";

    for (int i = 1; i < _cantidadOpciones + 1; i++) {
        std::cout << i << ". " << _opciones[i - 1] << "\n";
    }

    std::cout << "------------------------------\n";
    std::cout << "0. Salir\n";
}

/// @brief Se utiliza memoria dinamica para crear vector de strings.
/// En caso de que no se pueda asignar memoria, el puntero _opciones
/// permanecera nulo.
/// @param opciones vector de opciones. Solo se leera y asignara la cantidad
/// propuesta en "cantidadOpciones".
void Menu::setVectorOpciones(std::string opciones[]){
    // Solicitar memoria para vector de strings
    std::string *vOpciones = new std::string[_cantidadOpciones];

    if (vOpciones != nullptr) {
        // Se le puede asignar valores
        for (int i=0; i < _cantidadOpciones; i++) {
            vOpciones[i] = opciones[i];
        }
    } else {
        // Dejar puntero nulo
        std::cout << "Error al asignarle memoria a las opciones del menu";
    }
    
    _opciones = vOpciones;
}
