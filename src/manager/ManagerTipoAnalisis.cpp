#include "manager/ManagerTipoAnalisis.h"
#include "manager/ManagerSecuencia.h"
#include "secuencia.h"

ManagerTipoAnalisis::ManagerTipoAnalisis(){};

TipoAnalisis ManagerTipoAnalisis::seleccionar() {
    TipoAnalisis auxTipoAnalisis;
    int Id;

    std::cout << "Ingrese el ID del Tipo de Analisis a modificar: ";
    std::cin.ignore(100, '\n');
    std::cin >> Id;

    auxTipoAnalisis = _repo.leer(Id-1);
    return auxTipoAnalisis;
}

void ManagerTipoAnalisis::mostrar(TipoAnalisis tipoAnalisis){
    for(int i=0; i<_repo.cantidadRegistros(); i++){
        this->mostrar(_repo.leer(i));
    }

    std::cout << "ID: " << tipoAnalisis.getID() << "\n";
    std::cout << "Nombre: " << tipoAnalisis.getNombreAnalisis() << "\n";
    std::cout << "Tiempo para el resultado: " << tipoAnalisis.getTiempoResultado() << "dias\n";
    std::cout << "Precio: $ " << tipoAnalisis.getPrecio() << "\n";
}

bool ManagerTipoAnalisis::mostrarTodos(){
    TipoAnalisis regTipoAnalisis;
    int cantidadTipoAnalisis = _repo.cantidadRegistros();

    if (cantidadTipoAnalisis >= 1) {
        std::cout << "ID\tTipo\tTiempo estimado\tPrecio\n" << std::endl;
    }
    else {
        std::cout << "Registro vacio";
        system("pause");
        return false;
    }

    for(int i=0; i<cantidadTipoAnalisis; i++){
        regTipoAnalisis = _repo.leer(i);

        if (regTipoAnalisis.getEliminado()==false) {
            std::cout << regTipoAnalisis.getID() << "\t" ;
            std::cout << regTipoAnalisis.getNombreAnalisis() << "\t";
            std::cout << regTipoAnalisis.getTiempoResultado() << " dias\t";
            std::cout << "\t$ " << regTipoAnalisis.getPrecio() << "\n";
        }
    }

    std::cout << std::endl;
    system("pause");
    return true;
}

bool ManagerTipoAnalisis::cargar(){
    std::cin.ignore(100, '\n');

    ManagerSecuencia mSecuencia;
    Secuencia secuencia = mSecuencia.cargar("TipoAnalisis");

    int tipoAnalisisID = secuencia.getIdActual();
    std::string nombre;
    float precio = 0.0f;
    int tiempoResultado = 0;

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

    this->mostrar(tipoAnalisis);

    if (_repo.guardar(tipoAnalisis)) {
        std::cout << "El tipo de analisis se ha guardado correctamente.\n";
        secuencia.setIdActual(tipoAnalisisID);
        mSecuencia.actualizar(secuencia);
        return true;
    }

    system("pause");
    std::cout << "Ocurrio un error al intentar guardar el tipo de analisis.\n";
    return false;
}

bool ManagerTipoAnalisis::actualizar(TipoAnalisis tipoAnalisis){
    std::string nombreTipoAnalisis;
    int tiempoResultado = 0;
    float precio = 0;

    std::cout << "Modificar\n" << std::endl ;
    std::cout << "Nombre" << tipoAnalisis.getNombreAnalisis() << "\n";
    std::cout << "Nuevo nombre: ";
    std::cin.ignore(100, '\n');
    std::getline(std::cin, nombreTipoAnalisis);
    std::cout << "Tiempo: " << tipoAnalisis.getTiempoResultado() << "\n";
    std::cout << "Nuevo Tiempo: ";
    std::cin >> tiempoResultado;
    std::cout << "Precio: " << tipoAnalisis.getPrecio() << "\n";
    std::cout << "Nuevo Precio: ";
    std::cin >> precio;
    std::cout << std::endl;

    tipoAnalisis.setNombreAnalisis(nombreTipoAnalisis.c_str());
    tipoAnalisis.setTiempoResultado(tiempoResultado);
    tipoAnalisis.setPrecio(precio);

    _repo.modificar(tipoAnalisis, tipoAnalisis.getID()-1);

/*
    void ManagerPersona::actualizar(Persona& persona){
        std::string nombre = persona.getNombre();
        std::string apellido = persona.getApellido();
        std::string email = persona.getEmail();
        int telefono = persona.getTelefono();
        Fecha fechaNacimiento = persona.getFechaNacimiento();
        char opc = 'n';

        ManagerFecha fecha;

        std::cin.ignore(100, '\n');

        std::cout << "El nombre es el mismo? s/n: ";
        std::cin >> opc;

        if (opc != 's') {
            std::cout << "Ingrese el nombre: ";
            std::getline(std::cin, nombre);

            if (nombre == "" || nombre == " ") {
                nombre = "Sin nombre";
            }

            persona.setNombre(nombre.c_str());
        }
    */
    return true;
}

bool ManagerTipoAnalisis::eliminar(TipoAnalisis tipoAnalisis){
    char opc;

    std::cout << "Seguro que desea eliminar el tipo de analisis? s/n: ";
    std::cin >> opc;

    if (opc == 's') {
        tipoAnalisis.setEliminado(true);
        if (_repo.modificar(tipoAnalisis,tipoAnalisis.getID()-1)){
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
