#include "manager/ManagerPaciente.h"
#include "manager/ManagerProtocolo.h"
#include "manager/ManagerTurno.h"
#include "utils/ManagerFecha.h"
#include "utils/ManagerHora.h"
#include "utils/rlutil.h"
#include "utils/funcFrontend.h"
#include "Paciente.h"
#include <algorithm>
#include <iomanip>


ManagerTurno::ManagerTurno(){};

bool ManagerTurno::cargar(){
    std::cin.ignore(100, '\n');

    ManagerPaciente mPaciente;
    ManagerFecha mFecha;
    ManagerHora mHora;

    int proximoID = _repo.cantidadRegistros() + 1;
    int dniPaciente;
    bool pacienteExiste = false;
    Fecha fechaAtencion;
    Hora horaAtencion;
    char opc = 'n';

    // Carga de paciente. Comienza con DNI
    while (true) {
        std::cout << "Ingrese el DNI del paciente: ";
        std::cin >> dniPaciente;

        if (dniPaciente > 10000000 && dniPaciente < 99999999) {
            break;
        }

        std::cout << "Intente nuevamente. Asegurese que sea un numero de 8 digitos.\n";
    }

    // Chequear si el paciente ya existe en la base de datos
    const int CANT_PACIENTES = mPaciente.getRepositorio().cantidadRegistros();

    for (int i = 0; i < CANT_PACIENTES; i ++) {
        if (mPaciente.getRepositorio().leer(i).getDNI() == dniPaciente) {
            pacienteExiste = true;
        }
    }

    // Dar la posibilidad de cargar todos los datos del paciente si no existe
    if (!pacienteExiste) {
        std::cout << "Paciente inexistente. Desea cargar sus datos ahora? s/n: ";
        std::cin >> opc;

        if (opc == 's') {
            if (!mPaciente.cargar(dniPaciente)) {
                std::cout << "No se pudo cargar el paciente. El turno no sera guardado.\n";
                std::cout << "Presione ENTER para continuar\n";
                rlutil::anykey();
                return false;
            }
        } else {
            Paciente paciente;
            paciente.setDNI(dniPaciente);
            mPaciente.getRepositorio().guardar(paciente);
        }
    }

    opc = 'n';

    std::cout << "El paciente se atendera ahora? s/n: ";
    std::cin >> opc;

    if (opc == 's') {
        ManagerProtocolo mProtocolo;
        mProtocolo.iniciar(proximoID);
        //Pendiente agregar lo que sigue
    }

    std::cin.ignore(100, '\n');

    fechaAtencion = mFecha.cargar();
    horaAtencion = mHora.cargar();

    Turno turno(proximoID, dniPaciente, fechaAtencion, horaAtencion, 0.0f);

    if (_repo.guardar(turno)) {
        std::cout << "El turno se ha guardado correctamente. Presione ENTER para continuar\n";
        rlutil::anykey();
        return true;
    }

    std::cout << "Ocurrio un error al intentar guardar el turno. Presione ENTER para continuar\n";
    rlutil::anykey();
    return false;
}

std::string ManagerTurno::mostrarCabecera(const int anchoPaciente, const int anchoFecha, const int anchoImporte) {
    // -- Mostrar tabla --
    std::cout << std::left; // Alinear a la izquierda

    // Linea horizontal
    std::string linea = "+" + std::string(5, '-') + 
                        "+" + std::string(anchoPaciente + 2, '-') + 
                        "+" + std::string(anchoFecha + 2, '-') + 
                        "+" + std::string(15, '-') +
                        "+" + std::string(anchoImporte + 2, '-') + "+\n";
    // Cabeceras
    std::cout << linea;
    std::cout << "| " << std::setw(3) << "ID" << " | " 
              << std::setw(anchoPaciente) << "Paciente" << " | "
              << std::setw(anchoFecha) << "Fecha atencion" << " | "
              << std::setw(13) << "Hora atencion" << " | "
              << std::setw(anchoImporte) << "Importe" << " |\n";
    std::cout << linea;

    return linea;
}

void ManagerTurno::mostrarUno(Turno turno){
    ManagerFecha mFecha;
    ManagerHora mHora;
    
    // -- Calcular ancho maximo --
    int anchoPaciente = 8; // Largo minimo "Paciente"
    int anchoFecha = 14;   // Largo minimo "Fecha Atencion"
    int anchoImporte = 7;  // Largo minimo "Importe"
    std::string nombreCompleto;
    std::string precioStr;

    nombreCompleto = turno.getPaciente().getNombre();
    nombreCompleto += " ";
    nombreCompleto += turno.getPaciente().getApellido();

    anchoPaciente = std::max(anchoPaciente, (int)nombreCompleto.length());
    anchoFecha = std::max(anchoFecha, (int)turno.getFechaAtencion().to_str().length());
    precioStr = std::to_string((int)turno.getImporte()) + ".00";
    anchoImporte = std::max(anchoImporte, (int)precioStr.length());

    std::string linea = mostrarCabecera(anchoPaciente, anchoFecha, anchoImporte);

    std::cout << "| " << std::setw(3) << turno.getID() << " | " 
              << std::setw(anchoPaciente) << nombreCompleto << " | "
              << std::setw(anchoFecha) << turno.getFechaAtencion().to_str() << " | "
              << std::setw(13) << turno.getHoraAtencion().to_str() << " | "
              << "$ " << std::setw(anchoImporte - 2) << std::fixed << std::setprecision(2) << turno.getImporte() << " |\n";
}

void ManagerTurno::mostrarVarios(Turno* turnos, const int cantidad) {
    if (cantidad == 0) {
        std::cout << "No hay turnos para mostrar.\n";
        return;
    }

    // -- Calcular ancho maximo de columnas --
    int anchoPaciente = 8; // Largo minimo "Paciente"
    int anchoFecha = 14;   // Largo minimo "Fecha Atencion"
    int anchoImporte = 7;  // Largo minimo "Importe"
    std::string nombreCompleto;
    std::string precioStr;

    for(int i=0; i<cantidad; i++) {
        if (turnos[i].getEliminado()) {
            continue;
        }
        nombreCompleto = turnos[i].getPaciente().getNombre();
        nombreCompleto += " ";
        nombreCompleto += turnos[i].getPaciente().getApellido();

        anchoPaciente = std::max(anchoPaciente, (int)nombreCompleto.length());
        anchoFecha = std::max(anchoFecha, (int)turnos[i].getFechaAtencion().to_str().length());
        precioStr = std::to_string((int)turnos[i].getImporte()) + ".00";
        anchoImporte = std::max(anchoImporte, (int)precioStr.length());
    }

    std::string linea = mostrarCabecera(anchoPaciente, anchoFecha, anchoImporte);

    // Datos
    for(int i=0; i<cantidad; i++){
        if (turnos[i].getEliminado()) {
            continue;
        }

        nombreCompleto = turnos[i].getPaciente().getNombre();
        nombreCompleto += " ";
        nombreCompleto += turnos[i].getPaciente().getApellido();
        
        std::cout << "| " << std::setw(3) << turnos[i].getID() << " | " 
                  << std::setw(anchoPaciente) << nombreCompleto << " | "
                  << std::setw(anchoFecha) << turnos[i].getFechaAtencion().to_str() << " | "
                  << std::setw(13) << turnos[i].getHoraAtencion().to_str() << " | "
                  << "$ " << std::setw(anchoImporte - 2) << std::fixed << std::setprecision(2) << turnos[i].getImporte() << " |\n";
    }

    std::cout << linea;
}

void ManagerTurno::mostrarTodos(){
    if (_repo.cantidadRegistros() == 0) {
        std::cout << "No hay turnos cargados en la base de datos.\n";
        return;
    }

    Turno* turnos = _repo.leerTodos();

    // -- Calcular ancho maximo --
    int anchoPaciente = 8; // Largo minimo "Paciente"
    int anchoFecha = 14;   // Largo minimo "Fecha Atencion"
    int anchoImporte = 7;  // Largo minimo "Importe"
    std::string nombreCompleto;
    std::string precioStr;

    for(int i=0; i<_repo.cantidadRegistros(); i++) {
        if (turnos[i].getEliminado()) {
            continue;
        }
        nombreCompleto = turnos[i].getPaciente().getNombre();
        nombreCompleto += " ";
        nombreCompleto += turnos[i].getPaciente().getApellido();

        anchoPaciente = std::max(anchoPaciente, (int)nombreCompleto.length());
        anchoFecha = std::max(anchoFecha, (int)turnos[i].getFechaAtencion().to_str().length());
        precioStr = std::to_string((int)turnos[i].getImporte()) + ".00";
        anchoImporte = std::max(anchoImporte, (int)precioStr.length());
    }

    std::string linea = mostrarCabecera(anchoPaciente, anchoFecha, anchoImporte);

    // Datos
    for(int i=0; i<_repo.cantidadRegistros(); i++){
        if (turnos[i].getEliminado()) {
            continue;
        }

        nombreCompleto = turnos[i].getPaciente().getNombre();
        nombreCompleto += " ";
        nombreCompleto += turnos[i].getPaciente().getApellido();
        
        std::cout << "| " << std::setw(3) << turnos[i].getID() << " | " 
                  << std::setw(anchoPaciente) << nombreCompleto << " | "
                  << std::setw(anchoFecha) << turnos[i].getFechaAtencion().to_str() << " | "
                  << std::setw(13) << turnos[i].getHoraAtencion().to_str() << " | "
                  << "$ " << std::setw(anchoImporte - 2) << std::fixed << std::setprecision(2) << turnos[i].getImporte() << " |\n";
    }

    std::cout << linea;
}

void ManagerTurno::ordenadosFecha(){
    const int CANTIDAD = _repo.cantidadRegistros();
    Turno *turnos = _repo.leerTodos();
    Turno aux;

    // Ordenar
    for (int i=0; i<CANTIDAD; i++) {
        if (turnos[i].getEliminado()) {

            continue;
        }

        for (int j=i+1; j<CANTIDAD; j++) {
            if (turnos[i].getFechaAtencion() > turnos[j].getFechaAtencion()) {
                aux = turnos[i];
                turnos[i] = turnos[j];
                turnos[j] = aux;
            } else if (turnos[i].getFechaAtencion() == turnos[j].getFechaAtencion()) {
                // Corroborar hora si la fecha es la misma
                if (turnos[i].getHoraAtencion() > turnos[j].getHoraAtencion()) {
                    aux = turnos[i];
                    turnos[i] = turnos[j];
                    turnos[j] = aux;
                }
            }
        }
    }

    // Mostrar
    mostrarVarios(turnos, CANTIDAD);

    // Finalizar
    delete[] turnos;
    std::cout << "Presione ENTER para continuar";
    rlutil::anykey();
}

void ManagerTurno::agrupadosPaciente(){
    const int CANTIDAD = _repo.cantidadRegistros();
    bool* indicesVisitados = new bool[CANTIDAD] {false};
    bool* indicesPacientes = new bool[CANTIDAD] {false};
    Turno *turnos = _repo.leerTodos();
    Paciente auxPaciente;

    int totalPacientes = 0;
    int iAux = 0;
    for (int i=0; i<CANTIDAD; i++) {
        if (indicesVisitados[i]) {      // Saltear turnos ya mostrados
            continue;
        }

        if (turnos[i].getEliminado()) { // y eliminados
            indicesVisitados[i] = true;
            continue;
        }

        auxPaciente = turnos[i].getPaciente();
        std::cout << "-- Turnos del paciente " << auxPaciente.getNombre() << ' ' << auxPaciente.getApellido() << " --\n";
       
        for (int j=0; j<CANTIDAD; j++) {
            if (turnos[i].getEliminado()) {
                continue;
            }
            if (indicesVisitados[j]) {
                continue;
            }

            if (turnos[j].getDniPaciente() == auxPaciente.getDNI()) {
                totalPacientes += 1;
                indicesVisitados[j] = true;
                indicesPacientes[j] = true;
            }
        }

        Turno *turnosPaciente = new Turno[totalPacientes];

        for (int j = 0; j < CANTIDAD; j ++) {
            if (indicesPacientes[j]) {
                turnosPaciente[iAux] = turnos[j];
                iAux ++;
            }
        }

        mostrarVarios(turnosPaciente, totalPacientes);
        std::cout << "\n\n";

        // Reiniciar variables
        totalPacientes = 0;
        iAux = 0;
        for (int j = 0; j < CANTIDAD; j ++) { indicesPacientes[j] = false; }
        delete[] turnosPaciente;
    }

    delete[] turnos;
    delete[] indicesVisitados;

    std::cout << "Presione ENTER para continuar";
    rlutil::anykey();
}

void ManagerTurno::busquedaFecha(){
    std::cin.ignore(100, '\n');

    const int CANTIDAD = _repo.cantidadRegistros();
    bool* indicesVisitados = new bool[CANTIDAD] {false};
    Turno *turnos = _repo.leerTodos();

    ManagerFecha mFecha;
    int dias = 0;

    std::cout << "-- Ingreso de rango de fechas --";
    std::cout << "DESDE\n";
    Fecha desde = mFecha.cargar();
    
    while (true) {
        std::cout << "Cantidad de dias (1 = solo la fecha ingresada): \n";
        std::cin >> dias;

        if (dias > 0 && dias < 366) {
            break;
        }

        if (dias > 365) {
            std::cout << "No se permiten busquedas superiores a 365 dias. Intente nuevamente\n";
        }

        if (dias < 1) {
            std::cout << "No se permiten dias negativos. Intente nuevamente\n";
        }
    }

    buscando();
    
    bool mostrarLeyenda = true;

    if (dias == 1) {
        for (int i=0; i<CANTIDAD; i++) {
            if (turnos[i].getEliminado()) {
                continue;
            }

            if (turnos[i].getFechaAtencion() == desde) {
                if (mostrarLeyenda) {
                    mostrarLeyenda = false;
                    std::cout << "-- Se encontraron los siguientes turnos en la fecha provista --\n";
                }

                mostrarUno(turnos[i]);
                std::cout << "\n\n";
            }
        }
    } else {
        Fecha* fechasElegidas = mFecha.rangoFechas(desde, dias);

        for (int i=0; i<CANTIDAD; i++) {
            if (turnos[i].getEliminado()) {
                continue;
            }
            
            for (int j=0; j<dias; j++) {
                if (turnos[i].getFechaAtencion() == fechasElegidas[j]) {
                    if (mostrarLeyenda) {
                        mostrarLeyenda = false;
                        std::cout << "-- Se encontraron los siguientes turnos en el rango de fechas provisto --\n";
                    }

                    mostrarUno(turnos[i]);
                    std::cout << "\n\n";
                }
            }
        }

        delete[] fechasElegidas;
    }
    delete[] turnos;
    delete[] indicesVisitados;

    std::cout << "Presione ENTER para continuar";
    rlutil::anykey();
}

void ManagerTurno::busquedaPaciente(){
    std::cin.ignore(100, '\n');

    const int CANTIDAD = _repo.cantidadRegistros();

    bool* indices = new bool[CANTIDAD];
    for (int i = 0; i < CANTIDAD; i ++) { indices[i] = false; }

    Turno *turnos = _repo.leerTodos();
    ManagerPaciente mPaciente;
    
    // Busqueda personalizada por DNI o por nombre
    int opc = 0;

    std::cout << "Como desea buscar el paciente?\n";
    std::cout << "1. Por DNI\n";
    std::cout << "2. Por nombre completo\n";

    do{
        std::cout << "Opcion: ";
        std::cin >> opc;
    } while (opc != 1 && opc != 2);

    std::cin.ignore(100, '\n');

    // Para una leyenda posterior en caso de no existir
    bool encontrado = false;

    if (opc == 1) {
        // Busqueda por DNI
        int dni = 0;

        std::cout << "Ingrese el DNI del paciente: ";
        std::cin >> dni;

        buscando();

        for (int i = 0; i < CANTIDAD; i ++) {
            if (turnos[i].getEliminado()) {
                continue;
            }
            if (turnos[i].getDniPaciente() == dni) {
                encontrado = true;
                indices[i] = true;
            }
        }
    }

    if (opc == 2) {
        // Busqueda por nombre completo
        std::string nombreCompleto;
        std::string nombreIngresado;
        Paciente auxPaciente;
        
        std::cout << "Ingrese el nombre y apellido del paciente, separados por espacio: ";
        std::getline(std::cin, nombreIngresado);

        buscando();
        
        for (int i = 0; i < CANTIDAD; i ++) {
            if (turnos[i].getEliminado()) {
                continue;
            }

            auxPaciente = turnos[i].getPaciente();

            nombreCompleto = "";
            nombreCompleto.append(auxPaciente.getNombre());
            nombreCompleto.append(" ");
            nombreCompleto.append(auxPaciente.getApellido());

            if (nombreCompleto.compare(nombreIngresado) == 0) {
                encontrado = true;
                indices[i] = true;
            }
        }
    }

    if (encontrado) {
        std::cout << "-- Se encontraron los siguientes turnos para el paciente seleccionado --\n";
        
        for (int i = 0; i < CANTIDAD; i ++) {
            if (indices[i]) {
                mPaciente.mostrar(turnos[i].getPaciente());
                separadorParcial();
            }
        }
    } else {
        std::cout << "No se ha encontrado el paciente en la base de datos de turnos\n";
    }

    std::cout << "Presione ENTER para continuar";
    rlutil::anykey();

    delete[] turnos;
    delete[] indices;
}

bool ManagerTurno::actualizar(Turno turno){
    std::cin.ignore(100, '\n');

    ManagerFecha mFecha;
    ManagerHora mHora;

    int dniPaciente;
    float importe = 0.0f;
    char opc = 'n';

    // Carga de paciente. Comienza con DNI
    while (true) {
        std::cout << "Ingrese el DNI del paciente (0 para dejarlo como estaba): ";
        std::cin >> dniPaciente;

        if (dniPaciente == 0) {
            dniPaciente = turno.getDniPaciente();
            break;
        }

        if (dniPaciente > 10000000 && dniPaciente < 99999999) {
            break;
        }

        std::cout << "Intente nuevamente. Asegurese que sea un numero de 8 digitos.\n";
    }

    turno.setDniPaciente(dniPaciente);

    std::cin.ignore(100, '\n');

    std::cout << "La fecha sera la misma? s/n: ";
    std::cin >> opc;

    if (opc != 's') {
        turno.setFechaAtencion(mFecha.cargar());
    }
    
    std::cout << "La hora sera la misma? s/n: ";
    std::cin >> opc;
    
    if (opc != 's') {
        turno.setHoraAtencion(mHora.cargar());
    }

    std::cout << "El importe sera el mismo? s/n: ";
    std::cin >> opc;
    
    if (opc != 's') {
        while (true) {
            std::cout << "Ingrese un importe: $";
            std::cin >> importe;

            if (importe >= 0) {
                turno.setImporte(importe);
                break;
            }

            std::cout << "No se permiten importes negativos. Intente nuevamente.\n";
        }
    }

    if (_repo.modificar(turno, _repo.getPos(turno.getID()))) {
        std::cout << "El turno se ha modificado correctamente. Presione ENTER para continuar.\n";
        rlutil::anykey();
        return true;
    }

    std::cout << "Ocurrio un error al intentar modificar el turno. Presione ENTER para continuar.\n";
    rlutil::anykey();
    return false;
}

bool ManagerTurno::eliminar(Turno turno) {
    char opc;

    std::cout << "Seguro que desea eliminar el turno? s/n: ";
    std::cin >> opc;

    if (opc == 's') {
        // ELIMINACION LOGICA
        turno.setEliminado(true);
        if (_repo.modificar(turno, _repo.getPos(turno.getID()))) {
            std::cout << "El turno se ha eliminado correctamente. Presione ENTER para continuar.\n";
            rlutil::anykey();
            return true;
        };

        // ELIMINACION FISICA
        /*
        if (_repo.eliminar(_repo.getPos(turno.getID()))){
            std::cout << "El turno se ha eliminado correctamente.\n";
            return true;
        } else {
            std::cout << "Ocurrio un error al intentar eliminar el turno.\n";
            return false;
        }
        */
        std::cout << "Ocurrio un error al intentar eliminar el turno. Presione ENTER para continuar.\n";
        rlutil::anykey();
        return false;
    }

    std::cout << "Operacion cancelada.\n";
    return false;
}

ArchivoTurno ManagerTurno::getRepositorio(){
    return _repo;
}
