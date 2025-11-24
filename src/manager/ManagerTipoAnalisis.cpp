#include "manager/ManagerTipoAnalisis.h"
#include "TipoAnalisis.h"
#include "utils/IngresarDatos.h"
#include <string>
#include <cstring>
#include <iomanip> //chequear uso



ManagerTipoAnalisis::ManagerTipoAnalisis(){};

//VALIDACION: Comprueba que exista el ID

bool ManagerTipoAnalisis::comprobar(int idTipoAnalisis) {

    TipoAnalisis regTipoAnalisis;
    int cantidadTipoAnalisis = _repo.cantidadRegistros();

    if (cantidadTipoAnalisis == 0) {
        std::cout << "\nRegistro vacio.\n" << std::endl;
        return false;
    }

    //Posterior a comprobar el registro, sin ID ingresado retorna.
    if (idTipoAnalisis == -1) {
        return true;
    }

    regTipoAnalisis = _repo.leer(idTipoAnalisis-1);

    if (idTipoAnalisis==regTipoAnalisis.getID() && regTipoAnalisis.getEliminado()==0) {
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

void ManagerTipoAnalisis::mostrarTodos(){
    TipoAnalisis regTipoAnalisis;
    int cantidadTipoAnalisis = _repo.cantidadRegistros();

    std::cout << "ID\tTipo\t\tTiempo estimado\tPrecio\tDatos\n\n";

    for(int i=0; i<cantidadTipoAnalisis; i++) {
        regTipoAnalisis = _repo.leer(i);

            std::cout << regTipoAnalisis.getID() << "\t";
            std::cout << regTipoAnalisis.getNombreAnalisis() << "\t\t";
            std::cout << regTipoAnalisis.getTiempoResultado() << " dias\t";
            std::cout << "\t$ " << regTipoAnalisis.getPrecio() << "\t";
            (regTipoAnalisis.getEliminado())? std::cout << "Eliminado\n" : std::cout << "Existente\n";
    }
}

bool ManagerTipoAnalisis::ingresarDatos(TipoAnalisis &tipoAnalisis, bool nuevoId) {
    int idTipoAnalisis;
    std::string nombre;
    float precio = 0;
    int tiempoResultado = 0;
    char confirmar;

    IngresarDatos ingresar;

    if (nuevoId==true) {
        idTipoAnalisis = _repo.cantidadRegistros()+1;
    } else {
        idTipoAnalisis = tipoAnalisis.getID();
    }

    std::cin.ignore(100, '\n');

    if (!ingresar.nombre(nombre)) {
        return false;
        //Carga cancelada
    }
    if (!ingresar.tiempoResultado(tiempoResultado)){
        return false;
        //Carga cancelada
    }
    if (!ingresar.precio(precio)){
        return false;
        //Carga cancelada
    }

    tipoAnalisis = TipoAnalisis(idTipoAnalisis, nombre.c_str(), tiempoResultado, precio);
    return true;
}

bool ManagerTipoAnalisis::cargarDatos(TipoAnalisis tipoAnalisis) {
    const int cantidadRegistros = _repo.cantidadRegistros();
    TipoAnalisis* regTipoAnalisis = _repo.leerTodos();
    bool cargaValida = true;

    //CHEQUEO VALORES REPETIDOS

    for (int i = 0; i < cantidadRegistros; i++){

        if (regTipoAnalisis[i].getEliminado()) {
            continue;
        }
        if (strcmp(tipoAnalisis.getNombreAnalisis(),regTipoAnalisis[i].getNombreAnalisis()) == 0) {
            std::cout << "\nERROR: El nombre ingresado ya existe.\n";
            cargaValida = false;
            break;
        }
    }

    delete[] regTipoAnalisis; //Devuelvo la memoria de repo.leerTodos.}

    if (!cargaValida) {
        return false;
    }

    if (_repo.guardar(tipoAnalisis)) {
        //CARGA OK
        return true;
    } else {
        std::cout << "\nATENCION: Error al intentar guardar el tipo de analisis. ";
        return false;
    }
}

bool ManagerTipoAnalisis::actualizar(TipoAnalisis tipoAnalisis){
    std::string nombre;
    int tiempoResultado;
    float precio;
    char confirmar;

    //CHEQUEO VALORES REPETIDOS

    const int cantidadRegistros = _repo.cantidadRegistros();
    TipoAnalisis* regTipoAnalisis = _repo.leerTodos();
    bool cargaValida = true;

    for (int i = 0; i < cantidadRegistros; i++){

        if (regTipoAnalisis[i].getEliminado()) {
            continue;
        }
        if (strcmp(tipoAnalisis.getNombreAnalisis(),regTipoAnalisis[i].getNombreAnalisis()) == 0) {
            std::cout << "\nERROR: El nombre ingresado ya existe.\n";
            cargaValida = false;
            break;
        }
    }

    delete[] regTipoAnalisis; //Devuelvo la memoria de repo.leerTodos.}

    if (!cargaValida) {
        return false;
    }

    if (_repo.modificar(tipoAnalisis, tipoAnalisis.getID()-1)) {
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

    tipoAnalisis.setEliminado(true);

    if (_repo.modificar(tipoAnalisis,tipoAnalisis.getID()-1)){
        return true;
    } else {
        std::cout << "\nATENCION: Error al intentar eliminar el tipo de analisis.\n";
        return false;
    }
}
