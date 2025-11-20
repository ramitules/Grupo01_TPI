#include "manager/ManagerTipoAnalisis.h"
#include <string>
#include <iomanip>

ManagerTipoAnalisis::ManagerTipoAnalisis(){};

//VALIDACION: Comprueba que exista el ID

bool ManagerTipoAnalisis::comprobar(int idTipoAnalisis) {
    TipoAnalisis regTipoAnalisis;
    int cantidadTipoAnalisis = _repo.cantidadRegistros();

    if (cantidadTipoAnalisis <= 0) {
        std::cout << "\nRegistro vacio.\n\n" << std::endl;
        return false;
    }

    if (idTipoAnalisis == -1) { // valor por defecto: no se ingresó parametro
        return true;
    }

    regTipoAnalisis = _repo.leer(idTipoAnalisis-1);

    if (idTipoAnalisis==regTipoAnalisis.getID() && regTipoAnalisis.getEliminado()!=true) {
        //std::cout << "Tipo de Analisis encontrado";
        return true;
    }
    else {
        std::cout << "\nATENCION: ID Tipo Analisis no existente.\n" << std::endl;
        return false;
    }
}

//RETORNA EL OBJETO CON EL ID SELECCIONADO

TipoAnalisis ManagerTipoAnalisis::seleccionar(int idTipoAnalisis) {
    TipoAnalisis regTipoAnalisis;

    regTipoAnalisis = _repo.leer(idTipoAnalisis-1);
    return regTipoAnalisis;
}

void ManagerTipoAnalisis::mostrar(TipoAnalisis tipoAnalisis){
    std::cout << "\nID\tTipo\tTiempo estimado\tPrecio\n";
    std::cout << tipoAnalisis.getID() << "\t" ;
    std::cout << tipoAnalisis.getNombreAnalisis() << "\t";
    std::cout << tipoAnalisis.getTiempoResultado() << " dias\t";
    std::cout << "\t$ " << tipoAnalisis.getPrecio() << "\n";
}

bool ManagerTipoAnalisis::mostrarTodos(){
    TipoAnalisis regTipoAnalisis;
    int cantidadTipoAnalisis = _repo.cantidadRegistros();

    std::cout << "ID\tTipo\t\tTiempo estimado\tPrecio\n\n";

    for(int i=0; i<cantidadTipoAnalisis; i++){
        regTipoAnalisis = _repo.leer(i);

        if (regTipoAnalisis.getEliminado()!=true) {
            std::cout << regTipoAnalisis.getID() << "\t";
            std::cout << regTipoAnalisis.getNombreAnalisis() << "\t\t";
            std::cout << regTipoAnalisis.getTiempoResultado() << " dias\t";
            std::cout << "\t$ " << regTipoAnalisis.getPrecio() << "\n";
        }
    }
    std::cout << std::endl;
    return true;
}

bool ManagerTipoAnalisis::cargar(){

    int tipoAnalisisID = _repo.cantidadRegistros()+1;

    std::string nombre;
    float precio = 0.0f;
    int tiempoResultado = 0;
    char opc;

    std::cin.ignore(100, '\n');

    std::cout << "\nIngrese el nombre: ";
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
    std::cout << "\n";
    if (precio <= 0) {
        std::cout << "No se puede continuar sin un precio mayor a 0.\n";
        system("pause");
        return false;
    }

    TipoAnalisis tipoAnalisis(tipoAnalisisID, nombre.c_str(), tiempoResultado, precio);
    mostrar(tipoAnalisis);

    std::cout << "CONFIRMAR: Cargar los datos s/n: ";
    std::cin >> opc;
    std::cout << "\n";

    if (opc != 's') {
        std::cout << "ATENCION: No se cargaron los datos\n\n";
        return false;
    }

    if (_repo.guardar(tipoAnalisis)) {
        std::cout << "El tipo de analisis se ha cargado correctamente.\n\n";
        return true;
    }

    std::cout << "ATENCION: Ocurrio un error al intentar guardar el tipo de analisis.\n\n";
    return false;
}

bool ManagerTipoAnalisis::actualizar(TipoAnalisis tipoAnalisis){
    std::string nombre;
    int tiempoResultado, precio;
    char opc;

    std::cout << "\nNombre actual: " << tipoAnalisis.getNombreAnalisis() << "\n";
    std::cout << "Nuevo nombre: ";
    std::cin.ignore(100, '\n');
    std::getline(std::cin, nombre);
    tipoAnalisis.setNombreAnalisis(nombre.c_str());

    std::cout << "\nTiempo actual: " << tipoAnalisis.getTiempoResultado() << "\n";
    std::cout << "Nuevo Tiempo: ";
    std::cin >> tiempoResultado;
    tipoAnalisis.setTiempoResultado(tiempoResultado);

    std::cout << "\nPrecio actual: " << tipoAnalisis.getPrecio() << "\n";
    std::cout << "Nuevo Precio: ";
    std::cin >> precio; tipoAnalisis.setPrecio(precio);


    mostrar(tipoAnalisis);

    std::cout << "\nModificar los datos s/n: ";
    std::cin >> opc;

    if (opc != 's') {
        std::cout << "\nATENCION: No se modificaron los datos\n\n";
        return false;
    }

    if (_repo.modificar(tipoAnalisis, tipoAnalisis.getID()-1)) {
        std::cout << "\nEl tipo de analisis se ha modificado correctamente.\n\n";
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
            std::cout << "\nSe ha eliminado correctamente.\n\n" << std::endl;
            return true;
        } else {
            std::cout << "\nATENCION: Error al intentar eliminar el tipo de analisis.\n\n";
            return false;
        }
    }

    std::cout << "\nATENCION: No se eliminaron los datos.\n\n";
    return false;
}
