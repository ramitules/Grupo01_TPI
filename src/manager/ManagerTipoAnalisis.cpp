#include "manager/ManagerTipoAnalisis.h"
#include <string>
#include <iomanip>
#include <algorithm>
#include <cstring>

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

    regTipoAnalisis = _repo.leer(_repo.getPos(idTipoAnalisis));

    if (idTipoAnalisis==regTipoAnalisis.getID() && !regTipoAnalisis.getEliminado()) {
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

    regTipoAnalisis = _repo.leer(_repo.getPos(idTipoAnalisis));
    return regTipoAnalisis;
}

std::string ManagerTipoAnalisis::mostrarCabecera(int anchoID, int anchoNombreAnalisis, int anchoPrecio, int anchoTiempo){
    // -- Mostrar tabla --
    std::cout << std::left; // Alinear a la izquierda

    // Linea horizontal
    std::string linea = "+" + std::string(anchoID + 2, '-') + 
                        "+" + std::string(anchoNombreAnalisis + 2, '-') + 
                        "+" + std::string(anchoPrecio + 2, '-') + 
                        "+" + std::string(anchoTiempo + 2, '-') + "+\n";
    // Cabeceras
    std::cout << linea;
    std::cout << "| " << std::setw(anchoID) << "ID" << " | "
              << std::setw(anchoNombreAnalisis) << "Nombre Analisis" << " | "
              << std::setw(anchoPrecio) << "Precio" << " | "
              << std::setw(anchoTiempo) << "Tiempo" << " |\n";
    std::cout << linea;

    return linea;
}

void ManagerTipoAnalisis::mostrarUno(TipoAnalisis tipoAnalisis){
    // -- Calcular ancho maximo --
    int anchoID = 5;  
    int anchoNombreAnalisis = 6;
    int anchoPrecio = 8;
    int anchoTiempo = 9;

    anchoID = std::max(anchoID, (int)std::to_string(tipoAnalisis.getID()).length());
    anchoNombreAnalisis = std::max(anchoNombreAnalisis, (int)strlen(tipoAnalisis.getNombreAnalisis()));
    anchoPrecio = std::max(anchoPrecio, (int)std::to_string(tipoAnalisis.getPrecio()).length() + 3);
    anchoTiempo = std::max(anchoTiempo, (int)std::to_string(tipoAnalisis.getTiempoResultado()).length());

    std::string linea = mostrarCabecera(anchoID, anchoNombreAnalisis, anchoPrecio, anchoTiempo);

    std::cout << "| " << std::setw(anchoID) << tipoAnalisis.getID() << " | "
              << std::setw(anchoNombreAnalisis) << tipoAnalisis.getNombreAnalisis() << " | "
              << std::setw(anchoPrecio) << tipoAnalisis.getPrecio() << " | "
              << std::setw(anchoTiempo) << tipoAnalisis.getTiempoResultado() << " |\n";

    std::cout << linea;
}

void ManagerTipoAnalisis::mostrarVarios(TipoAnalisis* tipoAnalisis, const int cantidad) {
    if (cantidad == 0) {
        std::cout << "No hay tipos de analisis para mostrar.\n";
        return;
    }

    // -- Calcular ancho maximo de columnas --
    int anchoID = 5;
    int anchoNombreAnalisis = 6;
    int anchoPrecio = 8;
    int anchoTiempo = 9;

    for(int i=0; i<cantidad; i++) {
        if (tipoAnalisis[i].getEliminado()) {
            continue;
        }

        anchoID = std::max(anchoID, (int)std::to_string(tipoAnalisis[i].getID()).length());
        anchoNombreAnalisis = std::max(anchoNombreAnalisis, (int)strlen(tipoAnalisis[i].getNombreAnalisis()));
        anchoPrecio = std::max(anchoPrecio, (int)std::to_string(tipoAnalisis[i].getPrecio()).length() + 3);
        anchoTiempo = std::max(anchoTiempo, (int)std::to_string(tipoAnalisis[i].getTiempoResultado()).length());
    }

    std::string linea = mostrarCabecera(anchoID, anchoNombreAnalisis, anchoPrecio, anchoTiempo);

    // Datos
    for(int i=0; i<cantidad; i++){
        if (tipoAnalisis[i].getEliminado()) {
            continue;
        }
        
        std::cout << "| " << std::setw(anchoID) << tipoAnalisis[i].getID() << " | " 
                  << std::setw(anchoNombreAnalisis) << tipoAnalisis[i].getNombreAnalisis() << " | "
                  << std::setw(anchoPrecio) << std::fixed << std::setprecision(2) << tipoAnalisis[i].getPrecio() << " | "
                  << std::setw(anchoTiempo) << tipoAnalisis[i].getTiempoResultado() << " |\n";
    }

    std::cout << linea;
}

void ManagerTipoAnalisis::mostrar(TipoAnalisis tipoAnalisis){
    std::cout << "\nID\tTipo\tTiempo estimado\tPrecio\n";
    std::cout << tipoAnalisis.getID() << "\t" ;
    std::cout << tipoAnalisis.getNombreAnalisis() << "\t";
    std::cout << tipoAnalisis.getTiempoResultado() << " dias\t";
    std::cout << "\t$ " << tipoAnalisis.getPrecio() << "\n";
}

bool ManagerTipoAnalisis::mostrarTodos(){
    const int CANTIDAD = _repo.cantidadRegistros();
    TipoAnalisis* todos = _repo.leerTodos();
    
    mostrarVarios(todos, CANTIDAD);
    delete[] todos;
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

    for (int i = 0; i < _repo.cantidadRegistros(); ++i) {
        TipoAnalisis existeTipoAnalisis = _repo.leer(i);
        if (!existeTipoAnalisis.getEliminado() && existeTipoAnalisis.getNombreAnalisis() == nombre) {
            std::cout << "ATENCION: Ya existe un tipo de analisis con ese nombre.\n";
            system("pause");
            return false;
        }
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

void ManagerTipoAnalisis::listadoXnombre() {
    const int CANTIDAD = _repo.cantidadRegistros();
    TipoAnalisis *regTipoAnalisis = _repo.leerTodos(); //Pide memoria
    TipoAnalisis aux;

    // Ordenar
    for (int i=0; i<CANTIDAD; i++) {

        for (int j=i+1; j<CANTIDAD; j++) {
            std::string nombre1 =regTipoAnalisis[i].getNombreAnalisis();
            std::string nombre2 =regTipoAnalisis[j].getNombreAnalisis();

            if (nombre1 > nombre2) {
                aux = regTipoAnalisis[i];
                regTipoAnalisis[i] = regTipoAnalisis[j];
                regTipoAnalisis[j] = aux;
            }
        }
    }

    // Mostrar

    std::cout << "Tipo\t\tID\tTiempo estimado\tPrecio\n\n";

    for(int i=0; i<CANTIDAD; i++){

        if (regTipoAnalisis[i].getEliminado()!=true) {
            std::cout << regTipoAnalisis[i].getNombreAnalisis() << "\t\t";
            std::cout << regTipoAnalisis[i].getID() << "\t";
            std::cout << regTipoAnalisis[i].getTiempoResultado() << " dias\t";
            std::cout << "\t$ " << regTipoAnalisis[i].getPrecio() << "\n";
        }
    }

    delete [] regTipoAnalisis;
        //rlutil::anykey();
        //separadorParcial();
}

void ManagerTipoAnalisis::listadoXvalor() {
    const int CANTIDAD = _repo.cantidadRegistros();
    TipoAnalisis *regTipoAnalisis = _repo.leerTodos(); //Pide memoria
    TipoAnalisis aux;

    // Ordenar
    for (int i=0; i<CANTIDAD; i++) {

        for (int j=i+1; j<CANTIDAD; j++) {
            std::string nombre1 =regTipoAnalisis[i].getNombreAnalisis();
            std::string nombre2 =regTipoAnalisis[j].getNombreAnalisis();

            if (regTipoAnalisis[i].getPrecio() > regTipoAnalisis[j].getPrecio()) {
                aux = regTipoAnalisis[i];
                regTipoAnalisis[i] = regTipoAnalisis[j];
                regTipoAnalisis[j] = aux;
            }
        }
    }

    // Mostrar

    std::cout << "Precio\tID\tTipo\t\tID\tTiempo estimado\n\n";

    for(int i=0; i<CANTIDAD; i++){

        if (regTipoAnalisis[i].getEliminado()!=true) {
            std::cout << "$ " << regTipoAnalisis[i].getPrecio() << "\t";
            std::cout << regTipoAnalisis[i].getID() << "\t";
            std::cout << regTipoAnalisis[i].getNombreAnalisis() << "\t\t";
            std::cout << regTipoAnalisis[i].getTiempoResultado() << " dias\n";
        }
    }

    delete [] regTipoAnalisis;
    //rlutil::anykey();
    //separadorParcial();
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

ArchivoTipoAnalisis ManagerTipoAnalisis::getRepositorio(){
    return _repo;
}
