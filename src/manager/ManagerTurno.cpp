#include "manager/ManagerSecuencia.h"
#include "manager/ManagerPaciente.h"
#include "manager/ManagerProtocolo.h"
#include "manager/ManagerTurno.h"
#include "utils/ManagerFecha.h"
#include "utils/ManagerHora.h"
#include "Paciente.h"


ManagerTurno::ManagerTurno(){};

bool ManagerTurno::cargar(){
    std::cin.ignore(100, '\n');

    ManagerPaciente mPaciente;
    ManagerFecha mFecha;
    ManagerHora mHora;
    ManagerSecuencia mSecuencia;

    Secuencia sec = mSecuencia.cargar("Turno");

    int proximoID = sec.getIdActual() + 1;
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
        std::cout << "El turno se ha guardado correctamente.\n";
        return true;
    }

    std::cout << "Ocurrio un error al intentar guardar el turno.\n";
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
    for(int i=0; i<_repo.cantidadRegistros(); i++){
        this->mostrar(_repo.leer(i));
        std::cout << "------------------------\n";
    }
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
        std::cout << "El turno se ha modificado correctamente.\n";
        return true;
    }

    std::cout << "Ocurrio un error al intentar modificar el turno.\n";
    return false;
}

bool ManagerTurno::eliminar(Turno turno){
    char opc;

    std::cout << "Seguro que desea eliminar el turno? s/n: ";
    std::cin >> opc;

    if (opc == 's') {
        // ELIMINACION LOGICA
        turno.setEliminado(true);
        _repo.modificar(turno, _repo.getPos(turno.getID()));

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
    }

    return true;
}

ArchivoTurno ManagerTurno::getRepositorio(){
    return _repo;
}
