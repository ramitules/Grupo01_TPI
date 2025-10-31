#include "menu/MenuTipoAnalisis.h"
#include "manager/ManagerTipoAnalisis.h"
#include "TipoAnalisis.h"
#include <iostream>


MenuTipoAnalisis::MenuTipoAnalisis(): Menu(3, "Menu Tipos de Analisis"){
    std::string opciones[3] = {
        "Crear nuevo tipo de analisis",
        "Modificar tipo de analisis",
        "Eliminar tipo de analisis"
    };

    setVectorOpciones(opciones);
    setSalir(false);
}

void MenuTipoAnalisis::ejecutarOpcion(){
    ManagerTipoAnalisis mTipoAnalisis;
    TipoAnalisis  AuxTipoAnalisis;

    switch (_opcionSeleccionada) {
        case 0:
            return;
        case 1:
            mTipoAnalisis.cargar();
            break;
        case 2:
            mTipoAnalisis.mostrarTodos();
            // mTipoAnalisis.actualizar();
            break;
        case 3: {
            std::cout << "Acá se elimina";
            break;
        }


        default:
            std::cout << "Intente nuevamente\n";
            break;
    }
}
