#include "manager/ManagerSecuencia.h"
#include "manager/ManagerAnalisis.h"
#include "manager/ManagerTurno.h"
#include "utils/ManagerFecha.h"
#include "utils/ManagerHora.h"
#include "archivo/ArchivoPaciente.h"
#include "archivo/ArchivoAnalisis.h"


ManagerTurno::ManagerTurno(){};

bool ManagerTurno::cargar(){
    std::cin.ignore(100, '\n');

    ArchivoPaciente repoPacientes;
    ArchivoAnalisis repoAnalisis;

    ManagerFecha mFecha;
    ManagerHora mHora;
    ManagerAnalisis mAnalisis;
    ManagerSecuencia mSecuencia;

    Secuencia sec = mSecuencia.cargar("Turno");

    int proximoID = sec.getIdActual() + 1;
    int dniPaciente;
    int idAnalisis = 0;
    Fecha fechaAtencion;
    Hora horaAtencion;
    float importe = 0.0f;
    char opc = 'n';

    while (true) {
        std::cout << "Ingrese el DNI del paciente: ";
        std::cin >> dniPaciente;

        if (dniPaciente > 10000000 && dniPaciente < 99999999) {
            break;
        }

        std::cout << "Intente nuevamente. Asegurese que sea un numero de 8 digitos.\n";
    }

    std::cout << "Desea cargar el analisis ahora? s/n: ";
    std::cin >> opc;

    if (opc == 's') {
        if (mAnalisis.cargar()) {
            std::cout << "Analisis cargado correctamente.\n";
            idAnalisis = repoAnalisis.leer(repoAnalisis.cantidadRegistros() - 1).getId();
        } else {
            std::cout << "No se pudo cargar el analisis. Saliendo de la carga de turno.\n";
            return false;
        }
    }

    std::cin.ignore(100, '\n');

    fechaAtencion = mFecha.cargar();
    horaAtencion = mHora.cargar();

    opc = 'n';

    if (idAnalisis != 0) {
        std::cout << "El turno tendra el mismo importe que el precio del analisis? s/n: ";
        std::cin >> opc;

        if (opc == 's') {
            importe = repoAnalisis.leer(repoAnalisis.getPos(idAnalisis)).getTipoAnalisis().getPrecio();
        }
    } else {
        while (true) {
            std::cout << "Ingrese el importe del turno: ";
            std::cin >> importe;

            if (importe > 0) {
                break;
            }

            std::cout << "Intente nuevamente. El importe debe ser mayor a 0.\n";
        }
    }

    Turno turno(proximoID, dniPaciente, idAnalisis, fechaAtencion, horaAtencion, importe);

    if (_repo.guardar(turno)) {
        std::cout << "El turno se ha guardado correctamente.\n";
        return true;
    }

    std::cout << "Ocurrio un error al intentar guardar el turno.\n";
    return false;
}

void ManagerTurno::mostrar(Turno turno){
    Paciente auxP = turno.getPaciente();
    Analisis auxA = turno.getAnalisis();

    ManagerFecha mFecha;
    ManagerHora mHora;

    std::cout << "ID: " << turno.getID() << "\n";
    std::cout << "Paciente: " << auxP.getNombre() << " " << auxP.getApellido() << ", con DNI " << auxP.getDNI() << "\n";

    if (auxA.getId() != 0) {
        TipoAnalisis auxTA = auxA.getTipoAnalisis();
        std::cout << "Tipo de analsis: " << auxTA.getID() << " - " << auxTA.getNombreAnalisis() << "\n";
    } else {
        std::cout << "Tipo de analisis: 0 - No asignado\n";
    }

    std::cout << "Fecha de atencion: ";
    std::cout << mFecha.mostrar(turno.getFechaAtencion()) << "\n";
    std::cout << "Hora de atencion: ";
    std::cout << mHora.mostrar(turno.getHoraAtencion()) << "\n";
    std::cout << "Importe: $" << turno.getImporte() << "\n";
}

void ManagerTurno::mostrarTodos(){
    for(int i=0; i<_repo.cantidadRegistros(); i++){
        this->mostrar(_repo.leer(i));
    }
}

bool ManagerTurno::actualizar(Turno turno){
    // PENDIENTE
}

bool ManagerTurno::eliminar(Turno turno){
    char opc;

    std::cout << "Seguro que desea eliminar el turno? s/n: ";
    std::cin >> opc;

    if (opc == 's') {
        if (_repo.eliminar(_repo.getPos(turno.getID()))){
            std::cout << "El turno se ha eliminado correctamente.\n";
            return true;
        } else {
            std::cout << "Ocurrio un error al intentar eliminar el turno.\n";
            return false;
        }
    }
}