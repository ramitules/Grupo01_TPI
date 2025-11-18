#include "manager/ManagerTipoAnalisis.h"
#include <string>

ManagerTipoAnalisis::ManagerTipoAnalisis(){};

TipoAnalisis ManagerTipoAnalisis::seleccionar(int idTipoAnalisis) {
    TipoAnalisis regTipoAnalisis;

    regTipoAnalisis = _repo.leer(idTipoAnalisis-1);
    return regTipoAnalisis;
}

bool ManagerTipoAnalisis::comprobar(int idTipoAnalisis) {
    TipoAnalisis regTipoAnalisis;
    int cantidadTipoAnalisis = _repo.cantidadRegistros();

    if (cantidadTipoAnalisis <= 0) {
        std::cout << "\nRegistro vacio: No se pudo encontrar un Tipo de Analisis\n" << std::endl;
        return false;
    }

    regTipoAnalisis = _repo.leer(idTipoAnalisis-1);

    if (idTipoAnalisis==regTipoAnalisis.getID() && regTipoAnalisis.getEliminado()!=true) {
        std::cout << "Tipo de Analisis encontrado";
        return true;
    }
    else {
        std::cout << "No existe el Tipo de Analisis ingresado\n" << std::endl;
        return false;
    }
}

void ManagerTipoAnalisis::mostrar(TipoAnalisis tipoAnalisis){
    std::cout << "ID\tTipo\tTiempo estimado\tPrecio\n" << std::endl;
    std::cout << tipoAnalisis.getID() << "\t" ;
    std::cout << tipoAnalisis.getNombreAnalisis() << "\t";
    std::cout << tipoAnalisis.getTiempoResultado() << " dias\t";
    std::cout << "\t$ " << tipoAnalisis.getPrecio() << "\n" << std::endl;
}

bool ManagerTipoAnalisis::mostrarTodos(){
    TipoAnalisis regTipoAnalisis;
    int cantidadTipoAnalisis = _repo.cantidadRegistros();

    if (cantidadTipoAnalisis >= 1) {
        std::cout << "ID\tTipo\tTiempo estimado\tPrecio\n" << std::endl;
    }
    else {
        std::cout << "\nRegistro vacio\n" << std::endl;
        return false;
    }

    for(int i=0; i<cantidadTipoAnalisis; i++){
        regTipoAnalisis = _repo.leer(i);

        if (regTipoAnalisis.getEliminado()!=true) {
            std::cout << regTipoAnalisis.getID() << "\t" ;
            std::cout << regTipoAnalisis.getNombreAnalisis() << "\t";
            std::cout << regTipoAnalisis.getTiempoResultado() << " dias\t";
            std::cout << "\t$ " << regTipoAnalisis.getPrecio() << "\n";
        }
    }

    std::cout << std::endl;
    return true;
}

bool ManagerTipoAnalisis::cargar(){

    int tipoAnalisisID = _repo.cantidadRegistros()+1;

    char opc;

    std::string nombre;
    float precio = 0.0f;
    int tiempoResultado = 0;

    std::cin.ignore(100, '\n');

    std::cout << "Ingrese el nombre: ";
    std::getline(std::cin, nombre);
    
    if (nombre == "") {
        std::cout << "No se puede continuar sin un nombre de tipo de analisis.\n";
        system("pause");
        return false;
    }

    std::cout << "Tiempo del resultado (dias): ";
    std::cin >> tiempoResultado;

    if (tiempoResultado <= 0) {
        std::cout << "No se puede continuar, plazo minimo de 1 dia.\n";
        system("pause");
        return false;
    }

    std::cout << "Precio ($): ";
    std::cin >> precio;
    
    if (precio <= 0) {
        std::cout << "No se puede continuar sin un precio mayor a 0.\n";
        system("pause");
        return false;
    }

    TipoAnalisis tipoAnalisis(tipoAnalisisID, nombre.c_str(), tiempoResultado, precio);
    mostrar(tipoAnalisis);

    std::cout << "Cargar los datos s/n: ";
    std::cin >> opc;

    if (opc != 's') {
        std::cout << "No se cargaron los datos\n";
        return false;
    }

    if (_repo.guardar(tipoAnalisis)) {
        std::cout << "\nEl tipo de analisis se ha cargado correctamente.\n" << std::endl;
        return true;
    }

    std::cout << "Ocurrio un error al intentar guardar el tipo de analisis.\n";
    return false;
}

bool ManagerTipoAnalisis::actualizar(TipoAnalisis tipoAnalisis){
    std::string nombre;
    int tiempoResultado, precio;
    char opc;

    std::cout << "Nombre actual: " << tipoAnalisis.getNombreAnalisis() << "\n";
    std::cout << "Nuevo nombre: ";
    std::cin.ignore(100, '\n');
    std::getline(std::cin, nombre); tipoAnalisis.setNombreAnalisis(nombre.c_str());

    std::cout << "Tiempo actual: " << tipoAnalisis.getTiempoResultado() << "\n";
    std::cout << "Nuevo Tiempo: ";
    std::cin >> tiempoResultado;
    tipoAnalisis.setTiempoResultado(tiempoResultado);

    std::cout << "Precio actual: " << tipoAnalisis.getPrecio() << "\n";
    std::cout << "Nuevo Precio: ";
    std::cin >> precio; tipoAnalisis.setPrecio(precio);
    std::cout << std::endl;

    mostrar(tipoAnalisis);

    std::cout << "Modificar los datos s/n: ";
    std::cin >> opc;

    if (opc != 's') {
        std::cout << "No se modificaron los datos\n";
        return false;
    }

    if (_repo.modificar(tipoAnalisis, tipoAnalisis.getID()-1)) {
        std::cout << "\nEl tipo de analisis se ha modificado correctamente.\n" << std::endl;
        return true;
    }
    return true;
}

bool ManagerTipoAnalisis::eliminar(TipoAnalisis tipoAnalisis){
    char opc;

    std::cout << "\nSeguro que desea eliminar el tipo de analisis? s/n: ";
    std::cin >> opc;

    if (opc == 's') {
        tipoAnalisis.setEliminado(true);
        if (_repo.modificar(tipoAnalisis,tipoAnalisis.getID()-1)){
            std::cout << "\nEl tipo de analisis se ha eliminado correctamente.\n" << std::endl;
            return true;
        } else {
            std::cout << "\nOcurrio un error al intentar eliminar el tipo de analisis.\n";
            return false;
        }
    }

    std::cout << "Operacion cancelada.\n";
    return false;
}
