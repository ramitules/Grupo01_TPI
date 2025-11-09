#include "manager/ManagerTipoAnalisis.h"
#include "manager/ManagerSecuencia.h"

ManagerTipoAnalisis::ManagerTipoAnalisis(){};

bool ManagerTipoAnalisis::cargar(){
    std::cin.ignore(100, '\n');

    ManagerSecuencia mSecuencia;
    Secuencia sec = mSecuencia.cargar("TipoAnalisis");

    int proximoID = sec.getIdActual() + 1;
    std::string nombre;
    float precio = 0.0f;
    int tiempoResultado = 0;

    std::cout << "Ingrese el nombre del tipo de analisis: ";
    std::getline(std::cin, nombre);
    
    if (nombre == "") {
        std::cout << "No se puede continuar sin un nombre de tipo de analisis.\n";
        return false;
    }

    std::cout << "Ingrese el tiempo estimado del resultado (dias): ";
    std::cin >> tiempoResultado;

    if (tiempoResultado <= 0) {
        std::cout << "No se puede continuar, plazo minimo de 1 dia.\n";
        return false;
    }

    std::cout << "Ingrese el precio del tipo de analisis ($): ";
    std::cin >> precio;
    
    if (precio <= 0) {
        std::cout << "No se puede continuar sin un precio mayor a 0.\n";
        return false;
    }

    TipoAnalisis tipoAnalisis(proximoID, nombre.c_str(), tiempoResultado, precio);

    if (_repo.guardar(tipoAnalisis)) {
        std::cout << "El tipo de analisis se ha guardado correctamente.\n";
        return true;
    }

    std::cout << "Ocurrio un error al intentar guardar el tipo de analisis.\n";
    return false;
}

void ManagerTipoAnalisis::mostrar(TipoAnalisis tipoAnalisis){
    std::cout << "ID: " << tipoAnalisis.getID() << "\n";
    std::cout << "Nombre del analisis: " << tipoAnalisis.getNombreAnalisis() << "\n";
    std::cout << "Precio: $" << tipoAnalisis.getPrecio() << "\n";
}

void ManagerTipoAnalisis::mostrarTodos(){
    for(int i=0; i<_repo.cantidadRegistros(); i++){
        this->mostrar(_repo.leer(i));
    }
}

bool ManagerTipoAnalisis::actualizar(TipoAnalisis tipoAnalisis){
    // PENDIENTE
}

bool ManagerTipoAnalisis::eliminar(TipoAnalisis tipoAnalisis){
    char opc;

    std::cout << "Seguro que desea eliminar el tipo de analisis? s/n: ";
    std::cin >> opc;

    if (opc == 's') {
        if (_repo.eliminar(_repo.getPos(tipoAnalisis.getID()))){
            std::cout << "El tipo de analisis se ha eliminado correctamente.\n";
            return true;
        } else {
            std::cout << "Ocurrio un error al intentar eliminar el tipo de analisis.\n";
            return false;
        }
    }

    std::cout << "Operacion cancelada.\n";
    return false;
}
