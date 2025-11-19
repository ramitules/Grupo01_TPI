#include "menu/MenuConfiguracion.h"
#include "utils/funcBackend.h"
#include <iostream>


MenuConfiguracion::MenuConfiguracion(): Menu(3, "Menu Configuracion"){
    std::string opciones[3] = {
        "Realizar copia de seguridad",
        "Restaurar copia de seguridad",
        "Paleta de colores"
    };

    setVectorOpciones(opciones);
    setSalir(false);
}

void MenuConfiguracion::ejecutarOpcion(){
    if (_opcionSeleccionada == 1) {
        return backup();
    } 
    
    if (_opcionSeleccionada == 2) {
        return restaurarBackup();
    }

    if (_opcionSeleccionada == 3) {
        return paletaColores();
    }
}
