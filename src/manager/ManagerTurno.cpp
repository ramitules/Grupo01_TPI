#include "manager/ManagerSecuencia.h"
#include "manager/ManagerPaciente.h"
#include "manager/ManagerProtocolo.h"
#include "manager/ManagerTurno.h"
#include "utils/ManagerFecha.h"
#include "utils/ManagerHora.h"
#include "utils/rlutil.h"
#include "utils/funcFrontend.h"
#include "Paciente.h"


ManagerTurno::ManagerTurno(){};

bool ManagerTurno::cargar(){
    std::cin.ignore(100, '\n');

    ManagerPaciente mPaciente;
    ManagerFecha mFecha;
    ManagerHora mHora;
    ManagerSecuencia mSecuencia;

    Secuencia sec = mSecuencia.cargar("Turno");

    int proximoID = sec.getIdActual();
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
        std::cout << "Desea cargar los datos del paciente ahora? s/n: ";
        std::cin >> opc;

        if (opc == 's') {
            mPaciente.cargar();
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
        mProtocolo.cargar(proximoID);
    }

    std::cin.ignore(100, '\n');

    fechaAtencion = mFecha.cargar();
    horaAtencion = mHora.cargar();

    Turno turno(proximoID, dniPaciente, fechaAtencion, horaAtencion, 0.0f);

    if (_repo.guardar(turno)) {
        std::cout << "El turno se ha guardado correctamente. Presione ENTER para continuar\n";

        rlutil::getkey();
        return true;
    }

    // Si falla, el ID en la secuencia vuelve a su estado anterior (rollback).
    // Se debe actualizar dicha secuencia.
    sec.setIdActual(proximoID - 1);
    mSecuencia.actualizar(sec);

    std::cout << "Ocurrio un error al intentar guardar el turno. Presione ENTER para continuar\n";
    
    rlutil::getkey();
    return false;
}

void ManagerTurno::mostrar(Turno turno){
    Paciente auxP = turno.getPaciente();

    ManagerFecha mFecha;
    ManagerHora mHora;

    std::cout << "ID: " << turno.getID() << "\n";
    std::cout << "Paciente: " << auxP.getNombre() << " " << auxP.getApellido() << ", con DNI " << auxP.getDNI() << "\n";
    std::cout << "Fecha de atencion: ";
    std::cout << mFecha.mostrar(turno.getFechaAtencion()) << "\n";
    std::cout << "Hora de atencion: ";
    std::cout << mHora.mostrar(turno.getHoraAtencion()) << "\n";
    std::cout << "Importe: $" << turno.getImporte() << "\n";
}

void ManagerTurno::mostrarTodos(){
    Turno auxTurno;
    for(int i=0; i<_repo.cantidadRegistros(); i++){
        auxTurno = _repo.leer(i);
        
        if (auxTurno.getEliminado()) {
            continue;
        }

        mostrar(auxTurno);
        std::cout << separadorParcial();
    }
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
    for (int i=0; i<CANTIDAD; i++) {
        if (turnos[i].getEliminado()) {
            continue;
        }

        mostrar(turnos[i]);
        std::cout << separadorParcial();
    }

    std::cout << separador();

    delete[] turnos;

    std::cout << "Presione ENTER para continuar";
    rlutil::getkey();
}

void ManagerTurno::agrupadosPaciente(){
    const int CANTIDAD = _repo.cantidadRegistros();
    bool* indicesVisitados = new bool[CANTIDAD] {false};
    Turno *turnos = _repo.leerTodos();
    Paciente auxPaciente;

    for (int i=0; i<CANTIDAD; i++) {
        // Saltear turnos ya mostrados
        if (indicesVisitados[i]) {
            continue;
        }

        if (turnos[i].getEliminado()) {
            indicesVisitados[i] = true;
            continue;
        }

        auxPaciente = turnos[i].getPaciente();
        std::cout << "-- Turnos del paciente " << auxPaciente.getNombre() << ' ' << auxPaciente.getApellido() << " --";
       
        for (int j=0; j<CANTIDAD; j++) {
            if (turnos[i].getEliminado()) {
                continue;
            }
            if (indicesVisitados[j]) {
                continue;
            }

            if (turnos[j].getDniPaciente() == auxPaciente.getDNI()) {
                mostrar(turnos[j]);
                std::cout << separadorParcial();
                indicesVisitados[j] = true;
            }
        }

        std::cout << separador() << "\n\n";
    }

    delete[] turnos;
    delete[] indicesVisitados;

    std::cout << "Presione ENTER para continuar";
    rlutil::getkey();
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

                mostrar(turnos[i]);
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

                    mostrar(turnos[i]);
                    std::cout << "\n\n";
                }
            }
        }

        delete[] fechasElegidas;
    }
    delete[] turnos;
    delete[] indicesVisitados;

    std::cout << "Presione ENTER para continuar";
    rlutil::getkey();
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
                std::cout << separadorParcial();
            }
        }
    } else {
        std::cout << "No se ha encontrado el paciente en la base de datos de turnos\n";
    }

    std::cout << "Presione ENTER para continuar";
    rlutil::getkey();

    delete[] turnos;
    delete[] indices;
}

bool ManagerTurno::exportarCSV(Turno turno) {
    Fecha fechaAux = turno.getFechaAtencion();
    Hora horaAux = turno.getHoraAtencion();

    std::string fechaStr = std::to_string(fechaAux.getDia()) + '/' + std::to_string(fechaAux.getMes()) + '/' + std::to_string(fechaAux.getAnio());
    std::string horaStr = std::to_string(horaAux.getHora()) + ':' + std::to_string(horaAux.getMinuto()) + ':' + std::to_string(horaAux.getSegundo());
    
    std::string nombreArchivo = "Turno " + std::to_string(turno.getID()) + ".csv";
    std::string csv = "";

    csv.append(std::to_string(turno.getID()) + ',');
    csv.append(std::to_string(turno.getDniPaciente()) + ',');
    csv.append(fechaStr + ',' + horaStr + ',');
    csv.append(std::to_string(turno.getImporte()) + ',');
    csv.append(turno.getEliminado() ? "SI" : "NO");

    if (_repo.exportarCSV(csv, nombreArchivo)) {
        std::cout << "El turno se ha exportado exitosamente al archivo " << nombreArchivo << "\n";
        std::cout << "Presione ENTER para continuar\n";
        rlutil::getkey();
        return true;
    }
    
    std::cout << "El turno no se ha podido exportar. Presione ENTER para continuar\n";
    rlutil::getkey();
    return false;
}

bool ManagerTurno::exportarTodosCSV() {
    std::string csv = stringTodosCSV();

    if (_repo.exportarCSV(csv, "Turnos.csv")) {
        std::cout << "Los turnos se han exportado exitosamente al archivo 'Turnos.csv'\n";
        std::cout << "Presione ENTER para continuar\n";
        rlutil::getkey();
        return true;
    }
    
    std::cout << "No se han podido exportar los turnos. Presione ENTER para continuar\n";
    rlutil::getkey();
    return false;
}

std::string ManagerTurno::stringTodosCSV() {
    Fecha fechaAux;
    Hora horaAux;

    std::string fechaStr;
    std::string horaStr;
    
    std::string nombreArchivo = "Turnos.csv";
    std::string csv = "";

    Turno* turnos = _repo.leerTodos();
    const int CANTIDAD = _repo.cantidadRegistros();

    for (int i = 0; i < CANTIDAD; i ++) {
        fechaAux = turnos[i].getFechaAtencion();
        horaAux = turnos[i].getHoraAtencion();

        fechaStr = std::to_string(fechaAux.getDia()) + '/' + std::to_string(fechaAux.getMes()) + '/' + std::to_string(fechaAux.getAnio());
        horaStr = std::to_string(horaAux.getHora()) + ':' + std::to_string(horaAux.getMinuto()) + ':' + std::to_string(horaAux.getSegundo());

        csv.append(std::to_string(turnos[i].getID()) + ',');
        csv.append(std::to_string(turnos[i].getDniPaciente()) + ',');
        csv.append(fechaStr + ',' + horaStr + ',');
        csv.append(std::to_string(turnos[i].getImporte()) + ',');
        csv.append(turnos[i].getEliminado() ? "SI" : "NO");
        
        csv.append("\n");
    }

    csv.pop_back(); // Eliminar ultimo salto de linea

    delete[] turnos;

    return csv;
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
        rlutil::getkey();
        return true;
    }

    std::cout << "Ocurrio un error al intentar modificar el turno. Presione ENTER para continuar.\n";
    rlutil::getkey();
    return false;
}

bool ManagerTurno::eliminar(Turno turno){
    char opc;

    std::cout << "Seguro que desea eliminar el turno? s/n: ";
    std::cin >> opc;

    if (opc == 's') {
        // ELIMINACION LOGICA
        turno.setEliminado(true);
        if (_repo.modificar(turno, _repo.getPos(turno.getID()))) {
            std::cout << "El turno se ha eliminado correctamente. Presione ENTER para continuar.\n";
            rlutil::getkey();
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
        rlutil::getkey();
        return false;
    }
    
}

ArchivoTurno ManagerTurno::getRepositorio(){
    return _repo;
}
